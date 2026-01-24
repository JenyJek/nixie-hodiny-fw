#pragma once
#include <Arduino.h>
class DisplayBuffer{
    private:
        
    public:
        //storage casu
        uint8_t Seconds, Minutes, Hours;

        void Push(){
            displayedSecondsUnits = Seconds % 10;
            displayedSecondsTens = Seconds / 10;
            displayedMinutesUnits = Minutes % 10;
            displayedMinutesTens = Minutes / 10;
            displayedHoursUnits = Hours % 10;
            displayedHoursTens = Hours / 10;
        }

        //rychle "pole" pro ISR
        uint_fast8_t displayedSecondsUnits;
        uint_fast8_t displayedSecondsTens;
        uint_fast8_t displayedMinutesUnits;
        uint_fast8_t displayedMinutesTens;
        uint_fast8_t displayedHoursUnits;
        uint_fast8_t displayedHoursTens;
};

