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
  renderer.clear();
  renderer.drawBorder();
  renderer.drawScore(game.getScore());

  renderer.render();
}
void loop() {

  renderer.clear();
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
    game.setHasTetromino(true);
  }

  renderer.drawBorder();
  renderer.drawScore(game.getScore());
  renderer.drawGrid(game);
  renderer.drawTetromino(t);

  renderer.render();

  delay(1000);
}