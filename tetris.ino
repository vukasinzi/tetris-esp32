#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "renderer.h"
#include "config.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);


Game game;
Renderer renderer(&display);

void setup() {
  Wire.begin(21, 22);
  renderer.begin();
 
}
void gameLoop(){
  Tetromino& t = game.getCurrentTetromino();
  if(game.hasTetromino())
  {
    if(game.canFallDown())
      t.fallDown();
    else{
      game.saveTetromino();
    }
   
  }
  else
  {
    t.spawnTetro();

    if(game.collidesWithGrid(t))
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
  gameLoop();
  
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
  delay(10);
}