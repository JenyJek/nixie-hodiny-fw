#pragma once
#include <Arduino.h>

struct PresetMemory{
    private:
    public:
    // pro displayBuffer
        struct displayBufferPreset
        {
            bool forceChange;
        };
        void pushDisplayBufferPreset(displayBufferPreset val);
        displayBufferPreset getDisplayBufferPreset();
    // pro displayManager
        struct displayManagerPreset{
            bool slotSecondsUnits;
            uint8_t animUpdateInterval;
            uint8_t rotateSecondsInterval;
            uint8_t rotateMinutesHoursInterval;
            uint8_t doubleDotOnTime;
        };
        void pushDisplayManagerPreset(displayManagerPreset val);
        displayManagerPreset getDisplayManagerPreset();
    // pro touch
        struct touchPreset
        {
            uint8_t adcChannel;
            uint16_t samples;
            int treshold;
            int alpha = 8;
        };
        void pushTouchPreset(touchPreset val);
        touchPreset getTouchPreset();
    // pro almSound
        struct almSoundPreset{
            char melody[32];
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