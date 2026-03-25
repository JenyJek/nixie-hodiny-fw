#include <Arduino.h>
#include <displayBuffer.h>
#include <displayManager.h>
#include <rtc.h>
#include <Wire.h>
#include <pins.h>
#include <touch.h>
#include <almSound.h>

DisplayBuffer displayBuffer; //actual deklarace globalniho bufferu pro displej
Rtc rtc(0x68); //inicializace RTC s I2C adresou 0x68

enum DMODE {MODE_TIME, MODE_DATE, MODE_TEMP, MODE_ALM_PRST, MODE_ALM_RUN};
DMODE displaying;

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

  pinMode(PIN_DIG_1, OUTPUT);
  pinMode(PIN_DIG_2, OUTPUT);
  pinMode(PIN_DIG_3, OUTPUT);

  pinMode(PIN_HV_MOS, OUTPUT);
  pinMode(PIN_RADAR, INPUT_PULLUP);

  pinMode(PIN_ALM_OUT, OUTPUT);

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

  touch.Setup(PIN_TOUCH, 100, 40, 8); //nastavenicko captouch s defaultnima hodnotama

  display.digits[0] = 1;
  display.digits[1] = 2;
  display.digits[2] = 3;
  display.digits[3] = 4;
  display.digits[4] = 5;
  display.digits[5] = 6;
  
  display.TurnOff();
  display.OnUpdate();
  Wire.begin();
  rtc.initAlm1();
  Serial.println("startup done");
  displaying = MODE_TIME;
  display.TurnOn();
}

uint64_t lastMillis, lastMillis2, lastMillis3;
bool on;
void loop(){
  display.OnUpdate(); //zavolat update displeje
  if(millis() - lastMillis >= 100){
    //kazdych 100ms
    Serial.print("actual: ");
    Serial.print(display.getHours());
    Serial.print(":");
    Serial.print(display.getMinutes());
    Serial.print(":");
    Serial.print(display.getSeconds());
    Serial.print(" | in buffer: ");
    Serial.print(displayBuffer.digits[0] == 0xF ?  '-' : char(displayBuffer.digits[0] + 48));
    Serial.print(displayBuffer.digits[1] == 0xF ?  '-' : char(displayBuffer.digits[1] + 48));
    Serial.print(displayBuffer.upperDots ? (displayBuffer.lowerLeftDot ? ":" : "-") : (displayBuffer.lowerLeftDot ? "." : " "));
    Serial.print(displayBuffer.digits[2] == 0xF ?  '-' : char(displayBuffer.digits[2] + 48));
    Serial.print(displayBuffer.digits[3] == 0xF ?  '-' : char(displayBuffer.digits[3] + 48));
    Serial.print(displayBuffer.upperDots ? (displayBuffer.lowerRightDot ? ":" : "-") : (displayBuffer.lowerRightDot ? "." : " "));
    Serial.print(displayBuffer.digits[4] == 0xF ?  '-' : char(displayBuffer.digits[4] + 48));
    Serial.println(displayBuffer.digits[5] == 0xF ?  '-' : char(displayBuffer.digits[5] + 48));
    lastMillis = millis();
  }

  if(millis() - lastMillis2 >= 50){
    if(rtc.getAlm1FlagTrigger()){
      // on alm1 trg flag
      if(displaying = MODE_TIME){
        display.SetDots(display.TIME);
        rtc.read();
        //push from rtc to display
        display.fillDigits(rtc.hours, rtc.minutes, rtc.seconds);
        if(rtc.seconds == 0){
          displayBuffer.forceChange = true;
        }
      }
      else if(displaying = MODE_DATE){
        display.SetDots(display.DATE);
        rtc.read();
        display.fillDigits(rtc.day, rtc.month, rtc.year);
      }
      else if(displaying = MODE_TEMP){
        display.SetDots(display.TEMP);
        rtc.readTemp();
        display.fillDigits(0xFF, rtc.getTemp(), rtc.getTempDecimalPart());
      }
      else if(displaying = MODE_ALM_PRST){
        display.SetDots(display.ALARM_SET);
        display.fillDigits(rtc.almhrs, rtc.almmins, 0xFF);
      }
      else if(displaying = MODE_ALM_RUN){
        display.SetDots(display.ALARM_RUN);
        rtc.read();
        display.fillDigits(rtc.almhrs, rtc.almmins, rtc.seconds);
      }
    }
    lastMillis2 = millis();
  }

  if(millis() - lastMillis3 >=125 && rtc.getAlm2Flag()){
    //periodicky update pro melodii, tony se generuji pres interni PWM PIO
    toneMachine.proceed();
  }

  if(millis() - lastMillis3 >= 25){
    //kazdych 25ms
    touch.Read();

    //pro DEBUG
    if(touch.touched) Serial.println("dotyq");

    lastMillis3 = millis();
  }
}

// jeste treba dodelat spousteni tecek
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
      //zobrazeni tecek #1 - leva spodni tecka
      digitalWrite(PIN_DOT, displayBuffer.lowerLeftDot);
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
      //zobrazeni tecek #2 - prava spodni tecka
      digitalWrite(PIN_DOT, displayBuffer.lowerRightDot);
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
      //zobrazeni tecek #3 - obe horni tecky
      digitalWrite(PIN_DOT, displayBuffer.upperDots);
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