#pragma once
#include <Arduino.h>
struct Display {
    private:
        // promenne pro animace
        enum animType {STATIC, FLY_IN, FLY_OUT};
        animType currentAnimState = STATIC;
        uint8_t animStep = 0;

        //helper funkce
        void rotateSeconds(), rotateMinutesHours();
        void stepAnimation();
    public:
        //nastavenicko
        bool slotSecondsUnits = false;
        uint16_t animUpdateInterval = 150; //interval volani OnUpdate v ms
        uint16_t rotateSecondsInterval = 75; //interval otaceni sekund v ms
        uint16_t rotateMinutesHoursInterval = 75; //interval otaceni minut a hodin v ms

        void OnUpdate();
        void TurnOn(){
            currentAnimState = FLY_IN;
        }
        void TurnOff(){
            currentAnimState = FLY_OUT;
        }

        uint8_t digits[6];

        //gettery a settery
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