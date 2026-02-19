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
    uint8_t minutes, hours, seconds, day, month, year;
    enum dayOfWeek{NAD, SUN, MON, TUE, WED, THU, FRI, SAT};
    dayOfWeek dow;

    rtc(uint8_t address);
    void setTime(uint8_t secs, uint8_t mins, uint8_t hrs);
    void setDate(uint8_t day, uint8_t month, uint8_t year, uint8_t dow);
    
    // Alarm2: user-settable, hours:minutes match
    void setAlm(uint8_t mins, uint8_t hrs);
    
    // Alarm1: every second trigger
    void initAlm1();
    
    // Alarm flag getters (also clear the flag when read)
    bool getAlm1FlagTrigger();

    bool getAlm2Flag();
    void enableAlm();
    void disableAlm();
    void clearAlm();
    
    void read();
    float getTemperature();
};


