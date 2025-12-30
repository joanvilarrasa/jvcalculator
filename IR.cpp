#include "IR.h"

int logList[32];
unsigned long startTime;
int endTime, end2Time;
int flagCode = 0;
int irPin;
bool irState = true;
enum KeyCode {
  // Short press keys
  KEY_POWER = 0xFFA25D,
  KEY_MENU = 0xFFE21D,
  KEY_RESULT = 0xFF22DD,
  KEY_DELETE = 0xFFC23D,
  KEY_UP = 0xFF02FD,
  KEY_DOWN = 0xFF9867,
  KEY_LEFT = 0xFFE01F,
  KEY_RIGHT = 0xFF906F,
  KEY_EQUAL = 0xFFA857,
  KEY_DOT = 0xFFB04F,
  KEY_0 = 0xFF6897,
  KEY_1 = 0xFF30CF,
  KEY_2 = 0xFF18E7,
  KEY_3 = 0xFF7A85,
  KEY_4 = 0xFF10EF,
  KEY_5 = 0xFF38C7,
  KEY_6 = 0xFF5AA5,
  KEY_7 = 0xFF42BD,
  KEY_8 = 0xFF4AB5,
  KEY_9 = 0xFF52AD,
  // Long press keys
  KEY_PLUS = 0x689700,
  KEY_MINUS = 0x10EF00,
  KEY_MULTIPLY = 0x18E700,
  KEY_DIVIDE = 0x38C700,
  KEY_OPEN_PARENTHESIS = 0x689700,
  KEY_CLOSE_PARENTHESIS = 0xB04F00,
  KEY_CLEAR = 0xC23D00,
};

void IR_Init(int pin) {
  irPin = pin;
  pinMode(irPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irPin), IR_Read, CHANGE);
}

void IR_Read() {
  if (irState == true) {
    unsigned long lowTime, highTime, intervalTime;
    int num = 0;
    while (digitalRead(irPin) == LOW) {
      startTime = micros();
      while (digitalRead(irPin) == LOW) {
        lowTime = micros();
      }
      intervalTime = lowTime - startTime;
      while (digitalRead(irPin) == HIGH) {
        highTime = micros();
        intervalTime = highTime - lowTime;
        if (intervalTime > 10000) {
          end2Time = millis();
          if (num == 32) {
            flagCode = 1;
            endTime = millis();
          }
          else if (num == 0 && end2Time - endTime > 300 && end2Time - endTime < 400) {
            flagCode = 2;
            endTime = millis();
          }
          return;
        }
      }
      if (intervalTime < 2000) {
        if (intervalTime < 700) {
          logList[num ++] = 0;
        }
        else {
          logList[num ++] = 1;
        }
      }
    }
  }
}

KeyCode IR_Decode(int &code) {
  unsigned long irData = 0;
  irState=false;
  if (code == 1) {
    code = 0;
    for (int i = 0; i < 32; i ++) {
      if (logList[i] == 0) {
        irData <<= 1;
      }
      else {
        irData <<= 1;
        irData ++;
      }
      logList[i] = 0;
    }
  }
  if (code == 2) {
    code = 0;
    irData <<= 2;
  }
  return (KeyCode)irData;
}

void IR_Release(){
  irState=true;
}
