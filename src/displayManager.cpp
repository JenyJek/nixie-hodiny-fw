/*
* the display manager handles animations, cathode anti-poisoning and HV enabling/disabling
*
*/

#include <Arduino.h>
#include <displayBuffer.h>
#include <displayManager.h>

Display display;

void Display::stepAnimation(){
    switch (this->currentAnimState)
    {
    case STATIC:
        //if seconds value changed, slot machine changed positions (seconds units slotting may be disabled in settings)
        //if minutes or hours change, slot every position except seconds XX:XX:--
        break;
    case FLY_IN:
        switch(animStep){
            case 0://push empty chars into displayBuffer
                for(uint8_t i = 0; i < 6; i++){
                    displayBuffer.digits[i] = 0xF; //empty char
                }
                //enable HV power supply
                animStep++;
                this->animRunning = true;
            break;
            case 1: //actual time 12:34:56 - display  6-:--:--
                displayBuffer.digits[0] = this->digits[5];
                animStep++;
            break;
            case 2: //actual time 12:34:56 - display  56:--:--
                displayBuffer.digits[0] = this->digits[4];
                displayBuffer.digits[1] = this->digits[5];
                animStep++;
            break;
            case 3: //actual time 12:34:56 - display  45:6-:--
                displayBuffer.digits[0] = this->digits[3];
                displayBuffer.digits[1] = this->digits[4];
                displayBuffer.digits[2] = this->digits[5];
                animStep++;
            break;
            case 4: //actual time 12:34:56 - display  34:56:--
                displayBuffer.digits[0] = this->digits[2];
                displayBuffer.digits[1] = this->digits[3];
                displayBuffer.digits[2] = this->digits[4];
                displayBuffer.digits[3] = this->digits[5];
                animStep++;
            break;
            case 5: //actual time 12:34:56 - display  23:45:6-
                displayBuffer.digits[0] = this->digits[1];
                displayBuffer.digits[1] = this->digits[2];
                displayBuffer.digits[2] = this->digits[3];
                displayBuffer.digits[3] = this->digits[4];
                displayBuffer.digits[4] = this->digits[5];
                animStep++;
            break;
            case 6: //actual time 12:34:56 - display  12:34:56
                displayBuffer.digits[0] = this->digits[0];
                displayBuffer.digits[1] = this->digits[1];
                displayBuffer.digits[2] = this->digits[2];
                displayBuffer.digits[3] = this->digits[3];
                displayBuffer.digits[4] = this->digits[4];
                displayBuffer.digits[5] = this->digits[5];
                this->currentAnimState = STATIC;
                this->animRunning = false;
                animStep = 0;
            break;
        }
        break;
    case FLY_OUT:
        switch(animStep){
            case 0:
                displayBuffer.digits[0] = this->digits[0];
                displayBuffer.digits[1] = this->digits[1];
                displayBuffer.digits[2] = this->digits[2];
                displayBuffer.digits[3] = this->digits[3];
                displayBuffer.digits[4] = this->digits[4];
                displayBuffer.digits[5] = this->digits[5];
                animStep++;
                this->animRunning = true;
            break;
            case 1://actual time 12:34:56 - display -1:23:45
                displayBuffer.digits[0] = 0xF;
                displayBuffer.digits[1] = this->digits[0];
                displayBuffer.digits[2] = this->digits[1];
                displayBuffer.digits[3] = this->digits[2];
                displayBuffer.digits[4] = this->digits[3];
                displayBuffer.digits[5] = this->digits[4];
                animStep++;
            break;
            case 2: //actual time 12:34:56 - display  --:12:34
                displayBuffer.digits[1] = 0xF;
                displayBuffer.digits[2] = this->digits[0];
                displayBuffer.digits[3] = this->digits[1];
                displayBuffer.digits[4] = this->digits[2];
                displayBuffer.digits[5] = this->digits[3];
                animStep++;
            break;
            case 3: //actual time 12:34:56 - display  --:-1:23
                displayBuffer.digits[2] = 0xF;
                displayBuffer.digits[3] = this->digits[0];
                displayBuffer.digits[4] = this->digits[1];
                displayBuffer.digits[5] = this->digits[2];
                animStep++;
            break;
            case 4: //actual time 12:34:56 - display  --:--:12
                displayBuffer.digits[3] = 0xF;
                displayBuffer.digits[4] = this->digits[0];
                displayBuffer.digits[5] = this->digits[1];
                animStep++;
            break;
            case 5: //actual time 12:34:56 - display  --:--:-1
                displayBuffer.digits[4] = 0xF;
                displayBuffer.digits[5] = this->digits[0];
                animStep++;
            break;
            case 6: //actual time 12:34:56 - display  --:--:--
                displayBuffer.digits[5] = 0xF;
                animStep=0;
                //disable HV power supply
                this->currentAnimState = OFF;
                this->animRunning = false;
            break;
        }
        break;
    default:
        break;
    }
    displayBuffer.Push();
}

