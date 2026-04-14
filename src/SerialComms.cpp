#include <Arduino.h>
#include <SerialComms.h>

#include <main.cpp>
#include <presetMemory.h>
#include <touch.h>
#include <rtc.h>
#include <melodies.h>
#include <displayManager.h>

SerialLine serialLine;

void SerialLine::update(){
  if (Serial.available() > 0) {
    int bytesRead = Serial.readBytesUntil('\n', buffer, MAX_BUF - 1);
    buffer[bytesRead] = '\0';

    // If bytesRead reached the limit AND the next char isn't the newline...
    if (bytesRead == MAX_BUF - 1 && Serial.peek() != '\n') {
      this->throwError(E_OVERFLOW);
      this->clear();
      // This is a confirmed overflow.
      goto end; //skip entire serial stuff
    }

    if (strncmp(buffer, CMD_PFX, strlen(CMD_PFX)) == 0) {
      // 1. Move pointer past the prefix
      char* ptr = buffer + strlen(CMD_PFX);

      // 2. SKIP SPACES: Move pointer until it hits a non-space character
      while (*ptr == ' ') { ptr++; }

      // 3. Now 'ptr' points exactly at 'S' in 'SCK'
      uint32_t cmd = encode3(ptr);

      char* dataPtr = ptr + 3; 
      while (*dataPtr == ' ') { dataPtr++; }

      switch (cmd) {
        case SET_CLOCK:{ // Matches "SCK"     
          int tempH, tempM, tempS;
          sscanf(dataPtr, "%d%*[^0-9]%d%*[^0-9]%d", &tempH, &tempM, &tempS);
          //converze signed -> unsigned
          uint8_t utempH = (uint8_t)tempH, utempM = (uint8_t)tempM, utempS = (uint8_t)tempS;
          //sanitize
          if(utempH < 23 && utempM < 60 && utempS < 60){
            //sprintf(buffer, "%02d:%02d:%02d-", utempH, utempM, utempS);
            //Serial.print(buffer);
            rtc.setTime(utempS, utempM, utempH);
            this->answerOk();
          }
          else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }
        
        case SET_DATE: {
          int tempD, tempM, tempY;
          sscanf(dataPtr, "%d%*[^0-9]%d%*[^0-9]%d", &tempD, &tempM, &tempY);
          //converze signed -> unsigned
          if(tempY >= 2000) tempY-=2000; //pokud je nekdo kokot a zadal rok 20XX
          uint8_t utempD = (uint8_t)tempD, utempM = (uint8_t)tempM, utempY = (uint8_t)tempY;
          //sanitize
          if(utempM <= 12 && utempY <= 99){
            if(utempD <= this->getMaxDays(utempM, utempY)){
              //sprintf(buffer, "%02d.%02d %02d-", utempD, utempM, utempY + 2000);
              //Serial.print(buffer);
              rtc.setDate(utempD, utempM, utempY, this->getDayOfWeek(utempD, utempM, utempY));
              this->answerOk();
            }
            else{
              this->throwError(E_INVALID_DATA);
            }
          }
          else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case SET_ALM: {
          int tempH, tempM;
          sscanf(dataPtr, "%d%*[^0-9]%d", &tempH, &tempM);
          //converze signed -> unsigned
          uint8_t utempH = (uint8_t)tempH, utempM = (uint8_t)tempM;
          //sanitize
          if(utempH < 23 && utempM < 60){
            //sprintf(buffer, "%02d:%02d-", utempH, utempM);
            //Serial.print(buffer);
            rtc.almhrs = utempH;
            rtc.almmins = utempM;
            rtc.setAlm();
            this->answerOk();
          }
          else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case CONF_DISPL_TEMP: {
          bool temp = (bool)atoi(dataPtr);
          //Serial.print(temp);
          //Serial.print('-');
          displayTemperature = temp;
          this->answerOk();
          break;
        }

        case CONF_TEST_SEGMENTS: {
          bool temp = (bool)atoi(dataPtr);
          //Serial.print(temp);
          //Serial.print('-');
          testSegments = temp;
          this->answerOk();
          break;
        }

        case CONF_RADAR_RETURNTIME: {
          int tempT = atoi(dataPtr);
          if(tempT >= 250 || tempT <= 0){
            this->throwError(E_INVALID_DATA);
          }
          else{
            uint8_t temp = (uint8_t)tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            turnOffAfterRadarTime = 1000*temp;
            this->answerOk();
          }
          break;
        }

        case CONF_MENU_RETURNTIME: {
          int tempT = atoi(dataPtr);
          if(tempT >= 250 || tempT <= 0){
            this->throwError(E_INVALID_DATA);
          }
          else{
            uint8_t temp = (uint8_t)tempT;
            //Serial.print(temp);
            //Serial.print('-');
            autoModeToSecondsTime = 1000*temp;
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_SAMPLES: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT >= 1000){
            this->throwError(E_INVALID_DATA);
          }
          else{
            touch.samples = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_THRESHOLD: {
          uint8_t tempT = (uint8_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            touch.threshold = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_ALPHA: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT >= 25){
            this->throwError(E_INVALID_DATA);
          }
          else{
            touch.alpha = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case MELODY_SET_ALARM: {
          int interval = atoi(dataPtr); 
          // Find the melody part (everything after the comma)
          char* melodyPtr = strchr(dataPtr, ';') + 1;
          if(isValidMelody(melodyPtr)&&interval > 0){
            melodies.alarmMelody = {melodyPtr, interval, false};
            //Serial.print(melodyPtr);
            //Serial.print(" at bpm: ");
            //Serial.print(interval);
            //Serial.print("-");
            this->answerOk();
          }else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case MELODY_SET_OK: {
          int interval = atoi(dataPtr); 
          // Find the melody part (everything after the comma)
          char* melodyPtr = strchr(dataPtr, ';') + 1;
          if(isValidMelody(melodyPtr)&&interval > 0){
            melodies.okSfxMelody = {melodyPtr, interval, true};
            //Serial.print(melodyPtr);
            //Serial.print(" at bpm: ");
            //Serial.print(interval);
            //Serial.print("-");
            this->answerOk();
          }else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case MELODY_SET_ERR: {
          int interval = atoi(dataPtr); 
          // Find the melody part (everything after the comma)
          char* melodyPtr = strchr(dataPtr, ';') + 1;
          if(isValidMelody(melodyPtr)&&interval > 0){
            melodies.forbiddenSfxMelody = {melodyPtr, interval, true};
            //Serial.print(melodyPtr);
            //Serial.print(" at bpm: ");
            //Serial.print(interval);
            //Serial.print("-");
            this->answerOk();
          }else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case DISPLAY_SLOT_SECONDS: {
          bool temp = (bool)atoi(dataPtr);
          //Serial.print(temp);
          //Serial.print('-');
          display.slotSecondsUnits = temp;
          this->answerOk();
          break;
        }

        case DISPLAY_ANIM_UPDATE: {
          uint8_t tempT = (uint8_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            display.animUpdateInterval = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case DISPLAY_SECS_UPDATE: {
          uint8_t tempT = (uint8_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            display.rotateSecondsInterval = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case DISPLAY_MINS_UPDATE: {
          uint8_t tempT = (uint8_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            display.rotateMinutesHoursInterval = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case DISPLAY_DOT_ONTIME: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT > 800){
            this->throwError(E_INVALID_DATA);
          }
          else{
            display.doubleDotOnTime = tempT;
            //Serial.print(tempT);
            //Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case EXIT_CMD:{
          this->endComms();
          break;
        }

        case SAVE_CMD:{
          this->saveToEeprom();
          this->answerOk();
          break;
        }

        case FACTORY_RESET_CMD:{
          this->resetToDefault();
          this->answerOk();
          break;
        }

        default:{
          this->throwError(E_UNKNOWN_CMD); 
          break;
        }
        // ... other cases ...
      }
    }
  }
  end:
  millis();
  //end
}

void SerialLine::setup()
{
  Serial.begin(115200);
  this->answerOk();
}

void SerialLine::throwError(ErrType error){
  Serial.print("E");
  Serial.println(error);
}

void SerialLine::answerOk()
{
  Serial.println("OK");
}

void SerialLine::endComms()
{
  this->answerOk();
  Serial.end();
}

uint8_t SerialLine::getMaxDays(uint8_t month,uint8_t year) {
  // February logic: Leap year check
  if (month == 2) {
    // In the 2000s, it's a leap year if the 2-digit year is divisible by 4
    // (Note: 00 was 2000, which WAS a leap year)
    if (year % 4 == 0) {
      return 29;
    }
    return 28;
  }

  // Months with 30 days: April(4), June(6), September(9), November(11)
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
  }

  // All other months have 31
  return 31;
}

void SerialLine::clear()
{
  // 1. Clear Hardware Buffer
  while (Serial.available() > 0) Serial.read();
  
  // 3. Exit the current logic
  return;
}

bool SerialLine::isValidMelody(char* str) {
  // 1. Check if the string actually ends with '0'
  int len = strlen(str);
  if (len == 0 || str[len - 1] != '0') return false;

  // 2. Iterate through the string in steps of 2 (the pairs)
  // We stop before the last character because that must be the '0'
  for (int i = 0; i < len - 1; i += 2) {
    
    // Check if the first char of the pair is a digit (Multiplier)
    if (!isdigit(str[i])) return false;

    // Check if there is a char after the digit (The Note)
    // If the '0' is in an even position (e.g., "1A2B0"), 
    // it means a pair is missing a note.
    if (str[i+1] == '0' || str[i+1] == '\0') return false;
    
    // Optional: Check if the note is a valid character
    // (A-Z, a-z, or X)
    char note = str[i+1];
    if (!isAlpha(note) && note != 'X') return false;
  }

  return true;
}

uint8_t SerialLine::getDayOfWeek(uint8_t d, uint8_t m, uint8_t y2d) {
  // y2d is the 2-digit year (e.g., 26 for 2026)
  // Adjust month and year for the formula (March becomes month 3, Feb is 14 of prev year)
  if (m < 3) {
    m += 12;
    y2d -= 1;
  }

  // Sakamoto's Algorithm / Zeller variation for the 21st Century
  // (d + y + y/4 + (31*m)/12) % 7
  // We add 2000 logic specifically for the offset
  int y = 2000 + y2d;
  int dow = (d + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;

  // The formula returns 0 for Sunday, 1 for Monday... 
  // To return 1-7:
  return dow + 1;
}

void SerialLine::saveToEeprom(){
  PresetMemory::mainConfigManagerPreset MainData;
  MainData.autoModeToSecondsTime = autoModeToSecondsTime;
  MainData.turnOffAfterRadarTime = turnOffAfterRadarTime;
  MainData.testSegments = testSegments;
  MainData.displayTemperature = displayTemperature;
  presetMemory.pushMainConfigManagerPreset(MainData);

  PresetMemory::displayManagerPreset DMGRData;
  DMGRData.slotSecondsUnits = display.slotSecondsUnits;
  DMGRData.animUpdateInterval = display.animUpdateInterval;
  DMGRData.rotateSecondsInterval = display.rotateSecondsInterval;
  DMGRData.rotateMinutesHoursInterval = display.rotateMinutesHoursInterval;
  DMGRData.doubleDotOnTime = display.doubleDotOnTime;
  presetMemory.pushDisplayManagerPreset(DMGRData);

  PresetMemory::touchPreset TouchData;
  TouchData.samples = touch.samples;
  TouchData.treshold = touch.threshold;
  TouchData.alpha = touch.alpha;
  presetMemory.pushTouchPreset(TouchData);

  PresetMemory::almSoundPreset MelodyData;
  MelodyData.almMelody = melodies.alarmMelody;
  MelodyData.okSfxMelody = melodies.okSfxMelody;
  MelodyData.errSfxMelody = melodies.forbiddenSfxMelody;
  presetMemory.pushAlmSoundPreset(MelodyData);
}

void SerialLine::resetToDefault(){
  PresetMemory::mainConfigManagerPreset MainData;
  MainData.autoModeToSecondsTime = 10000;
  MainData.turnOffAfterRadarTime = 2500;
  MainData.testSegments = true;
  MainData.displayTemperature = false;
  presetMemory.pushMainConfigManagerPreset(MainData);

  PresetMemory::displayManagerPreset DMGRData;
  DMGRData.slotSecondsUnits = false;
  DMGRData.animUpdateInterval = 150;
  DMGRData.rotateSecondsInterval = 75;
  DMGRData.rotateMinutesHoursInterval = 75;
  DMGRData.doubleDotOnTime = 250;
  presetMemory.pushDisplayManagerPreset(DMGRData);

  PresetMemory::touchPreset TouchData;
  TouchData.samples = 100;
  TouchData.treshold = 40;
  TouchData.alpha = 8;
  presetMemory.pushTouchPreset(TouchData);

  PresetMemory::almSoundPreset MelodyData;
  MelodyData.almMelody = {"1W1V2f2g1u1B2D2E1B1A2c2E3A5X0", 65, false};
  MelodyData.okSfxMelody = {"1C1E1G1U1X0", 20, true};
  MelodyData.errSfxMelody = {"2C1X2C1X0", 30, true};
  presetMemory.pushAlmSoundPreset(MelodyData);
}