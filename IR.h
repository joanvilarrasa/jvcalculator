#ifndef __IR_H__
#define __IR_H__

#include <Arduino.h>

extern int flagCode;
enum KeyCode {
    // Short press keys
    KEY_POWER = 0xFFA25D,
    KEY_MENU = 0xFFE21D,
    KEY_TEST = 0xFF22DD,
    KEY_PLUS = 0xFF02FD,
    KEY_BACH = 0xFFC23D,
    KEY_LEFT = 0xFFE01F,
    KEY_PLAY = 0xFFA857,
    KEY_RIGHT = 0xFF906F,
    KEY_0 = 0xFF6897,
    KEY_MINUS = 0xFF9867,
    KEY_CLEAR = 0xFFB04F,
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
    KEY_LONG_PRESS = 0xffffffff,
    KEY_NONE = 0x00000000,

    // Special keys
    KEY_ASTERISK = 0xFF5AAD,
    KEY_SLASH = 0xFF42B5,
    KEY_EQUAL = 0xFF4ABD,
};

void IR_Init(int pin);
KeyCode IR_Decode(int &code);
void IR_Release();

void IR_Read();

#endif
