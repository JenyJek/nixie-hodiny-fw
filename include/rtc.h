#pragma once
#include <Arduino.h>
class rtc
{
    private:
    uint8_t address;
    uint8_t decToBcd(uint8_t decimal);
    uint8_t bcdToDec(uint8_t bcd);
    /* data */
    public:
    signed char intTemperature, intTemperatureDecimal;
    uint8_t minutes, hours, seconds, day, month, year;
    enum dayOfWeek{NAD, SUN, MON, TUE, WED, THU, FRI, SAT}; //NAD: not a day, rtc works by 1-7, not 0-6.
    dayOfWeek dow;

    rtc(uint8_t address);
    void setTime(uint8_t secs, uint8_t mins, uint8_t hrs);
    void setAlm(uint8_t secs, uint8_t mins, uint8_t hrs);
    void setDate(uint8_t day, uint8_t month, uint8_t year, uint8_t dow);
    void enableAlarm();
    void disableAlarm();
    void read();
    bool alarmActive();
    void readTemperature();
    float getTemperature(){
        readTemperature();
        return intTemperature + 0.01f * intTemperatureDecimal;
    }
};


