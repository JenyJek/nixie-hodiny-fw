#include <rtc.h>
#include <Wire.h>

//constructor
rtc::rtc (uint8_t address){
    this->address = address;
    Wire.begin();
}

void rtc::setTime(uint8_t secs, uint8_t mins, uint8_t hrs){
    Wire.beginTransmission(this->address);
    Wire.write(0x00);//set starting pointer to 0x00
    Wire.write(decToBcd(secs));//seconds in bcd format, msb first, 0xtens, 0xunits
    Wire.write(decToBcd(mins));
    Wire.write(decToBcd(hrs));
    Wire.endTransmission();
}

void rtc::setAlm(uint8_t secs, uint8_t mins, uint8_t hrs){
    Wire.beginTransmission(this->address);
    Wire.write(0x07);//set starting pointer to 0x07
    Wire.write(decToBcd(secs));//seconds in bcd format, msb first, 0xtens, 0xunits
    Wire.write(decToBcd(mins));
    Wire.write(decToBcd(hrs));
    Wire.write(0x80); //need to enable A1M4 (msb) - trigger ALMIRQ when secs, mins hours match
    Wire.endTransmission();
}

void rtc::setDate(uint8_t day, uint8_t month, uint8_t year, uint8_t dow){
    Wire.beginTransmission(this->address);
    Wire.write(0x03);//set starting pointer to 0x03
    Wire.write(decToBcd(dow));//seconds in bcd format, msb first, 0xtens, 0xunits
    Wire.write(decToBcd(day));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();
}

void rtc::enableAlarm(){
    Wire.beginTransmission(this->address);
    Wire.write(0x0E);
    Wire.write(0x02);
    Wire.endTransmission();
}

void rtc::disableAlarm(){
    Wire.beginTransmission(this->address);
    Wire.write(0x0E);
    Wire.write(0x00);
    Wire.endTransmission();
}

bool rtc::alarmActive(){
    Wire.beginTransmission(this->address);
    Wire.write(0x0F);
    Wire.endTransmission();
    Wire.requestFrom(this->address, 1);
    return Wire.read() == 0x01;
}

void rtc::read(){
    Wire.beginTransmission(this->address);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(this->address, 7);
    this->seconds = (Wire.read() & 0x7F);
    this->minutes = Wire.read();
    this->hours = (Wire.read() & 0x3F);
    this->dow = dayOfWeek(Wire.read());
    this->day = Wire.read();
    this->month = Wire.read();
    this->year = Wire.read();
}

uint8_t rtc::decToBcd(uint8_t decimal){
    return ( (decimal/10*16) + (decimal%10) );
}

uint8_t rtc::bcdToDec(uint8_t bcd){
    return ( (bcd/16*10) + (bcd%16) );
}