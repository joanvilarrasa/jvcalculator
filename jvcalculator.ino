/**********************************************************************
  Filename    : Calculator.
  Description : Calculator with memory similar to command line in linux.
  Auther      : Joan Vilarrasa
  Modification: 2025/12/30
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include "IR.h"

#define irPin 16

LiquidCrystal_I2C lcd(0x27,16,2); 
#define LCD_LINE_LENGTH 16

char query[64] = "";
char result[LCD_LINE_LENGTH] = "";
// Queue cache;

int cursorIndex = 0;
int resultLength = 0;
KeyCode lastKey = KEY_NONE;
bool isOn = false;

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

void computeResult() {
  result[0] = '1';
  result[1] = '2';
  result[2] = '3';
  result[3] = '4';
  result[4] = '5';
  resultLength = 5;
}

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

void loop() {

  if(!flagCode){
    // No input - do nothing
    return;
  }

  // Read input
  KeyCode irValue = IR_Decode(flagCode);
  Serial.println(irValue, HEX);
  IR_Release();
  // This should not exists but the remote has a limited number of keys and I do not want to get a new remote as this is just an experiment.
  irValue = translateKey(irValue);

  // TODO: Possible enhancements: Handle long press keys for more complex behaviour.
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
  if(irValue == KEY_0) { addCharToQuery('0'); }
  else if(irValue == KEY_1) { addCharToQuery('1'); }
  else if(irValue == KEY_2) { addCharToQuery('2'); }
  else if(irValue == KEY_3) { addCharToQuery('3'); }
  else if(irValue == KEY_4) { addCharToQuery('4'); }
  else if(irValue == KEY_5) { addCharToQuery('5'); }
  else if(irValue == KEY_6) { addCharToQuery('6'); }
  else if(irValue == KEY_7) { addCharToQuery('7'); }
  else if(irValue == KEY_8) { addCharToQuery('8'); }
  else if(irValue == KEY_9) { addCharToQuery('9'); }
  else if(irValue == KEY_PLUS) { addCharToQuery('+'); }
  else if(irValue == KEY_MINUS) { addCharToQuery('-'); }
  else if(irValue == KEY_ASTERISK) { addCharToQuery('*'); }
  else if(irValue == KEY_SLASH) { addCharToQuery('/'); }

  // Compute the result
  computeResult();

  // Handle special keys
  if(irValue == KEY_CLEAR) { 
    if(cursorIndex > 0) { 
      cursorIndex--; 
      query[cursorIndex] = ' '; 
    } 
    for(int i = 0; i < LCD_LINE_LENGTH; i++) {
      result[i] = ' ';
    }
  }

  if(irValue == KEY_EQUAL) {
    for(int i = 0; i < LCD_LINE_LENGTH; i++) {
      query[i] = result[i];
    }
    for(int i = LCD_LINE_LENGTH; i < 64; i++) {
      query[i] = ' ';
    }
    cursorIndex = resultLength;
  }
  
  // Render
  char queryToPrint[LCD_LINE_LENGTH] = "";
  for(int i = 0; i < LCD_LINE_LENGTH; i++) {
    int queryIndex = cursorIndex + i - LCD_LINE_LENGTH;
    if(queryIndex >= 0) {
      queryToPrint[i] = query[queryIndex];
    }
    else {
      queryToPrint[i] = ' ';
    }
  }
  lcd.setCursor(0,0);
  lcd.print(queryToPrint);

  char resultToPrint[LCD_LINE_LENGTH] = "";
  for(int i = 0; i < LCD_LINE_LENGTH; i++) {
    int resultIndex = resultLength + i - LCD_LINE_LENGTH;
    if(resultIndex >= 0) {
      resultToPrint[i] = result[resultIndex];
    }
    else {
      resultToPrint[i] = ' ';
    }
  }
  lcd.setCursor(0,1);
  lcd.print(resultToPrint);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}


// The remote has a limited number of keys, so we have to get a little bit creative with the keys.
KeyCode translateKey(KeyCode key) {
  if(key == KEY_LEFT) {
    return KEY_ASTERISK;
  }
  if(key == KEY_RIGHT) {
    return KEY_SLASH;
  }
  if(key == KEY_PLAY) {
    return KEY_EQUAL;
  }
  return key;
}

