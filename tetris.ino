#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "renderer.h"
#include "config.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);


Game game;
Renderer renderer(&display);
unsigned long previous;
void setup() {
  Wire.begin(21, 22);
  renderer.begin();
 
}
void gameTick(){
 
 
  if(game.hasTetromino())
  {
   
    if(game.canFallDown())
      game.getCurrentTetromino().fallDown();
    else{
      game.saveTetromino();
    }
   
  }
  else
  {
    game.getCurrentTetromino().spawnTetro();

    if(game.collidesWithGrid(game.getCurrentTetromino()))
    {
      game.funcGameOver();
      return;
    }

    game.setHasTetromino(true);
  }

}

void loop() {
  if(game.isGameOver())
    return;
  unsigned long currentTime = millis();
  if((currentTime-previous)>=1000)
  {
    previous = currentTime;
    gameTick();
    
  }
  
  renderer.clear();
  
  if(game.isGameOver()) {
    renderer.drawGameOver();
  } else {
    renderer.drawBorder();
    renderer.drawScore(game.getScore());
    renderer.drawGrid(game);
    renderer.drawTetromino(game.getCurrentTetromino());
  }
  
  renderer.render();
 
}