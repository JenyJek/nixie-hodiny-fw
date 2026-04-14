#pragma once
#include <Arduino.h>
#include <rtc.h>
#include <displayBuffer.h>

extern Rtc rtc;
extern DisplayBuffer displayBuffer;
extern uint32_t autoModeToSecondsTime;
extern uint16_t turnOffAfterRadarTime;
extern bool testSegments;
extern bool displayTemperature;