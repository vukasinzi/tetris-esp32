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
  game.addScore(12);
  
  renderer.drawBorder();
  renderer.drawScore(game.getScore());
  
}

void loop() {}