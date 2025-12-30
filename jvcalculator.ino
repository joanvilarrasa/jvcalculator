/**********************************************************************
  Filename    : Calculator.
  Description : Calculator with memory similar to command line in linux.
  Auther      : Joan Vilarrasa
  Modification: 2025/12/30
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include "IR.h"
#include "cache.h"

#define irPin 16

LiquidCrystal_I2C lcd(0x27,16,2); 
#define LCD_LINE_LENGTH 16

char query[64] = "";
char result[16] = "";
// Queue cache;

int cursorIndex = 0;
int cacheIndex = 0;
KeyCode lastKey = KEY_NONE;
bool isOn = false;



void setup() {
  // Initialize the cache
  // queue_init(&cache);
  // queue_enqueue(&cache, "some string");
  // const char* item = queue_get(&cache, 0);

  // Initialize the LCD
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();   

  // Initialize the infrared receiver and serial communication
  Serial.begin(115200);           // Initialize serial communication
  IR_Init(irPin);                 // Initialize infrared receiver

  // Initialize the query and the result
  clearQuery();

}

void addCharToQuery(char c) {
  if(cursorIndex < 64) {
    query[cursorIndex] = c;
    cursorIndex++;
  }
}

void clearQuery() {
  for(int i = 0; i < 64; i++) {
    query[i] = ' ';
  }
  cursorIndex = 0;
}

void loop() {

  if(!flagCode){
    // No input - do nothing
    return;
  }

  // Read input
  KeyCode irValue = IR_Decode(flagCode);
  Serial.println(irValue, HEX);
  IR_Release();

  // TODO: Possible enhancements: Handle long press keys
  if(irValue == KEY_LONG_PRESS) {
    if(lastKey == KEY_CLEAR) {
      clearQuery();
    }
    lastKey = KEY_NONE;
  } else {
    lastKey = irValue;
  }

  // Handle On/Off
  if(isOn && irValue == KEY_POWER) {
      isOn = false;
      lcd.noBacklight();
      lcd.noDisplay();
    return;
  }

  if(!isOn) {
    if(irValue == KEY_POWER) {
      isOn = true;
      lcd.display();
      lcd.backlight();
    }
    return;
  }

  // Handle Normal Keypress
  switch (irValue) {
    case KEY_0:              
      addCharToQuery('0');
      break;
    case KEY_1:              
      addCharToQuery('1');
      break;
    case KEY_2:              
      addCharToQuery('2');
      break;
    case KEY_3:              
      addCharToQuery('3');
      break;
    case KEY_4:              
      addCharToQuery('4');
      break;
    case KEY_5:              
      addCharToQuery('5');
      break;
    case KEY_6:              
      addCharToQuery('6');
      break;
    case KEY_7:              
      addCharToQuery('7');
      break;
    case KEY_8:              
      addCharToQuery('8');
      break;
    case KEY_9:              
      addCharToQuery('9');
      break;
    
    case KEY_CLEAR:              
      if(cursorIndex > 0) {
        cursorIndex--;
        query[cursorIndex] = ' ';
      }
      break;
  }

  // Change state
  char queryToPrint[LCD_LINE_LENGTH] = "";
  int emptySpaces = LCD_LINE_LENGTH - cursorIndex;
  for(int i = 0; i < emptySpaces; i++) {
    queryToPrint[cursorIndex + i] = ' ';
  }
  if(emptySpaces < 0) {
    for(int i = 0; i < LCD_LINE_LENGTH; i++) {
      queryToPrint[i] = query[i - emptySpaces];
    }
  }
  else {
    for(int i = emptySpaces; i < LCD_LINE_LENGTH; i++) {
      queryToPrint[i] = query[i - emptySpaces];
    }
  }
  lcd.setCursor(0,0);
  lcd.print(queryToPrint);
  lcd.setCursor(0,1);
  lcd.print(result);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

