#pragma once

class inputManager{
  public:
     void begin();
     void update();
     bool anyKeyPressed();
     bool consumeLeft();
     bool consumeRight();
     bool consumeDown();
     bool consumeRotate();

  private:
    bool left = false;
    bool right = false;
    bool down = false;
    bool rotate = false;
};