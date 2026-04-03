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

void testAllSegments();

void setup() {
  // setup se spousti pouze jednou, pri spusteni MCU (reset, napajeni apod.)
  Serial.begin(115200); //inicializuj seriovou linku s rychlosti 115200baud
  //initMelodies(); //inicializace melodii

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

  /*touch.Setup(PIN_TOUCH, 100, 40, 8); //nastavenicko captouch s defaultnima hodnotama

  displayBuffer.digits[0] = 0;
  displayBuffer.digits[1] = 0;
  displayBuffer.digits[2] = 0;
  displayBuffer.digits[3] = 0;
  displayBuffer.digits[4] = 0;
  displayBuffer.digits[5] = 0;
  
  display.TurnOff();
  //display.OnUpdate();
  //Wire.begin();
  //rtc.initAlm1();
  Serial.println("startup done");
  displaying = MODE_TIME;
  display.TurnOn();
  toneMachine.currentMelody = melodies.okSfxMelody;*/
  digitalWrite(PIN_HV_MOS, HIGH);
  testAllSegments();
}

uint64_t lastMillis, lastMillis2, lastMillis3;
bool lastTouch;
uint8_t anode, cathode = 0;
uint8_t mode = 0;
bool step;
void loop(){
  //toneMachine.loop();
  //display.OnUpdate(); //zavolat update displeje
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
 /* if(millis() - lastMillis2 >= 50){
    if(rtc.getAlm1FlagTrigger()){
      // on alm1 trg flag
      if(displaying == MODE_TIME){
        display.SetDots(display.TIME);
        rtc.read();
        //push from rtc to display
        display.fillDigits(rtc.hours, rtc.minutes, rtc.seconds);
        if(rtc.seconds == 0){
          displayBuffer.forceChange = true;
        }
      }
      else if(displaying == MODE_DATE){
        display.SetDots(display.DATE);
        rtc.read();
        display.fillDigits(rtc.day, rtc.month, rtc.year);
      }
      else if(displaying == MODE_TEMP){
        display.SetDots(display.TEMP);
        rtc.readTemp();
        display.fillDigits(0xFF, rtc.getTemp(), rtc.getTempDecimalPart());
      }
      else if(displaying == MODE_ALM_PRST){
        display.SetDots(display.ALARM_SET);
        display.fillDigits(rtc.almhrs, rtc.almmins, 0xFF);
      }
      else if(displaying == MODE_ALM_RUN){
        display.SetDots(display.ALARM_RUN);
        rtc.read();
        display.fillDigits(rtc.almhrs, rtc.almmins, rtc.seconds);
      }
    }
    lastMillis2 = millis();
  }

  if(millis() - lastMillis3 >= 25){
    //kazdych 25ms
    touch.Read();

    if(lastTouch != touch.touched){
      toneMachine.run = touch.touched;
      lastTouch = touch.touched;
    }
    
    lastMillis3 = millis();
  }
  */
  /*if(millis() - lastMillis3 >= 25){
    //Serial.println("touch!");
    //kazdych 25ms
    touch.Read();

    //pro DEBUG
    if(lastTouch != touch.touched){
      if(touch.touched) toneMachine.play(melodies.hapticMelody);
      step = true;
      lastTouch = touch.touched;
    }
    
    lastMillis3 = millis();
  }*/
}

// Simple cathode/anode test - cycles through all segments without animation
void testAllSegments() {
  Serial.println("Starting segment test...");
  
  // Direct pin control for testing
  const uint8_t anodePins[4] = {PIN_DIG_1, PIN_DIG_2, PIN_DIG_3};
  const uint8_t cathodeA[2] = {PIN_MH141_A1, PIN_MH141_A2};
  const uint8_t cathodeB[2] = {PIN_MH141_B1, PIN_MH141_B2};
  const uint8_t cathodeC[2] = {PIN_MH141_C1, PIN_MH141_C2};
  const uint8_t cathodeD[2] = {PIN_MH141_D1, PIN_MH141_D2};
  
  // Test each anode
  for(int anode = 0; anode < 4; anode++) {
    digitalWrite(anodePins[anode], HIGH);
    
    // Test each cathode (0-11)
    for(int cathode = 0; cathode < 12; cathode++) {
      // Decode cathode value to BCD
      uint8_t bit0 = (cathode & 1) ? HIGH : LOW;
      uint8_t bit1 = (cathode & 2) ? HIGH : LOW;
      uint8_t bit2 = (cathode & 4) ? HIGH : LOW;
      uint8_t bit3 = (cathode & 8) ? HIGH : LOW;
      
      // Set cathode pins
      digitalWrite(cathodeA[0], bit0);
      digitalWrite(cathodeB[0], bit1);
      digitalWrite(cathodeC[0], bit2);
      digitalWrite(cathodeD[0], bit3);

      Serial.print("Anode: ");
      Serial.print(anode);
      Serial.print(" Cathode: ");
      Serial.println(cathode);
      
      delay(300);
    }
    for(int cathode = 0; cathode < 12; cathode++){
      // Decode cathode value to BCD
      uint8_t bit0 = (cathode & 1) ? HIGH : LOW;
      uint8_t bit1 = (cathode & 2) ? HIGH : LOW;
      uint8_t bit2 = (cathode & 4) ? HIGH : LOW;
      uint8_t bit3 = (cathode & 8) ? HIGH : LOW;

      digitalWrite(cathodeA[1], bit0);
      digitalWrite(cathodeB[1], bit1);
      digitalWrite(cathodeC[1], bit2);
      digitalWrite(cathodeD[1], bit3);
    }
      Serial.print("Anode: ");
      Serial.print(anode);
      Serial.print(" Cathode: ");
      Serial.println(cathode);
      delay(300);
      digitalWrite(anodePins[anode], LOW);
  }

  Serial.println("Test complete!");
}

#define ONTIME 3
#define OFFTIME 1
volatile uint_fast8_t pairIndex, timer_counter;
volatile bool isBlanking;
volatile const uint_fast8_t nix_LUT[]={0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xF}; //pouzite pro opravu hw protoze jenyjek je dementni :down:

ISR(TIMER1_COMPA_vect) {
  timer_counter--;

  if (timer_counter == 0) {
    if (!isBlanking) {
      // --- DEAD-TIME  cas, kdy jsou vsechny anody vypnuty---
            
      // 1. vypni vsetky anody (Anody su PC0, PC1, PC2 / A0-A2)
      PORTC &= ~0x07; 

      // 2. na obe MH74141 nastav (0x0F - 0b1111) tj. vypnuto
      PORTD = (PORTD & 0x0F) | (0x0F << 4); // 1 (PD4-7)
      PORTB = (PORTB & 0xF0) | 0x0F;        // 2 (PB0-3), PB4 je! des. tecka
      isBlanking = true;
      timer_counter = OFFTIME;
    } 
    else {
      // --- ON-TIME  zapni jednu z anod 1,2,3 ---
            
      // 1. vybrat anodu
      pairIndex++;
      if (pairIndex >= 3) pairIndex = 0;

      // 2. Load data from buffer for this pair
      uint_fast8_t cathod_drv_1; 
      uint_fast8_t cathod_drv_2;

      // vyber co se kam da:
      if (pairIndex == 0) {      // Anode A0: Tubes 1 and 5
        cathod_drv_1 = displayBuffer.displayedHoursTens;//tube 1 
        cathod_drv_2 = displayBuffer.displayedSecondsTens; //tube 5
      } else if (pairIndex == 1) { // Anode A1: Tubes 2 and 4
        cathod_drv_1 = displayBuffer.displayedHoursUnits; //tube 2
        cathod_drv_2 = displayBuffer.displayedMinutesUnits; //tube 4
      } else {                   // Anode A2: Tubes 3 and 6
        cathod_drv_1 = displayBuffer.displayedMinutesTens; //tube 3
        cathod_drv_2 = displayBuffer.displayedSecondsUnits; //tube 6
      }
      /* poznamka programatora - uint_fast8_t neni nic jineho nez fancy #define. radeji to ale napiseme,
      funguje to totiz jako jakysi mental reminder, ze jsme v ISR a tudiz program musi byt co nejmensi, nejrychlejsi*/

      // 3. zapis dat na 74141
      PORTD = (PORTD & 0x0F) | (nix_LUT[cathod_drv_1] << 4);
      PORTB = (PORTB & 0xF0) | (nix_LUT[cathod_drv_2] & 0x0F);

      // 4. zapnut jednu z anod
      PORTC = (PORTC & ~0x07) | (1 << pairIndex);

      isBlanking = false;
      timer_counter = ONTIME;
    }
  }
}