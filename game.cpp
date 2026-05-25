#include "game.h"

Game::Game() = default;
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
bool Game::canMove(Tetromino& t){
  for(int i = 0; i < 4; i++)
  {
    int x = t.getTetroblocks()[i].p.x;
    int y = t.getTetroblocks()[i].p.y;

    if(x < 0 || x >= 10 || y < 0 || y >= 20)
      return false;

    if(grid[x][y] == 1)
      return false;
  }

  return true;
}
bool Game:: canFallDown()
{
  Tetromino copy = currentTetromino;
  copy.fallDown();
  return canMove(copy);
}
bool Game::canMoveLeft(){
  Tetromino copy = currentTetromino;
  copy.moveLeft();
  return canMove(copy);
}
bool Game::canMoveRight(){
  Tetromino copy = currentTetromino;
  copy.moveRight();
  return canMove(copy);
}
/**implementirano floor kick na dnu f-je i wallkickovi x2*/
bool Game::tryRotate()
{
  Tetromino copy = currentTetromino;
  copy.rotate();

  if(canMove(copy))
  {
    currentTetromino = copy;
    return true;
  }

  Tetromino right1 = copy;
  right1.moveRight();

  if(canMove(right1))
  {
    currentTetromino = right1;
    return true;
  }

  Tetromino left1 = copy;
  left1.moveLeft();

  if(canMove(left1))
  {
    currentTetromino = left1;
    return true;
  }

  Tetromino right2 = copy;
  right2.moveRight();
  right2.moveRight();

  if(canMove(right2))
  {
    currentTetromino = right2;
    return true;
  }

  Tetromino left2 = copy;
  left2.moveLeft();
  left2.moveLeft();

  if(canMove(left2))
  {
    currentTetromino = left2;
    return true;
  }

  Tetromino up = copy;
  for(int i = 0; i < 4; i++)
  {
    up.getTetroblocks()[i].p.y -= 1;
  }

  if(canMove(up))
  {
    currentTetromino = up;
    return true;
  }

  return false;
}
void Game:: saveTetromino(){
  
  for(int i = 0; i< 4;i++)
  {
    Position pt = getCurrentTetromino().getTetroblocks()[i].p;  
    grid[pt.x][pt.y] = 1;
  }
  setHasTetromino(false);
}

bool Game::collidesWithGrid(Tetromino& t)
{
  TetroBlock* blocks = t.getTetroblocks();

  for(int i = 0; i < 4; i++)
  {
    int x = blocks[i].p.x;
    int y = blocks[i].p.y;

    if(grid[x][y] == 1)
      return true;
  }

  return false;
}