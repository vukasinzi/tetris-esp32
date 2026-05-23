#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "renderer.h"
#include "config.h"


Adafruit_SSD1306 display(128, 64, &Wire, -1);

enum class STATE{
  START,GAME_OVER, SPAWN,FALL
};
STATE state = STATE::START;
Game game;
Renderer renderer(&display);
unsigned long previous;
void setup() {
  Wire.begin(21, 22);
  renderer.begin();
 
}
void gameTick(){
 
 
  switch(state)
  {
    case STATE::START:
    game = Game();
    state = STATE::SPAWN;
    break;

    case STATE::SPAWN:
    game.getCurrentTetromino().spawnTetro();
    if(game.collidesWithGrid(game.getCurrentTetromino()))
    {
      state = STATE::GAME_OVER;
      break;
    }
    game.setHasTetromino(true);
    state = STATE::FALL;
    break;

    case STATE::FALL:
    if(game.hasTetromino())
    {
      if(game.canFallDown())
        game.getCurrentTetromino().fallDown();
      else{
        game.saveTetromino();
        game.setHasTetromino(false);
        state = STATE::SPAWN;
        }
    }
    break;

    case STATE::GAME_OVER:
      //opcija da se igra restartuje...
    break;
  }
  


}

void loop() {
  if(state == STATE::GAME_OVER)
    return;
  unsigned long currentTime = millis();
  if((currentTime-previous)>=10)
  {
    previous = currentTime;
    gameTick();
    
  }
  renderer.clear();
  
  if(state == STATE::GAME_OVER){
    renderer.drawGameOver();
    game = Game();
    previous = millis();
  } else {
    renderer.drawBorder();
    renderer.drawScore(game.getScore());
    renderer.drawGrid(game);
    if(game.hasTetromino())
      renderer.drawTetromino(game.getCurrentTetromino());
  }
  
  renderer.render();
 
}