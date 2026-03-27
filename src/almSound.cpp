#include <almSound.h>
#include <Arduino.h>
#include <pins.h>

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
    case 'X': return 0; // rest
    default:  return 0;
  }
}

void almSound::proceed(){
    if(accumulatedWaitTime <= 0){
        this->stopped = true;
        accumulatedWaitTime = this->melody[current_position];
        tone(PIN_ALM_OUT, noteToFreq(this->melody[current_position+1]), this->melody[current_position]*120);
        this->current_position+=2;
        if(this->melody[current_position] == 0) current_position=0;
    }
    else{
        accumulatedWaitTime--;
    }    
}

void almSound::stop(){
    if(!stopped){
        accumulatedWaitTime = 0;
        current_position=0;
        noTone(PIN_ALM_OUT);
    }
}