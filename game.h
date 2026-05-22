#pragma once
#include <stdint.h>


class Game{
  private:
    int score = 0;
    uint16_t grid[20][10] = {0};
  public:
    int getScore();
    void addScore(int amount);



};