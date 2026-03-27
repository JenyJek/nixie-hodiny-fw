#include <Arduino.h>
#include <presetMemory.h>
#include <EEPROM.h>

// EEPROM layout offsets
static constexpr int EEPROM_ADDR_DBUF_PRST = 0;
static constexpr int EEPROM_ADDR_DISPLAY_MANAGER = EEPROM_ADDR_DBUF_PRST + sizeof(PresetMemory::displayBufferPreset);
static constexpr int EEPROM_ADDR_TOUCH = EEPROM_ADDR_DISPLAY_MANAGER + sizeof(PresetMemory::displayManagerPreset);
static constexpr int EEPROM_ADDR_ALM_SOUND = EEPROM_ADDR_TOUCH + sizeof(PresetMemory::touchPreset);

PresetMemory presetMemory;

void PresetMemory::pushDisplayBufferPreset (displayBufferPreset val) {
    EEPROM.put(EEPROM_ADDR_DBUF_PRST, val);
}

PresetMemory::displayBufferPreset PresetMemory::getDisplayBufferPreset () {
    displayBufferPreset val;
    EEPROM.get(EEPROM_ADDR_DBUF_PRST, val);
    return val;
}

void PresetMemory::pushDisplayManagerPreset(displayManagerPreset val) {
    EEPROM.put(EEPROM_ADDR_DISPLAY_MANAGER, val);
}

PresetMemory::displayManagerPreset PresetMemory::getDisplayManagerPreset() {
    displayManagerPreset val;
    EEPROM.get(EEPROM_ADDR_DISPLAY_MANAGER, val);
    return val;
}

void PresetMemory::pushTouchPreset(touchPreset val) {
    EEPROM.put(EEPROM_ADDR_TOUCH, val);
}

PresetMemory::touchPreset PresetMemory::getTouchPreset() {
    touchPreset val;
    EEPROM.get(EEPROM_ADDR_TOUCH, val);
    return val;
}

void PresetMemory::pushAlmSoundPreset(almSoundPreset val) {
    EEPROM.put(EEPROM_ADDR_ALM_SOUND, val);
}

PresetMemory::almSoundPreset PresetMemory::getAlmSoundPreset() {
    almSoundPreset val;
    EEPROM.get(EEPROM_ADDR_ALM_SOUND, val);
    return val;
}
