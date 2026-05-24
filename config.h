/*Dimenzije ekrana za sada su 64x128
 
  pa sledi:
  border 2px sa obe strane
  cell 5px
  score 8px visine nebitna duzina
  razmaci ...

  dimenzije samo sa borderima su 52x102 
  52px ostaje 12 , dakle border pocinje na 6 pixelu?
*///64x128px
#pragma once
#define CELL 5
#define X_COUNT 10
#define Y_COUNT 20

#define SCORE_X 6
#define SCORE_Y 5

#define BORDER_X 6
#define BORDER_Y 18//koordinate, 5 prazno, 8 rez za score i 5 razmak

#define BORDER_W 52
#define BORDER_H 102


const int LEFT_BUTTON = 14;
const int DOWN_BUTTON = 25;
const int RIGHT_BUTTON = 26;
const int ROTATION_BUTTON = 27;
//dakle ostace dole 8 Y pixela
