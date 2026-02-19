#include <rtc.h>
#include <Wire.h>

//constructor
rtc::rtc (uint8_t address){
    this->address = address;
    Wire.begin();
}

//nastaveni casu v RTC
void rtc::setTime(uint8_t secs, uint8_t mins, uint8_t hrs){
    Wire.beginTransmission(this->address);
    Wire.write(0x00);//set starting pointer to 0x00
    Wire.write(decToBcd(secs));//seconds in bcd format, msb first, 0xtens, 0xunits
    Wire.write(decToBcd(mins));
    Wire.write(decToBcd(hrs));
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

//nastaveni alarmu A2 - uzivatelem nastavitelny budik
void rtc::setAlm(uint8_t mins, uint8_t hrs){
    Wire.beginTransmission(this->address);
    Wire.write(0x0B);//set pointer to alarm1 registers
    Wire.write(decToBcd(mins));
    Wire.write(decToBcd(hrs));
    Wire.write(0x80); // A2M3 - 1 - trigger on minutes & hours match
    Wire.endTransmission();
    enableAlm();
}

void rtc::enableAlm(){
    Wire.beginTransmission(this->address);
    Wire.write(0x0D);
    Wire.write(0x80);
    Wire.endTransmission();    
}

void rtc::disableAlm(){
    Wire.beginTransmission(this->address);
    Wire.write(0x0D);
    Wire.write(0x00);
    Wire.endTransmission();  
}

void rtc::clearAlm(){
    uint8_t statusReg = getStatusRegister();
    statusReg &= ~0x02; // smazat A2F

    Wire.beginTransmission(this->address);
    Wire.write(0x0F);
    Wire.write(statusReg);
    Wire.endTransmission();
}

//inicializace alarmu A1 - trigger kazdou vterinu
void rtc::initAlm1(){
    Wire.beginTransmission(this->address);
    Wire.write(0x07);//nastaveni offsetu
    Wire.write(0x80); //A1M1 - 1
    Wire.write(0x80); //A1M2 - 1
    Wire.write(0x80); //A1M3 - 1
    Wire.write(0x80); //A1M4 - 1
    Wire.endTransmission();
}

uint8_t rtc::getStatusRegister() {
    Wire.beginTransmission(this->address);
    Wire.write(0x0F);
    Wire.endTransmission();

    Wire.requestFrom(this->address, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

bool rtc::getAlm1FlagTrigger() {
    uint8_t statusReg = getStatusRegister();
    if ((statusReg & 0x01) != 0){
        //reset register
        statusReg &= ~0x01; // smazat A1F

        Wire.beginTransmission(this->address);
        Wire.write(0x0F);
        Wire.write(statusReg);
        Wire.endTransmission();
        return true;
    }
    else{
        return false;
    }
}

bool rtc::getAlm2Flag() {
    return (getStatusRegister() & 0x02) != 0;
}

void rtc::read(){
    Wire.beginTransmission(this->address);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(this->address, (uint8_t)7);
    this->seconds = (Wire.read() & 0x7F);
    this->minutes = Wire.read();
    this->hours = (Wire.read() & 0x3F);
    this->dow = dayOfWeek(Wire.read());
    this->day = Wire.read();
    this->month = Wire.read();
    this->year = Wire.read();
}

float rtc::getTemperature() {
    Wire.beginTransmission(this->address);
    Wire.write(0x11);                 // MSB registr teplotniho cidla
    Wire.endTransmission();

    Wire.requestFrom(this->address, (uint8_t)2); //chceme 2 bytes - samotne cislo se znamenkem (signed) (0x11) a desetina cast LSB (0x12)

    if (Wire.available() < 2) {
        return NAN;  // dojebalo se D:
    }

    int8_t msb = Wire.read(); // se znamenkem (signed)
    uint8_t lsb = Wire.read(); // desetinna cast

    float temperature = msb + ((lsb >> 6) * 0.25f); //desetiny casti jsou 2 bity na 1 - 0.00, 0.25, 0.50, 0.75 pro bity 00, 01, 10, 11

    return temperature;
}


uint8_t rtc::decToBcd(uint8_t decimal){
    return ( (decimal/10*16) + (decimal%10) );
}

uint8_t rtc::bcdToDec(uint8_t bcd){
    return ( (bcd/16*10) + (bcd%16) );
}