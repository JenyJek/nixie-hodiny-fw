#include <melodies.h>

// Individual melodies
const Melody alarmMelodyData = {"1W1V2f2g1u1B2D2E1B1A2c2E3A10X", 65, false};
const Melody okSfxMelodyData = {"1C1E1G1U1X0", 20, true};
const Melody forbiddenSfxMelodyData = {"2C1X2C1X0", 30, true};
const Melody hapticMelodyData = {"1G1U1X0", 15, true};

// Global melodies instance
Melodies melodies;

// Initialize members
void initMelodies() {
    melodies.alarmMelody = alarmMelodyData;
    melodies.okSfxMelody = okSfxMelodyData;
    melodies.forbiddenSfxMelody = forbiddenSfxMelodyData;
    melodies.hapticMelody = hapticMelodyData;
}

