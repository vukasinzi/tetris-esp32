
#include "renderer.h"


Renderer::Renderer(Adafruit_SSD1306* dis)
{
  display = dis;
}
void Renderer::begin(){
  display->begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display->clearDisplay();
  display->setRotation(1);
  display->setTextColor(SSD1306_WHITE);
  display->setTextSize(1);
  display->setCursor(0, 0);
}
void Renderer::clear(){
  display->clearDisplay();
}
void Renderer::render(){
  display->display();
}
void Renderer::drawStats(Game& game)
{
    display->setCursor(SCORE_X, SCORE_Y);
    display->print("S:");
    display->print(game.getScore());

    display->setCursor(SCORE_X, SCORE_Y + 10);
    display->print("L:");
    display->print(game.getLevel());
}
void Renderer::drawBorder()
{
  display->drawRect(BORDER_X, BORDER_Y, BORDER_W, BORDER_H, SSD1306_WHITE);
}
void Renderer::drawGrid(Game& game)
{
  
  for(int i = 0; i<10;i++)
  {
    for(int j = 0;j<20;j++)
    {
      if(game.getCell(i,j) == 1)
      {
        int x = BORDER_X + i*CELL;
        int y = BORDER_Y + j*CELL;
        display->drawRect(x,y, CELL, CELL, SSD1306_WHITE);

      }
    }
  }
}
void Renderer::drawTetromino(Tetromino& t)
{
  TetroBlock* blocks = t.getTetroblocks();
  for (int i = 0; i< 4; i++) {
    int x = BORDER_X+ blocks[i].p.x*CELL;
    int y = BORDER_Y +blocks[i].p.y*CELL;

   display->drawRect(x,y, CELL, CELL, SSD1306_WHITE);
  
  }
}
void Renderer::drawMenu(const char* title, const char* prompt)
{
 display->setCursor(5, 60);
  display->println(title);
   display->setCursor(18,75);
  display->println(prompt); 
}

