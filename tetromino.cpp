#include "tetromino.h"  
#include <esp_system.h>
#include <Arduino.h>


void Tetromino::spawnTetro()
{
      type = (TetrominoType)(esp_random() % 7);
      for(int i = 0; i< 4;i++)
      {
        tetroBlocks[i].p = shapes[(int)type][i];
      }
}
TetrominoType Tetromino::getTetroType()
{
  return type;
}
TetroBlock* Tetromino::getTetroblocks()
{
  return tetroBlocks;
}
void Tetromino::fallDown(){
    for(int i = 0; i< 4;i++)
    {
      tetroBlocks[i].p.y+=1;
    }
}
void Tetromino::moveLeft()
{
  for(int i = 0;i<4;i++)
  {
    tetroBlocks[i].p.x-=1;
  }
}
void Tetromino::moveRight(){
   for(int i = 0;i<4;i++)
  {
    tetroBlocks[i].p.x+=1;
  }
}
void Tetromino::rotate()
{
  if(type == TetrominoType::O)
    return;
  int pivotX = tetroBlocks[1].p.x;
  int pivotY = tetroBlocks[1].p.y;

  for(int i = 0; i < 4; i++)
  {
    int oldX = tetroBlocks[i].p.x;
    int oldY = tetroBlocks[i].p.y;

    int dx = oldX - pivotX;
    int dy = oldY - pivotY;

    tetroBlocks[i].p.x = pivotX - dy;
    tetroBlocks[i].p.y = pivotY + dx;
  }
}