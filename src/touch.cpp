#include <Arduino.h>
#include <touch.h>

Touch touch;

void Touch::Read()
{
    long _value = 0;
    int _samples = samples > 0 ? samples : 1;
    for (int _counter = 0; _counter < _samples; _counter++) {
        pinMode(ADCChannel, INPUT_PULLUP);

        // connect the ADC input and the internal sample-and-hold capacitor
        // to ground to discharge it (mirror of ADCTouch non-Tiny branch)
        ADMUX |= 0b11111;

        // start conversion to allow discharge
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));

        pinMode(ADCChannel, INPUT);
        _value += analogRead(ADCChannel);
    }

    readVal = _value / _samples;

    long val = readVal;
    if (!baselineInit) {
        baseline = val;
        baselineInit = true;
        prevTouched = false;
        this->touched=false;
    }

    if (!prevTouched) {
        if (val > baseline + threshold) {
            prevTouched = true;
            this->touched=true;
        }
        // adapt baseline slowly when not touched
        baseline = (baseline * (alpha - 1) + val) / alpha;
        this->touched=false;
    } else {
        // currently touched: require a smaller value to clear (hysteresis)
        if (val < baseline + threshold / 2) {
            prevTouched = false;
            // reinitialize baseline to current value for faster recovery
            baseline = val;
            this->touched=false;
        }
        this->touched=true;
    }
}