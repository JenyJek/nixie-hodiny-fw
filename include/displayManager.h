#pragma once
#include <Arduino.h>
struct Display {
    private:
        // promenne pro animace
        enum animType {STATIC, FLY_IN, FLY_OUT};
        animType currentAnimState = STATIC;
        bool animRunning;
        uint8_t animStep = 0;

        // promenne pro tocky
        bool slottingActive = true;
        bool secondsChanged, hrsMinsChanged;

        //helper funkce
        
    public:
        void rotateSeconds(), rotateMinutesHours();

        bool isAnimRunning(){return this->animRunning;}
        bool slotSecondsUnits = false;
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
        uint8_t getSeconds() {return (this->digits[4] * 10 + this->digits[5]);}
        uint8_t getMinutes() {return (this->digits[2] * 10 + this->digits[3]);}
        uint8_t getHours() {return (this->digits[0] * 10 + this->digits[1]);}   
};

extern Display display;