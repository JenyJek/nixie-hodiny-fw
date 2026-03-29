#include <almSound.h>
#include <Arduino.h>
#include <pins.h>
//#include <toneOut.h>

// Frequencies (Hz) for octave 4
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

// Frequencies (Hz) for octave 5
#define NOTE_C5  524
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

// Convert your char encoding to frequency
int almSound::noteToFreq(char note) {
  switch (note) {
    case 'C': return NOTE_C4;
    case 'c': return NOTE_CS4;
    case 'D': return NOTE_D4;
    case 'd': return NOTE_DS4;
    case 'E': return NOTE_E4;
    case 'F': return NOTE_F4;
    case 'f': return NOTE_FS4;
    case 'G': return NOTE_G4;
    case 'g': return NOTE_GS4;
    case 'A': return NOTE_A4;
    case 'a': return NOTE_AS4;
    case 'B': return NOTE_B4;
    case 'U': return NOTE_C5;
    case 'u': return NOTE_CS5;
    case 'V': return NOTE_D5;
    case 'v': return NOTE_DS5;
    case 'W': return NOTE_E5;
    case 'w': return NOTE_F5;
    case 'Y': return NOTE_FS5;
    case 'y': return NOTE_G5;
    case 'Z': return NOTE_GS5;
    case 'z': return NOTE_A5;
    case 'H': return NOTE_AS5;
    case 'h': return NOTE_B5;
    case 'X': return 0; // rest
    default:  return 0;
  }
}

void almSound::proceed(){
    if(accumulatedWaitTime <= 0){
        accumulatedWaitTime = this->currentMelody.melody[current_position] - '0';
        int Outtone = noteToFreq(this->currentMelody.melody[current_position+1]);
        Outtone == 0 ? noTone(PIN_ALM_OUT) : tone(PIN_ALM_OUT, Outtone);
        this->current_position+=2;
        if(this->currentMelody.melody[current_position] == '0'){
            Serial.print("Zero here! | ");
            Serial.println(this->currentMelody.oneShot);
            if(this->currentMelody.oneShot)this->stop();
            else this->current_position = 0;
        }
    }
    else{
        accumulatedWaitTime--;
    }
}

void almSound::stop(){
    this->accumulatedWaitTime = 0;
    this->current_position=0;
    noTone(PIN_ALM_OUT);
    this->run = false;
}

void almSound::loop(){
    if(millis() - this->lastMillis >= this->currentMelody.bpm){
        this->run ? this->proceed() : this->stop();
        this->lastMillis = millis();
    }
}

// Global instance definition
almSound toneMachine;