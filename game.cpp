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
int Game::getLines()
{
    return globalCount;
}

int Game::getLevel()
{
    return globalCount / 10 + 1;
}

int Game::getFallDelay()
{
    int delayMs = 1000 - ((getLevel() - 1) * 80);//12 levela. posle 12og bude fiksno 150ms.

    if (delayMs < 150)
        delayMs = 150;

    return delayMs;
}
void Game::clearLines() {
    int count = 0;
    for (int i = 0; i < 20; i++) {

        bool flag = true;
        for (int j = 0; j < 10; j++) {
            if (grid[j][i] == 0) {
                flag = false;
                break;
            }
        }

        if (flag) {
            count++;
            for (int k = i; k > 0; k--) {//krecem od trenutnog reda koji je pun i idem nagore
                for (int j = 0; j < 10; j++) {
                    grid[j][k] = grid[j][k - 1];
                }
            }
            for (int j = 0; j < 10; j++)//bitan edge case za vrh table. nemoguce je da nesto van grida padne na prvi red, pa moramo ga rucno resetovati
                grid[j][0] = 0;
            i--;//prakticno ovaj deo f-je gore pomeri sve za jedan red dole kad red bude skrsen. samim tim i-1 postaje i. to je dobro ali for petlja gore ce pomeriti i na i++!
            //zato moramo da neutralisemo taj njen preskok
        }
    }
    switch(count) {
        case 1: addScore(100 * getLevel()); break;
        case 2: addScore(300 * getLevel()); break;
        case 3: addScore(500 * getLevel()); break;
        case 4: addScore(800 * getLevel()); break;}
    globalCount+=count;
}
