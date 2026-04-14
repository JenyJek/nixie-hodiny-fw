/*
* the display manager handles animations, cathode anti-poisoning and HV enabling/disabling
*/

#include <Arduino.h>
#include <displayBuffer.h>
#include <displayManager.h>
#include <pins.h>
#include <presetMemory.h>

Display display;

void Display::stepAnimation(){
    switch (this->currentAnimState) {
    case FLY_IN:
        switch(animStep){
            case 0://nasypat prazdne characters do bufferu displeje
                for(uint8_t i = 0; i < 6; i++){
                    displayBuffer.digits[i] = 0xF; //0xF = 0b1111 = zadny vystup aktivni (viz datasheet MH74141)
                }
                //zapnut HV (jinak uvidime prdlajs)
                digitalWrite(PIN_HV_MOS, HIGH);
                display.isOn = true;
                animStep++;
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
                animStep = 0;
            break;
        }
        break;
    case FLY_OUT:
        switch(animStep){
            case 0:
                for(uint8_t i = 0; i < 6; i++){
                    //pro jistotu
                    displayBuffer.digits[i] = this->digits[i];
                }
                animStep++;
            break;
            case 1://actual time 12:34:56 - display -1:23:45
                displayBuffer.digits[0] = 0xF; //postupne mazat posledni cislici a posouvat udaj vpravo
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
                //vypni HV (setrime energii)
                digitalWrite(PIN_HV_MOS, LOW);
                display.isOn = false;
                this->currentAnimState = OFF;
            break;
        }
        break;
    default:
        //nerob nic
        break;
    }
    displayBuffer.Push();
}

void Display::rotateSeconds(){
    //jednotky sekund jsou [5]
    int8_t bufferSecs = displayBuffer.digits[5]; //musi byt signed (chceme aby 0 -> -1 -> 9)
    if(this->digits[5] != bufferSecs){ //pokud actual jednotky sekund nesedi s bufferem
        if(!slotSecondsUnits){ //pokud nechceme tocit s jednotkama sekund
            displayBuffer.digits[5] = this->digits[5]; //tak je proste nasolime rovnou a muzeme se dloubat v nose
        }
        else{
            bufferSecs--;
            if(bufferSecs < 0) bufferSecs = this->slotToInvisible ? 10 : 9;
            displayBuffer.digits[5] = bufferSecs; //vratit hodnotu do realneho bufferu
        }
    }
    //desitky sekund jsou [4]
    bufferSecs = displayBuffer.digits[4]; //vypujcime si hodnotu desitek sekund
    if(this->digits[4] != bufferSecs){ //pokud actual desitky sekund nesedi s bufferem
        bufferSecs--;
        if(bufferSecs < 0) bufferSecs = this->slotToInvisible ? 10 : 9;
        displayBuffer.digits[4] = bufferSecs; //vratit hodnotu do realneho bufferu
    } 
    displayBuffer.Push();//nasypat z bufferu na realne vystupy
}

void Display::rotateMinutesHours(){
    bool forceChange = displayBuffer.forceChange;
    //jednotky minut jsou [3]
    int8_t buffer = displayBuffer.digits[3]; //vypujcime si hodnotu jednotek minut
    if(forceChange){ //force zmena hodnoty
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.forceChange = false; //zamerne nemenime hodnotu lokalniho forceChange, jinak by to fungovalo jenom pro jednu digit
    }
    if(this->digits[3] != buffer){ //pokud actual jednotky minut nesedi s bufferem
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.digits[3] = buffer; //vratit hodnotu do realneho bufferu
    }
    //desitky minut jsou [2]
    buffer = displayBuffer.digits[2]; //vypujcime si hodnotu desitek minut
    if(forceChange){ //force zmena hodnoty
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.forceChange = false; //zamerne nemenime hodnotu lokalniho forceChange, jinak by to fungovalo jenom pro jednu digit
    }
    if(this->digits[2] != buffer){ //pokud actual desitky minut nesedi s bufferem
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.digits[2] = buffer; //vratit hodnotu do realneho bufferu
    }
    //jednotky hodin jsou [1]
    buffer = displayBuffer.digits[1]; //vypujcime si hodnotu jednotek hodin
    if(forceChange){ //force zmena hodnoty
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.forceChange = false; //zamerne nemenime hodnotu lokalniho forceChange, jinak by to fungovalo jenom pro jednu digit
    }
    if(this->digits[1] != buffer){ //pokud actual jednotky hodin nesedi s bufferem
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.digits[1] = buffer; //vratit hodnotu do realneho bufferu
    }
    //desitky hodin jsou [0]
    buffer = displayBuffer.digits[0]; //vypujcime si hodnotu desitek hodin
    if(forceChange){ //force zmena hodnoty
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.forceChange = false; //zamerne nemenime hodnotu lokalniho forceChange, jinak by to fungovalo jenom pro jednu digit
    }
    if(this->digits[0] != buffer){ //pokud actual desitky hodin nesedi s bufferem
        buffer--;
        if(buffer < 0) buffer = this->slotToInvisible ? 10 : 9;
        displayBuffer.digits[0] = buffer; //vratit hodnotu do realneho bufferu
    }
    displayBuffer.Push();//nasypat z bufferu na realne vystupy
}

uint64_t lastAnimationMillis, lastRotateSecondsMillis, lastRotateMinutesHoursMillis, lastDoubleDotOnMillis;
void Display::OnUpdate(){
    uint64_t currentMillis = millis(); 
    if(this->currentAnimState == STATIC){ //pokud nebezi animace, muzeme smele tocit cislicema
        if(currentMillis - lastRotateSecondsMillis >= this->rotateSecondsInterval){
            this->rotateSeconds();
            lastRotateSecondsMillis = currentMillis;
        }
        if(currentMillis - lastRotateMinutesHoursMillis >= this->rotateMinutesHoursInterval){
            this->rotateMinutesHours();
            lastRotateMinutesHoursMillis = currentMillis;
        }
    }
    else if(currentMillis - lastAnimationMillis >= this->animUpdateInterval){
        this->stepAnimation();
        lastAnimationMillis = currentMillis;
    }

    if(this->currentMode == TIME || this->currentMode == ALARM_RUN){
        if(currentMillis - lastDoubleDotOnMillis >= this->doubleDotOnTime){
            this->SetDots(NONE);
        }
    }else if(this->currentMode == NONE){
        lastDoubleDotOnMillis = currentMillis;
    }
}

void Display::setup(){
    PresetMemory::displayManagerPreset data = presetMemory.getDisplayManagerPreset();
    animUpdateInterval = data.animUpdateInterval;
    rotateSecondsInterval = data.rotateSecondsInterval;
    rotateMinutesHoursInterval = data.rotateMinutesHoursInterval;
    doubleDotOnTime = data.doubleDotOnTime;
}