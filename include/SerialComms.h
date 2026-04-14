#pragma once
#include <Arduino.h>

#define CMD_PFX "AT"
#define MAX_BUF 48

//encoding prikazu na uint32_t
constexpr uint32_t encode3(char a, char b, char c) {
  return ((uint32_t)a << 16) | ((uint32_t)b << 8) | (uint32_t)c;
}
constexpr uint32_t encode3(const char* s) {
  return ((uint32_t)s[0] << 16) | ((uint32_t)s[1] << 8) | (uint32_t)s[2];
}

// Předzpracované příkazy:

// Set Commands
#define SET_CLOCK             0x53434B // "SCK"
#define SET_DATE              0x534454 // "SDT"
#define SET_ALM               0x53414C // "SAL"

// Config Commands
#define CONF_DISPL_TEMP       0x434454 // "CDT"
#define CONF_TEST_SEGMENTS    0x435453 // "CTS"
#define CONF_RADAR_RETURNTIME 0x435252 // "CRR"
#define CONF_MENU_RETURNTIME  0x434D52 // "CMR"

// Touch Commands
#define TOUCH_SET_SAMPLES     0x545341 // "TSA"
#define TOUCH_SET_THRESHOLD   0x545452 // "TTR"
#define TOUCH_SET_ALPHA       0x54414C // "TAL"

// Melody Commands
#define MELODY_SET_ALARM      0x4D414C // "MAL"
#define MELODY_SET_OK         0x4D4F4B // "MOK"
#define MELODY_SET_ERR        0x4D4552 // "MER"

// Display Commands
#define DISPLAY_SLOT_SECONDS  0x445353 // "DSS"
#define DISPLAY_ANIM_UPDATE   0x444155 // "DAU"
#define DISPLAY_SECS_UPDATE   0x445355 // "DSU"
#define DISPLAY_MINS_UPDATE   0x444D55 // "DMU"
#define DISPLAY_DOT_ONTIME    0x444F54 // "DOT"

// Util Commands
#define EXIT_CMD              0x454E44 // "END"
#define SAVE_CMD              0x534156 // "SAV"
#define FACTORY_RESET_CMD     0x465253 // "FRS"

struct SerialLine{
  public:
    enum ErrType {E_UNKNOWN_CMD, E_INVALID_DATA, E_FAILED, E_OVERFLOW};
    void update();
    void setup();
    void answerOk();
  private:
    char buffer[MAX_BUF];
    void throwError(ErrType error);
    void endComms();
    uint8_t getMaxDays(uint8_t M, uint8_t Y);
    void clear();
    bool isValidMelody(char* str);
    uint8_t getDayOfWeek(uint8_t d, uint8_t m, uint8_t y2d);
    void saveToEeprom();
    void resetToDefault();
};

extern SerialLine serialLine;