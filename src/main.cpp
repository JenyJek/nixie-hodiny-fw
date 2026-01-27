#include <Arduino.h>
#include <displayBuffer.h>
#include <displayManager.h>

#define PIN_MH141_A1 1
#define PIN_MH141_B1 2
#define PIN_MH141_C1 3
#define PIN_MH141_D1 4
#define PIN_MH141_A2 1
#define PIN_MH141_B2 2
#define PIN_MH141_C2 3
#define PIN_MH141_D2 4
#define PIN_DIG_1 5
#define PIN_DIG_2 6
#define PIN_DIG_3 7
#define PIN_HV_MOS 8
#define PIN_RADAR 9
#define PIN_TOUCH 10

DisplayBuffer displayBuffer; //actual deklarace globalniho bufferu pro displej

void setup() {
  // setup se spousti pouze jednou, pri spusteni MCU (reset, napajeni apod.)
  Serial.begin(115200); //inicializuj seriovou linku s rychlosti 115200baud

  //nastaveni modu GPIO
  pinMode(PIN_MH141_A1, OUTPUT);
  pinMode(PIN_MH141_B1, OUTPUT);
  pinMode(PIN_MH141_C1, OUTPUT);
  pinMode(PIN_MH141_D1, OUTPUT);

  pinMode(PIN_MH141_A2, OUTPUT);
  pinMode(PIN_MH141_B2, OUTPUT);
  pinMode(PIN_MH141_C2, OUTPUT);
  pinMode(PIN_MH141_D2, OUTPUT);

  pinMode(PIN_DIG_3, OUTPUT);
  pinMode(PIN_DIG_3, OUTPUT);
  pinMode(PIN_DIG_3, OUTPUT);

  pinMode(PIN_HV_MOS, OUTPUT);
  pinMode(PIN_RADAR, INPUT_PULLUP);

  noInterrupts(); // pri nastavovani nutno vypnout vsechny interrupty
  TCCR2A = 0; // timer/counter control register A casovace 2 - cely vynulovat
  TCCR2B = 0; // to same pro TCCR registr B

  TCNT2  = 0; //pocatecni hodnota timer/counter 2 nastavit na 0
  OCR2A = 249; // nastaveni output compare registru na 500Hz pri freq. 8MHz
  //magicka formulka = (16 * 10^6) / (8 * 500 Hz) - 1 (musi byt <0xFF)

  TCCR2B |= (1 << WGM22); // zapnout ctc mod (normalni citac)
  TCCR2B |= (1 << CS21); // nastaveni nasobice 8 a spousteni casovace

  TIMSK2 |= (1 << OCIE2A);  // zapnout funkci timer compare

  interrupts(); //zapnout zpet vsechny interrupty
}

uint64_t lastMillis, lastMillis2, lastMillis3;
bool on;
void loop(){
  display.OnUpdate(); //zavolat update displeje
  if(millis() - lastMillis >= 100){
    //kazdych 100ms
    Serial.print("actual: ");
    Serial.print(display.getSeconds());
    Serial.print(" | in buffer: ");
    Serial.println(displayBuffer.digits[4] * 10 + displayBuffer.digits[5]);
    lastMillis = millis();
  }

  if(millis() - lastMillis2 >= 1000){
    //kazdych 100ms
    display.digits[5]++;
    if(display.digits[5] >= 10){
      display.digits[4]++;
      display.digits[5]=0;
      if(display.digits[4] >= 6){
        display.digits[4]=0;
        display.digits[3]++;
        if(display.digits[3] >= 6){
          display.digits[3]=0;
          display.digits[1]++;
          if(display.digits[0]>=2 && display.digits[1]>=4){
            display.digits[0]=0;
            display.digits[1]=0;
          }
        }
      }
    }
    lastMillis2 = millis();
  }

  if(millis() - lastMillis3 >= 20000){
    //kazdych 100ms
    if(on){
      display.TurnOff();
      on = false;
    }
    else{
      display.TurnOn();
      on = true;
    }

    lastMillis3 = millis();
  }
}


static uint_fast8_t mux_phase;
ISR(TIMER2_COMPA_vect) {
  //interupt service routine, multiplex displeje
  //casovano kazdych 5ms (133Hz obnovovaci frekvence)

  //vypnout anody
  digitalWrite(PIN_DIG_1, LOW);
  digitalWrite(PIN_DIG_2, LOW);
  digitalWrite(PIN_DIG_3, LOW);
  switch (mux_phase){
    case 0:
      mux_phase=1;
      //zobrazujeme na MH74141 A - desiky hodin
      digitalWrite(PIN_MH141_B1, displayBuffer.displayedHoursTens & 0x01);
      digitalWrite(PIN_MH141_C1, displayBuffer.displayedHoursTens & 0x02);
      digitalWrite(PIN_MH141_D1, displayBuffer.displayedHoursTens & 0x04);
      digitalWrite(PIN_MH141_A1, displayBuffer.displayedHoursTens & 0x08);
      //zobrazujeme na MH74141 B - jednotky minut
      digitalWrite(PIN_MH141_A2, displayBuffer.displayedMinutesUnits & 0x01);
      digitalWrite(PIN_MH141_B2, displayBuffer.displayedMinutesUnits & 0x02);
      digitalWrite(PIN_MH141_C2, displayBuffer.displayedMinutesUnits & 0x04);
      digitalWrite(PIN_MH141_D2, displayBuffer.displayedMinutesUnits & 0x08);
      //zapnout anody 
      digitalWrite(PIN_DIG_1, HIGH);
    break;
    case 1: //faze 1, zobrazujeme jednotky a desitky hodin
      mux_phase=2;
      //zobrazujeme na MH74141 A - jednotky hodin
      digitalWrite(PIN_MH141_B1, displayBuffer.displayedHoursUnits & 0x01);
      digitalWrite(PIN_MH141_C1, displayBuffer.displayedHoursUnits & 0x02);
      digitalWrite(PIN_MH141_D1, displayBuffer.displayedHoursUnits & 0x04);
      digitalWrite(PIN_MH141_A1, displayBuffer.displayedHoursUnits & 0x08);
      //zobrazujeme na MH74141 B - jednotky sekund
      digitalWrite(PIN_MH141_B2, displayBuffer.displayedSecondsUnits & 0x01);
      digitalWrite(PIN_MH141_C2, displayBuffer.displayedSecondsUnits & 0x02);
      digitalWrite(PIN_MH141_D2, displayBuffer.displayedSecondsUnits & 0x04);
      digitalWrite(PIN_MH141_A2, displayBuffer.displayedSecondsUnits & 0x08);
      //zapnout anody 
      digitalWrite(PIN_DIG_2, HIGH);
    break;
    case 2: //faze 2, zobrazujeme jednotky a desitky minut
      mux_phase=0;
      //zobrazujeme na MH74141 A - desiky minut
      digitalWrite(PIN_MH141_B1, displayBuffer.displayedMinutesTens & 0x01);
      digitalWrite(PIN_MH141_C1, displayBuffer.displayedMinutesTens & 0x02);
      digitalWrite(PIN_MH141_D1, displayBuffer.displayedMinutesTens & 0x04);
      digitalWrite(PIN_MH141_A1, displayBuffer.displayedMinutesTens & 0x08);
      //zobrazujeme na MH74141 B - desitky sekund
      digitalWrite(PIN_MH141_A2, displayBuffer.displayedSecondsTens & 0x01);
      digitalWrite(PIN_MH141_B2, displayBuffer.displayedSecondsTens & 0x02);
      digitalWrite(PIN_MH141_C2, displayBuffer.displayedSecondsTens & 0x04);
      digitalWrite(PIN_MH141_D2, displayBuffer.displayedSecondsTens & 0x08);
      //zapnout anody 
      digitalWrite(PIN_DIG_3, HIGH);
    break;
    default:
      mux_phase = 0;
    break;
  }
}