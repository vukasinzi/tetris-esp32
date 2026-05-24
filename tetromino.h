#pragma once
#include <stdint.h>

enum class TetrominoType{
  T,Z,S,O,J,L,I
};
enum class Rotation{
  zero = 0,half_pi=90,pi=180,pi_and_a_half=270
};
struct Position{
  int x;
  int y;
};

const Position shapes[7][4] = {
  { {4,0}, {5,0}, {6,0}, {5,1} }, // T
  { {4,0}, {5,0}, {5,1}, {6,1} }, // Z
  { {5,0}, {6,0}, {4,1}, {5,1} }, // S
  { {4,0}, {5,0}, {4,1}, {5,1} }, // O
  { {4,0}, {4,1}, {5,1}, {6,1} }, // J
  { {6,0}, {4,1}, {5,1}, {6,1} }, // L
  { {3,0}, {4,0}, {5,0}, {6,0} }  // I
};
struct TetroBlock{
  Position p;
};
class Tetromino{
  private:
    TetrominoType type;
    TetroBlock tetroBlocks[4];
    Rotation rotation;
  public:
      void spawnTetro();
      TetrominoType getTetroType();
      TetroBlock* getTetroblocks();
      Rotation getRotation();
      void fallDown();
      void moveLeft();
      void moveRight();
      void rotate();



  
};