#pragma once
#include <Arduino.h>
struct DisplayBuffer {
    //storage casu
    uint8_t digits[6]; //HH:MM:SS
    bool forceChange = false;

    
    //nastaveni doutnavek tecek na hodinach, based on bity na uint8_t in 
    //(1bit - leva spodni tecka, 2bit - prava spodni tecka, 3-bit - vrchni tecky)
    void setDots(uint8_t in){
        lowerLeftDot = in & 0x01;
        lowerRightDot = in & 0x02;
        upperDots = in & 0x04;
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
    volatile uint_fast8_t displayedSecondsUnits;
    volatile uint_fast8_t displayedSecondsTens;
    volatile uint_fast8_t displayedMinutesUnits;
    volatile uint_fast8_t displayedMinutesTens;
    volatile uint_fast8_t displayedHoursUnits;
    volatile uint_fast8_t displayedHoursTens;

    volatile uint_fast8_t lowerLeftDot, lowerRightDot, upperDots;
};

extern DisplayBuffer displayBuffer; //globalni buffer pro displej je extern - dostupny vsude, kde je #include displayBuffer.h
