#ifndef __IR_H__
#define __IR_H__

#include <Arduino.h>

extern int flagCode;
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
    KEY_PLUS = 0x30CF00,
    KEY_MINUS = 0x10EF00,
    KEY_MULTIPLY = 0x18E700,
    KEY_DIVIDE = 0x38C700,
    KEY_OPEN_PARENTHESIS = 0x689700,
    KEY_CLOSE_PARENTHESIS = 0xB04F00,
    KEY_CLEAR = 0xC23D00,
};

void IR_Init(int pin);
KeyCode IR_Decode(int &code);
void IR_Release();

void IR_Read();

#endif
