#pragma once
#include <Arduino.h>
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
        enum dotMode {NONE, TIME, DATE, ALARM_SET, ALARM_RUN};
        dotMode currentMode;

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

        uint8_t digits[6];

        //gettery a settery
        void fillDigits(uint8_t hours, uint8_t minutes, uint8_t seconds){
            this->digits[0] = (hours >> 4) & 0xF;
            this->digits[1] = hours & 0xF;
            this->digits[2] = (minutes >> 4) & 0xF;
            this->digits[3] = minutes & 0xF;
            this->digits[4] = (seconds >> 4) & 0xF;
            this->digits[5] = seconds & 0xF;
        }

        uint8_t getSeconds() {return (this->digits[4] * 10 + this->digits[5]);}
        uint8_t getMinutes() {return (this->digits[2] * 10 + this->digits[3]);}
        uint8_t getHours() {return (this->digits[0] * 10 + this->digits[1]);}   
};

extern Display display;