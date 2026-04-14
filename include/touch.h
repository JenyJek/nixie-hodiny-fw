#pragma once
#include <Arduino.h>

struct Touch{
    private:
        uint8_t ADCChannel;
        long baseline;
        bool baselineInit;
        bool prevTouched;
    public:
    int32_t samples;
        int threshold;
        int alpha;
        bool touched;
        int32_t readVal;
        void Read();
        void setup(uint8_t adcChannel);
};
extern Touch touch;