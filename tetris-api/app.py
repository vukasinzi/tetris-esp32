import os

from dotenv import load_dotenv
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.exc import OperationalError

load_dotenv()

app = Flask(__name__)

database_url = os.getenv("DATABASE_URL")
API_KEY = os.getenv("API_KEY")

if not database_url:
    raise RuntimeError("DATABASE_URL nije podesen u .env fajlu.")

if not API_KEY:
    raise RuntimeError("API_KEY nije podesen u .env fajlu.")

app.config["SQLALCHEMY_DATABASE_URI"] = database_url
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

app.config["SQLALCHEMY_ENGINE_OPTIONS"] = {
    "pool_pre_ping": True,
    "pool_recycle": 300,
}

db = SQLAlchemy(app)


class Score(db.Model):
    __tablename__ = "scores"

    id = db.Column(db.Integer, primary_key=True)
    score = db.Column(db.Integer, nullable=False)
    lines = db.Column(db.Integer, nullable=False, default=0)
    created_at = db.Column(
        db.DateTime(timezone=True),
        server_default=db.func.now(),
        nullable=False
    )


@app.route("/", methods=["GET"])
def home():
    return jsonify({
        "status": "ok",
        "message": "Tetris API radi"
    })


@app.route("/api/scores", methods=["POST"])
def add_score():
    received_key = request.headers.get("X-API-Key")

    if received_key != API_KEY:
        return jsonify({"error": "Unauthorized"}), 401

    data = request.get_json(silent=True)

    if data is None:
        return jsonify({"error": "Missing JSON body"}), 400

    score = data.get("score")
    lines = data.get("lines", 0)

    if not isinstance(score, int) or score < 0:
        return jsonify({"error": "Invalid score"}), 400

    if not isinstance(lines, int) or lines < 0:
        return jsonify({"error": "Invalid lines"}), 400

    try:
        new_score = Score(score=score, lines=lines)

        db.session.add(new_score)
        db.session.commit()

        return jsonify({
            "message": "Score saved",
            "id": new_score.id
        }), 201

    except OperationalError:
        db.session.rollback()
        db.engine.dispose()

        try:
            new_score = Score(score=score, lines=lines)

            db.session.add(new_score)
            db.session.commit()

            return jsonify({
                "message": "Score saved after reconnect",
                "id": new_score.id
            }), 201

        except OperationalError as error:
            db.session.rollback()

            return jsonify({
                "error": "Database connection failed",
                "details": str(error)
            }), 500


@app.route("/api/scores/top", methods=["GET"])
def get_top_scores():
    try:
        scores = (
            Score.query
            .order_by(Score.score.desc())
            .limit(10)
            .all()
        )

        result = []

        for s in scores:
            result.append({
                "id": s.id,
                "score": s.score,
                "lines": s.lines,
                "created_at": s.created_at.isoformat()
            })

        return jsonify(result)

    except OperationalError as error:
        db.session.rollback()
        db.engine.dispose()

        return jsonify({
            "error": "Database connection failed",
            "details": str(error)
        }), 500


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
