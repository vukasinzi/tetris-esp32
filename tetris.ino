#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "renderer.h"
#include "config.h"
#include "inputManager.h"


Adafruit_SSD1306 display(128, 64, &Wire, -1);

enum class STATE{
  MAIN_MENU,START,GAME_OVER, SPAWN,FALL
};
STATE state = STATE::MAIN_MENU;
Game game;
inputManager input;
Renderer renderer(&display);
unsigned long previous;
unsigned long currentTime;

void setup() {
  Wire.begin(21, 22);
  renderer.begin();
   input.begin();

}
void gameTick(){
 
 
  switch(state)
  {
    case STATE::START:
    previous = millis();
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
        game.clearLines();
        game.setHasTetromino(false);
        state = STATE::SPAWN;
        }
    }
    break;

    case STATE::GAME_OVER:
    if (input.anyKeyPressed()) {
    state = STATE::START;
    }

    break;
  }
}
void handleInput(){
  
  Tetromino& t = game.getCurrentTetromino();
  if(input.consumeLeft() && game.canMoveLeft())
    t.moveLeft();

  if(input.consumeRight() && game.canMoveRight())
    t.moveRight();

  if(input.consumeDown() && game.canFallDown())
    t.fallDown();

  if(input.consumeRotate())
    game.tryRotate();
  
}
void loop() {
   input.update();

    currentTime = millis();
    
  renderer.clear();
  switch(state)
  {
    case STATE::GAME_OVER:
    renderer.drawMenu("GAME OVER","press");
    if (input.anyKeyPressed()) {
      state = STATE::START;
    }
    break;
    case STATE::MAIN_MENU:
    renderer.drawMenu("MAIN MENU","press");
     if (input.anyKeyPressed()) {
      state = STATE::START;
     }
    break;
    case STATE::START:
    gameTick();
    break;
    default:
     if ((currentTime - previous) >= game.getFallDelay()) {
        previous = currentTime; //poseban slucaj zato što prvi spawn krene sa 2s kasnjenja umesto 1s.
    //resenje - ne cekamo da prodje 2 sekunde za 2 ticka da bi se desio prebacaj mainmenu->start->spawn nego automatski ga pozovemo.
        gameTick();
     }
    renderer.drawBorder();
    renderer.drawStats(game);
    renderer.drawGrid(game);
    if(game.hasTetromino())
    {
      handleInput();
      renderer.drawTetromino(game.getCurrentTetromino());
    }
    break;
   }
  renderer.render();
   
}