#pragma once
#include <Arduino.h>
struct DisplayBuffer {
    //storage casu
    uint8_t digits[6]; //HH:MM:SS
    bool forceChange = false;

    
    //nastaveni doutnavek tecek na hodinach, based on bity na uint8_t in 
    //(1bit - leva spodni tecka, 2bit - prava spodni tecka, 3-bit - vrchni tecky)
    void setDots(uint8_t in){
        lowerLeftDot = (in >> 1) & 1;
        lowerRightDot = (in >> 2) & 1;
        upperDots = (in >> 3) & 1;
    }

    //tadyten push je tu jenom kvuli tomu aby se setril cas zpracovani
    void Push(){
        displayedHoursTens = digits[0];
        displayedHoursUnits = digits[1];
        displayedMinutesTens = digits[2];
        displayedMinutesUnits = digits[3];
        displayedSecondsTens = digits[4];
        displayedSecondsUnits = digits[5];
    }

    //rychle "pole" pro ISR
    uint_fast8_t displayedSecondsUnits;
    uint_fast8_t displayedSecondsTens;
    uint_fast8_t displayedMinutesUnits;
    uint_fast8_t displayedMinutesTens;
    uint_fast8_t displayedHoursUnits;
    uint_fast8_t displayedHoursTens;

    uint_fast8_t lowerLeftDot, lowerRightDot, upperDots;
};

extern DisplayBuffer displayBuffer; //globalni buffer pro displej je extern - dostupny vsude, kde je #include displayBuffer.h
