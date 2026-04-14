#include <Arduino.h>
#include <SerialComms.h>

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
            sprintf(buffer, "%02d:%02d:%02d-", utempH, utempM, utempS);
            Serial.print(buffer);
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
              sprintf(buffer, "%02d.%02d %02d-", utempD, utempM, utempY + 2000);
              Serial.print(buffer);
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
            sprintf(buffer, "%02d:%02d-", utempH, utempM);
            Serial.print(buffer);
            this->answerOk();
          }
          else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case CONF_DISPL_TEMP: {
          bool temp = (bool)atoi(dataPtr);
          Serial.print(temp);
          Serial.print('-');
          this->answerOk();
          break;
        }

        case CONF_TEST_SEGMENTS: {
          bool temp = (bool)atoi(dataPtr);
          Serial.print(temp);
          Serial.print('-');
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
            Serial.print(tempT);
            Serial.print('-');
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
            Serial.print(temp);
            Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_SAMPLES: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            Serial.print(tempT);
            Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_THRESHOLD: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            Serial.print(tempT);
            Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case TOUCH_SET_ALPHA: {
          uint16_t tempT = (uint16_t)atoi(dataPtr);
          if(tempT >= 250){
            this->throwError(E_INVALID_DATA);
          }
          else{
            Serial.print(tempT);
            Serial.print('-');
            this->answerOk();
          }
          break;
        }

        case MELODY_SET_ALARM: {
          int interval = atoi(dataPtr); 
          // Find the melody part (everything after the comma)
          char* melodyPtr = strchr(dataPtr, ';') + 1;
          if(isValidMelody(melodyPtr)&&interval > 0){
            Serial.print(melodyPtr);
            Serial.print(" at bpm: ");
            Serial.print(interval);
            Serial.print("-");
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
            Serial.print(melodyPtr);
            Serial.print(" at bpm: ");
            Serial.print(interval);
            Serial.print("-");
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
            Serial.print(melodyPtr);
            Serial.print(" at bpm: ");
            Serial.print(interval);
            Serial.print("-");
            this->answerOk();
          }else{
            this->throwError(E_INVALID_DATA);
          }
          break;
        }

        case EXIT_CMD:{
          this->endComms();
          break;
        }

        case SAVE_CMD:{
          this->throwError(E_FAILED);
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
