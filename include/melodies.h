#pragma once
#include <Arduino.h>

struct Melody {
    const char* melody;
    uint8_t bpm;
    bool oneShot;
    Melody() : melody(""), bpm(0), oneShot(false){}
    Melody(const char* m, uint8_t b, bool o) : melody(m), bpm(b), oneShot(o){}
};

struct Melodies{
    public:
    void setup();
    Melody alarmMelody;
    Melody okSfxMelody;
    Melody forbiddenSfxMelody;
    Melody hapticMelody;
};

extern Melodies melodies;


