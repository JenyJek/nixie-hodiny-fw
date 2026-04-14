#include <melodies.h>
#include <presetMemory.h>

// Individual melodies
//const Melody alarmMelodyData = {"1W1V2f2g1u1B2D2E1B1A2c2E3A5X0", 65, false};
//const Melody okSfxMelodyData = {"1C1E1G1U1X0", 20, true};
//const Melody forbiddenSfxMelodyData = {"2C1X2C1X0", 30, true};
const Melody hapticMelodyData = {"1G1U1X0", 15, true}; //this ones static, just to make users angry (ima lazy af)

// Global melodies instance
Melodies melodies;

// Initialize members
void Melodies::setup() {
    PresetMemory::almSoundPreset data = presetMemory.getAlmSoundPreset();
    melodies.alarmMelody = data.almMelody;
    melodies.okSfxMelody = data.okSfxMelody;
    melodies.forbiddenSfxMelody = data.errSfxMelody;
    melodies.hapticMelody = hapticMelodyData;
}

