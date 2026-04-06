#include <Arduino.h>
#include <displayBuffer.h>
#include <displayManager.h>
#include <rtc.h>
#include <Wire.h>
#include <pins.h>
#include <touch.h>
#include <almSound.h>
#include <melodies.h>

DisplayBuffer displayBuffer; //actual deklarace globalniho bufferu pro displej
Rtc rtc(0x68); //inicializace RTC s I2C adresou 0x68

enum DMODE {MODE_TIME, MODE_DATE, MODE_TEMP, MODE_ALM_PRST, MODE_ALM_RUN};
DMODE displaying;

//nastavenicka tady
const unsigned int autoModeToSecondsTime = 10000;


void testAllSegments();

void setup() {
  // setup se spousti pouze jednou, pri spusteni MCU (reset, napajeni apod.)
  Serial.begin(115200); //inicializuj seriovou linku s rychlosti 115200baud
  initMelodies(); //inicializace melodii

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
  TCCR1A = 0; // timer/counter control register A casovace 1 - cely vynulovat
  TCCR1B = 0; // to same pro TCCR registr B
  TCNT1  = 0; //pocatecni hodnota timer/counter 1 nastavit na 0
  OCR1A = 249; // nastaveni output compare registru na 500Hz pri freq. 16MHz
  //magicka formulka = (16 * 10^6) / (8 * 500 Hz) - 1 (musi byt <0xFFFF)
  TCCR1B |= (1 << WGM12); // zapnout ctc mod (normalni citac)
  TCCR1B |= (1 << CS11); // nastaveni nasobice 8 a spousteni casovace
  TIMSK1 |= (1 << OCIE1A);  // zapnout funkci timer compare
  interrupts(); //zapnout zpet vsechny interrupty

  touch.Setup(PIN_TOUCH, 100, 40, 8); //nastavenicko captouch s defaultnima hodnotama

  for(uint8_t digit : displayBuffer.digits){
    displayBuffer.digits[digit] = 0;
  }
    
  display.TurnOff();
  display.OnUpdate();
  Wire.begin();
  rtc.initAlm1();
  Serial.println("startup done");
  displaying = MODE_TIME;
  display.TurnOn();
  toneMachine.currentMelody = melodies.okSfxMelody;
  testAllSegments();
}

uint64_t lastMillis, lastMillis2, lastMillis3, switchBackTime;
bool lastTouch;
uint8_t anode, cathode = 0;
uint8_t mode = 0;
bool step;
void loop(){
  toneMachine.loop();
  display.OnUpdate(); //zavolat update displeje
  /*(millis() - lastMillis >= 100){
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
  }*/

   if(millis() - lastMillis >= 50){ //zobrazovani na displej
    if(rtc.getAlm1FlagTrigger()){
      // on alm1 trg flag
      rtc.read();
      if(displaying == MODE_TIME){
        display.SetDots(display.TIME);
        rtc.read();
        //push from rtc to display
        display.slotToInvisible = false;
        display.fillDigits(rtc.hours, rtc.minutes, rtc.seconds);
        if(rtc.seconds == 0){
          displayBuffer.forceChange = true;
        }
      }
      else if(displaying == MODE_DATE){
        display.SetDots(display.DATE);
        rtc.read();
        display.slotToInvisible = false;
        display.fillDigits(rtc.day, rtc.month, rtc.year);
      }
      else if(displaying == MODE_TEMP){
        display.SetDots(display.TEMP);
        rtc.readTemp();
        display.slotToInvisible = true;
        display.fillDigits(0xAA, rtc.getTemp(), rtc.getTempDecimalPart());
      }
      else if(displaying == MODE_ALM_PRST){
        display.SetDots(display.ALARM_SET);
        display.slotToInvisible = true;
        display.fillDigits(rtc.almhrs, rtc.almmins, 0xAA);
      }
      else if(displaying == MODE_ALM_RUN){
        display.SetDots(display.ALARM_RUN);
        rtc.read();
        display.slotToInvisible = false;
        display.fillDigits(rtc.almhrs, rtc.almmins, rtc.seconds);
      }
    }
    lastMillis = millis();
  }

  if(millis() - lastMillis2 >= 25){ //detekce dotyku a prepinani DMODu
    touch.Read();

    //pro DEBUG
    if(lastTouch != touch.touched){
      if(touch.touched){
        toneMachine.play(melodies.hapticMelody);
        switchBackTime = millis();
        displaying = (DMODE)(displaying + 1);
        if(displaying >= MODE_ALM_RUN) displaying = MODE_TIME;
        Serial.println("touch");
      } 
      lastTouch = touch.touched;
    }
    lastMillis2 = millis();
  }

  if(millis() - switchBackTime >= autoModeToSecondsTime){ //auto prepinani DMODu zpet na cas
    if(!displaying == MODE_TIME) displaying = MODE_TIME;
  }
}

void testAllSegments() {
  digitalWrite(PIN_HV_MOS, HIGH);
  volatile uint8_t* tubes[] = {
    &displayBuffer.displayedHoursTens,   // Index 0
    &displayBuffer.displayedHoursUnits,  // Index 1
    &displayBuffer.displayedMinutesTens, // Index 2
    &displayBuffer.displayedMinutesUnits,// Index 3
    &displayBuffer.displayedSecondsTens, // Index 4
    &displayBuffer.displayedSecondsUnits // Index 5
  };
  for (int i = 0; i < 6; i++) {
    *tubes[i] = 0x0F;
  }
  delay(250);
  for (int t = 0; t < 6; t++) {
    for (int d = 0; d <= 9; d++) {
      *tubes[t] = d;
      delay(50); 
    }
     *tubes[t] = 0x0F; 
  }
  digitalWrite(PIN_HV_MOS, LOW);
}

#define ONTIME 4
#define OFFTIME 2
//tady se pouzije volatile aby se predeslo memory optimization
volatile uint_fast8_t pairIndex, timer_counter;
volatile bool isBlanking;
volatile const uint_fast8_t nix_LUT_upper[]={0x00, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0x09, 0x01, 0x08, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F}; //pouzite pro opravu hw protoze jenyjek je dementni :down:
volatile const uint_fast8_t nix_LUT_downer[]={0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F}; //a druha 74141 taky protoze jenyjek neni schopnej je zapojit stejne womp womp

ISR(TIMER1_COMPA_vect) {
  if (--timer_counter == 0) {
    if (!isBlanking) {
      // --- DEAD-TIME  cas, kdy jsou vsechny anody vypnuty---
            
      // 1. vypni vsetky anody (Anody su PC0, PC1, PC2 / A0-A2)
      PORTC &= ~0x07; 

      // 2. na obe MH74141 nastav (0x0F - 0b1111) tj. vypnuto
      PORTD = (PORTD & 0x0F) | (0x0F << 4); // 1 (PD4-7)
      PORTB = (PORTB & 0xF0) | 0x0F;        // 2 (PB0-3), PB4 je des. tecka
      isBlanking = true;
      timer_counter = OFFTIME;
    } 
    else {
      // --- ON-TIME  zapni jednu z anod 1,2,3 ---
            
      // 1. vybrat anodu
      pairIndex++;
      if (pairIndex >= 3) pairIndex = 0;

      // 2. vyber co kam ma jit
      uint_fast8_t cathod_drv_1; 
      uint_fast8_t cathod_drv_2;

      // TODO dodelat desetecku
      if (pairIndex == 0) {      // Anoda A0
        cathod_drv_1 = displayBuffer.displayedMinutesTens;
        cathod_drv_2 = displayBuffer.displayedSecondsUnits; 
      } else if (pairIndex == 1) { // Anoda A1
        cathod_drv_1 = displayBuffer.displayedHoursUnits; 
        cathod_drv_2 = displayBuffer.displayedSecondsTens; 
      } else {                   // Anoda A2
        cathod_drv_1 = displayBuffer.displayedHoursTens; 
        cathod_drv_2 = displayBuffer.displayedMinutesUnits; 
      }
      /* poznamka programatora - uint_fast8_t neni nic jineho nez fancy #define. radeji to ale napiseme,
      funguje to totiz jako jakysi mental reminder, ze jsme v ISR a tudiz program musi byt co nejmensi, nejrychlejsi*/

      // 3. zapis dat na 74141
      PORTD = (PORTD & 0x0F) | (nix_LUT_upper[cathod_drv_1] << 4);//vrchni 74141ka
      PORTB = (PORTB & 0xF0) | (nix_LUT_downer[cathod_drv_2] & 0x0F);//spodni 74141ka

      // 4. zapnut jednu z anod
      PORTC = (PORTC & ~0x07) | (1 << pairIndex);

      isBlanking = false;
      timer_counter = ONTIME;
    }
  }
}