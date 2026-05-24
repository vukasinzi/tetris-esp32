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
      rotation = Rotation::zero;
}
TetrominoType Tetromino::getTetroType()
{
  return type;
}
TetroBlock* Tetromino::getTetroblocks()
{
  return tetroBlocks;
}
Rotation Tetromino::getRotation()
{
  return rotation;
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
  
}
