#pragma once
#include <Arduino.h>

struct almSound
{
    private:
        int noteToFreq(char note);
        uint8_t current_position;
        uint8_t accumulatedWaitTime;
    public:
        void proceed();
        char melody[32] = "1E2D1f1g2c1B1D1E2B1A1c1E2A2X0";
        void stop();
};
extern almSound toneMachine;
