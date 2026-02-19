#pragma once
#include <Arduino.h>
class rtc
{
    private:
    uint8_t address;
    uint8_t decToBcd(uint8_t decimal);
    uint8_t bcdToDec(uint8_t bcd);
    uint8_t getStatusRegister();
    
    public:
    //funny
    uint8_t minutes, hours, seconds, day, month, year;
    enum dayOfWeek{NAD, SUN, MON, TUE, WED, THU, FRI, SAT}; //NAD: not a day, rtc funguje na 1-7, ne 0-6.
    dayOfWeek dow;

    //konstruktor
    rtc(uint8_t address);

    //nastaveni rtc
    void setTime(uint8_t secs, uint8_t mins, uint8_t hrs);
    void setDate(uint8_t day, uint8_t month, uint8_t year, uint8_t dow);
    
    // Alarm2: nastavitelny userem - minuty&hodiny match
    void setAlm(uint8_t mins, uint8_t hrs);
    
    // Alarm1: trigger kazdou vterinu
    void initAlm1();
    
    // Alarm1 flag getr - maze se sam pri cteni
    bool getAlm1FlagTrigger();

    // Alarm2 - user alarm - tady uz je nutnuy flag mazat rucne, pres clearAlm()
    bool getAlm2Flag();
    void clearAlm();
    
    // cteni z rtc
    void read();
    float getTemperature();
};


