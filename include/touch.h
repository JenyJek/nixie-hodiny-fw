#pragma once
#include <Arduino.h>

struct Touch{
    private:
        uint8_t ADCChannel;
        int32_t samples;
        int threshold;
        int alpha;
        long baseline;
        bool baselineInit;
        bool prevTouched;
    public:
        bool touched;
        int32_t readVal;
        void Read();
        void Setup(uint8_t adcChannel, int32_t samples, int threshold = 40, int alpha = 8) {
            this->ADCChannel = adcChannel;
            this->samples = samples;
            this->threshold = threshold;
            this->alpha = alpha;
            this->baseline = 0;
            this->baselineInit = false;
            this->prevTouched = false;
        }
};
extern Touch touch;