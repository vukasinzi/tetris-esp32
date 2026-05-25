#pragma once
#include <stdint.h>
#include <cstdlib>
#include "tetromino.h"
#include <cstring>


class Game{
  private:
    int score = 0;
    uint16_t grid[10][20] = {0};
    bool currentTetrominoActive = false;
    Tetromino currentTetromino;

  public:
    Game();
    int getScore();
    void addScore(int amount);
  uint16_t getCell(uint16_t x, uint16_t y);
    void setCell(uint16_t x, uint16_t y);
    bool hasTetromino();
    void setHasTetromino(bool value);
    bool canFallDown();
    bool canMove(Tetromino& t);
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    bool tryRotate();//glavno odstupanje

    void saveTetromino();
    Tetromino& getCurrentTetromino();
  bool collidesWithGrid(Tetromino& t);



};