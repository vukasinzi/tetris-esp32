#pragma once
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "tetromino.h"
#include "game.h"

class Renderer{
  private:
      Adafruit_SSD1306* display;
  public:
    Renderer(Adafruit_SSD1306* display);
    void begin();
    void drawScore(int score);
    void drawBorder();
    void render();
    void clear();
    void drawTetromino(Tetromino& t);
    void drawGrid(Game& game);
    void drawGameOver();


};