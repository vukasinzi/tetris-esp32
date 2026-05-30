#pragma once

#include <Arduino.h>

class sender
{
private:
    String createScoreJson(int score, int lines);
    bool connectToWiFi();

public:
    sender();

    bool begin();
    bool sendScore(int score, int lines);
};