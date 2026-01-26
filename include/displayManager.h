#pragma once
#include <Arduino.h>
struct Display {
    private:
        enum animType {STATIC, FLY_IN, FLY_OUT, OFF};
        animType currentAnimState = STATIC;
        bool animRunning;
        uint8_t animStep = 0;

        bool secondsChanged, hrsMinsChanged;
    public:
        bool isAnimRunning(){return this->animRunning;}
        bool slotSecondsUnits = true;
        void stepAnimation();
        uint8_t digits[6];
        void fillDigits(uint8_t hours, uint8_t minutes, uint8_t seconds){
            this->digits[0] = hours / 10;
            this->digits[1] = hours % 10;
            this->digits[2] = minutes / 10;
            this->digits[3] = minutes % 10;
            this->digits[4] = seconds / 10;
            this->digits[5] = seconds % 10;
        }   
};

extern Display display;