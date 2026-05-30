#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "game.h"
#include "renderer.h"
#include "config.h"
#include "inputManager.h"
#include "sender.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

sender scoreSender;
bool scoreSent = false;

enum class STATE {
  MAIN_MENU,
  START,
  GAME_OVER,
  SPAWN,
  FALL
};

STATE state = STATE::MAIN_MENU;

Game game;
inputManager input;
Renderer renderer(&display);

unsigned long previous;
unsigned long currentTime;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);
  renderer.begin();
  input.begin();

  scoreSender.begin();
}

void gameTick() {
  switch (state) {
    case STATE::START:
      previous = millis();
      game = Game();
      scoreSent = false;
      state = STATE::SPAWN;
      break;

    case STATE::SPAWN:
      game.getCurrentTetromino().spawnTetro();

      if (game.collidesWithGrid(game.getCurrentTetromino())) {
        state = STATE::GAME_OVER;
        break;
      }

      game.setHasTetromino(true);
      state = STATE::FALL;
      break;

    case STATE::FALL:
      if (game.hasTetromino()) {
        if (game.canFallDown()) {
          game.getCurrentTetromino().fallDown();
        }
        else {
          game.saveTetromino();
          game.clearLines();
          game.setHasTetromino(false);
          state = STATE::SPAWN;
        }
      }
      break;

    case STATE::GAME_OVER:
      break;

    case STATE::MAIN_MENU:
      break;
  }
}

void handleInput() {
  Tetromino& t = game.getCurrentTetromino();

  if (input.consumeLeft() && game.canMoveLeft()) {
    t.moveLeft();
  }

  if (input.consumeRight() && game.canMoveRight()) {
    t.moveRight();
  }

  if (input.consumeDown() && game.canFallDown()) {
    t.fallDown();
  }

  if (input.consumeRotate()) {
    game.tryRotate();
  }
}

void loop() {
  input.update();

  currentTime = millis();

  renderer.clear();

  switch (state) {
    case STATE::MAIN_MENU:
      renderer.drawMenu("MAIN MENU", "press");

      if (input.anyKeyPressed()) {
        state = STATE::START;
      }

      break;

    case STATE::START:
      gameTick();
      break;

    case STATE::GAME_OVER:
      if (!scoreSent) {
        Serial.println("GAME OVER - sending score");
        scoreSender.sendScore(game.getScore(), game.getLines());
        scoreSent = true;
      }

      renderer.drawMenu("GAME OVER", "press");

      if (input.anyKeyPressed()) {
        state = STATE::START;
      }

      break;

    case STATE::SPAWN:
    case STATE::FALL:
      if ((currentTime - previous) >= game.getFallDelay()) {
        previous = currentTime;
        gameTick();
      }

      renderer.drawBorder();
      renderer.drawStats(game);
      renderer.drawGrid(game);

      if (game.hasTetromino()) {
        handleInput();
        renderer.drawTetromino(game.getCurrentTetromino());
      }

      break;
  }

  renderer.render();
}