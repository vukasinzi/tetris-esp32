#include "inputManager.h"
#include "config.h"
#include <Arduino.h>

static volatile bool leftInterrupt;
static volatile bool downInterrupt;
static volatile bool rightInterrupt;
static volatile bool rotateInterrupt;

void IRAM_ATTR onLeftButton() {
  leftInterrupt = true;
}

void IRAM_ATTR onRightButton() {
  rightInterrupt = true;
}

void IRAM_ATTR onDownButton() {
  downInterrupt = true;
}

void IRAM_ATTR onRotationButton() {
  rotateInterrupt = true;
}

void inputManager::begin() {
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ROTATION_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), onLeftButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(DOWN_BUTTON), onDownButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROTATION_BUTTON), onRotationButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), onRightButton, FALLING);
}

void inputManager::update() {
  if (leftInterrupt) {
    leftInterrupt = false;
    delay(20);

    if (digitalRead(LEFT_BUTTON) == LOW) {
      left = true;
    }
  }

  if (rightInterrupt) {
    rightInterrupt = false;
    delay(20);

    if (digitalRead(RIGHT_BUTTON) == LOW) {
      right = true;
    }
  }

  if (rotateInterrupt) {
    rotateInterrupt = false;
    delay(20);

    if (digitalRead(ROTATION_BUTTON) == LOW) {
      rotate = true;
    }
  }

  if (downInterrupt) {
    downInterrupt = false;
    delay(20);

    if (digitalRead(DOWN_BUTTON) == LOW) {
      down = true;
    }
  }
}

bool inputManager::anyKeyPressed() {
  if (left || right || down || rotate) {
    left = false;
    right = false;
    down = false;
    rotate = false;
    return true;
  }

  return false;
}

bool inputManager::consumeLeft() {
  if (left) {
    left = false;
    return true;
  }

  return false;
}

bool inputManager::consumeRight() {
  if (right) {
    right = false;
    return true;
  }

  return false;
}

bool inputManager::consumeDown() {
  if (down) {
    down = false;
    return true;
  }

  return false;
}

bool inputManager::consumeRotate() {
  if (rotate) {
    rotate = false;
    return true;
  }

  return false;
}