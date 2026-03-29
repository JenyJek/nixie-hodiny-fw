#pragma once
#include <Arduino.h>
#include <melodies.h>

struct almSound
{
    private:
        int noteToFreq(char note);
        uint8_t current_position;
        uint8_t accumulatedWaitTime;
        void proceed();
        uint64_t lastMillis;
    public:
        Melody currentMelody;
        bool run = false;
        almSound() : current_position(0), accumulatedWaitTime(0), lastMillis(0), currentMelody("", 0, false), run(false) {}
        void stop();
        void loop();
        void play() {this->run = true;};
};
extern almSound toneMachine;
//e2d2f1g1