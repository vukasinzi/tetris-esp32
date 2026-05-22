#include "game.h"

void Game::addScore(int amount) {
    score += amount;
}
int Game::getScore()
{
  return score;
}