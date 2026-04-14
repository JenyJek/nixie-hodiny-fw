#pragma once
#include <Arduino.h>

#include <melodies.h>

struct PresetMemory{
    private:
    public:
    //pro main
        struct mainConfigManagerPreset{
            uint16_t autoModeToSecondsTime; //deft: 10000
            uint16_t turnOffAfterRadarTime; //deft: 2500
            bool testSegments; //deft: false
            bool displayTemperature; //deft true
        };
        void pushMainConfigManagerPreset(mainConfigManagerPreset val);
        mainConfigManagerPreset getMainConfigManagerPreset();
    // pro displayManager
        struct displayManagerPreset{
            bool slotSecondsUnits; //deft false
            uint8_t animUpdateInterval; //deft 150
            uint8_t rotateSecondsInterval; //deft 75
            uint8_t rotateMinutesHoursInterval; //deft 75
            uint8_t doubleDotOnTime; // deft 250
        };
        void pushDisplayManagerPreset(displayManagerPreset val);
        displayManagerPreset getDisplayManagerPreset();
    // pro touch
        struct touchPreset
        {
            uint16_t samples; //deft 100
            int treshold; //deft 40
            int alpha; //deft 8
        };
        void pushTouchPreset(touchPreset val);
        touchPreset getTouchPreset();
    // pro almSound
        struct almSoundPreset{
            Melody almMelody;//deft {"1W1V2f2g1u1B2D2E1B1A2c2E3A5X0", 65, false};
            Melody okSfxMelody;//deft {"1C1E1G1U1X0", 20, true};
            Melody errSfxMelody;//deft {"2C1X2C1X0", 30, true};
        };
        void pushAlmSoundPreset(almSoundPreset val);
        almSoundPreset getAlmSoundPreset();
};
/*
*
* DATOVA STRUKTURA EEPROMKY:
* 1kb = 128bytes
*
*/
extern PresetMemory presetMemory;