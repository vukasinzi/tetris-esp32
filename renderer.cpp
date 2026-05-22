
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
void Renderer::drawScore(int score)
{
  display->setCursor(SCORE_X, SCORE_Y);      
  display->print("S:");
  display->print(score);
  display->display();
}
void Renderer::drawBorder()
{
  display->drawRect(BORDER_X, BORDER_Y, BORDER_W, BORDER_H, SSD1306_WHITE);
  display->display();
}
void Renderer::drawTetromino(Tetromino t)
{
  TetroBlock* blocks = t.getTetroblocks();
  for (int i = 0; i< 4; i++) {
    int x = BORDER_X+ blocks[i].p.x*CELL;
    int y = BORDER_Y +blocks[i].p.y*CELL;

  display->drawRect(x,y, CELL, CELL, SSD1306_WHITE);
  display->display();
  
  }
}

