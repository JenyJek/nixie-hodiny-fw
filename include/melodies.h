#pragma once
#include <Arduino.h>

struct Melody {
    const char* melody;
    uint8_t bpm;
    Melody() : melody(""), bpm(0) {}
    Melody(const char* m, uint8_t b) : melody(m), bpm(b) {}
};

struct Melodies{
    public:
    Melody alarmMelody;
    Melody okSfxMelody;
    Melody forbiddenSfxMelody;
};

extern Melodies melodies;

void initMelodies();
