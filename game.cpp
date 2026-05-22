#include "game.h"

void Game::addScore(int amount) {
    score += amount;
}
int Game::getScore()
{
  return score;
}
uint16_t Game::getCell(uint16_t x, uint16_t y){
  return grid[x][y];
}
void Game::setCell(uint16_t x, uint16_t y){
  grid[x][y] = 1;
}
bool Game::hasTetromino(){
  return currentTetrominoActive;
}
Tetromino& Game::getCurrentTetromino(){
  return currentTetromino;
}
void Game:: setHasTetromino(bool value)
{
  currentTetrominoActive = value;
}
bool Game:: canFallDown(){
  for(int i = 0; i<4;i++)
  {
    int tetromino_x = currentTetromino.getTetroblocks()[i].p.x;
    int tetromino_y = currentTetromino.getTetroblocks()[i].p.y;
    if(tetromino_x>=10 || tetromino_y >=19)
      return false;
    if(grid[tetromino_x][tetromino_y+1]==1)
      return false;
  }
  return true;

}
void Game:: saveTetromino(){
  
  for(int i = 0; i< 4;i++)
  {
    Position pt = getCurrentTetromino().getTetroblocks()[i].p;  
    grid[pt.x][pt.y] = 1;
  }
  setHasTetromino(false);
}
