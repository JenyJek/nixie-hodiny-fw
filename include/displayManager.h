#pragma once
#include <Arduino.h>
#include <mainGlobals.h>

struct Display {
    private:
        // promenne pro animace
        enum animType {STATIC, FLY_IN, FLY_OUT, OFF};
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
        uint16_t doubleDotOnTime = 250;
        enum dotMode {NONE, TIME, DATE, ALARM_SET, ALARM_RUN, TEMP};
        dotMode currentMode;
        bool slotToInvisible = false; //pro DMODy, ktere zahrnuji prazdny charakter - zahrnuje v toceni cislicema i 0xA, resp. nezobrazeno

        void SetDots(dotMode mode){
            currentMode = mode;
            if(currentAnimState != OFF) {
                switch (currentMode){
                    case NONE:
                        displayBuffer.setDots(0b0000);
                    break;
                    case TIME:
                        displayBuffer.setDots(0b1110);
                    break;
                    case DATE:
                        displayBuffer.setDots(0b1100);
                    break;
                    case ALARM_SET:
                        displayBuffer.setDots(0b1010);
                    break;
                    case ALARM_RUN:
                        displayBuffer.setDots(0b0010);
                    break;
                    case TEMP:
                        displayBuffer.setDots(0b0100);
                }
            }
            else{
                displayBuffer.setDots(0b0000);
            }
        }

        void OnUpdate();
        void TurnOn(){
            currentAnimState = FLY_IN;
        }
        void TurnOff(){
            currentAnimState = FLY_OUT;
        }
        bool IsOn(){
            return currentAnimState == STATIC;
        }
        void setup();
        uint8_t digits[6];

        //gettery a settery
        void fillDigits(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t mask){
            this->digits[0] = mask & 0x20 ? (hours >> 4) & 0xF : hours / 10;
            this->digits[1] = mask & 0x10 ? hours & 0xF : hours % 10;
            this->digits[2] = mask & 0x08 ? (minutes >> 4) & 0xF : minutes / 10;
            this->digits[3] = mask & 0x04 ? minutes & 0xF : minutes % 10;
            this->digits[4] = mask & 0x02 ? (seconds >> 4) & 0xF : seconds / 10;
            this->digits[5] = mask & 0x01 ? seconds & 0xF : seconds % 10;
        }

        uint8_t getSeconds() {return (this->digits[4] * 10 + this->digits[5]);}
        uint8_t getMinutes() {return (this->digits[2] * 10 + this->digits[3]);}
        uint8_t getHours() {return (this->digits[0] * 10 + this->digits[1]);}   
};

extern Display display;