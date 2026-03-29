#include <melodies.h>

// Individual melodies
const Melody alarmMelodyData = {"1W1V2f2g1u1B2D2E1B1A2c2E3A1X0", 65};
const Melody okSfxMelodyData = {"2C1X1C1X", 200};
const Melody forbiddenSfxMelodyData = {"2C1X1C1X", 200};

// Global melodies instance
Melodies melodies;

// Initialize members
void initMelodies() {
    melodies.alarmMelody = alarmMelodyData;
    melodies.okSfxMelody = okSfxMelodyData;
    melodies.forbiddenSfxMelody = forbiddenSfxMelodyData;
}

