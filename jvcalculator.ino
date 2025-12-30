/**********************************************************************
  Filename    : Calculator.
  Description : Calculator with memory similar to command line in linux.
  Auther      : Joan Vilarrasa
  Modification: 2025/12/30
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include "IR.h"
#include "cache.h"

//   KEY_POWER = 0xFFA25D,
//   KEY_MENU = 0xFFE21D,
//   KEY_RESULT = 0xFF22DD,
//   KEY_DELETE = 0xFFC23D,
//   KEY_UP = 0xFF02FD,
//   KEY_DOWN = 0xFF9867,
//   KEY_LEFT = 0xFFE01F,
//   KEY_RIGHT = 0xFF906F,
//   KEY_EQUAL = 0xFFA857,
//   KEY_DOT = 0xFFB04F,
//   KEY_0 = 0xFF6897,
//   KEY_1 = 0xFF30CF,
//   KEY_2 = 0xFF18E7,
//   KEY_3 = 0xFF7A85,
//   KEY_4 = 0xFF10EF,
//   KEY_5 = 0xFF38C7,
//   KEY_6 = 0xFF5AA5,
//   KEY_7 = 0xFF42BD,
//   KEY_8 = 0xFF4AB5,
//   KEY_9 = 0xFF52AD,
//   // Long press keys
//   KEY_PLUS = 0x689700,
//   KEY_MINUS = 0x10EF00,
//   KEY_MULTIPLY = 0x18E700,
//   KEY_DIVIDE = 0x38C700,
//   KEY_OPEN_PARENTHESIS = 0x689700,
//   KEY_CLOSE_PARENTHESIS = 0xB04F00,
//   KEY_CLEAR = 0xC23D00,

#define irPin 16

LiquidCrystal_I2C lcd(0x27,16,2); 

char query[64] = "";
char result[16] = "";
// Queue cache;

int cursorIndex = 0;
int cacheIndex = 0;
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
    query[i] = '\0';
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



  // lcd.setCursor(0,1);             // Move the cursor to row 1, column 0
  // read input and modify the query
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
    case KEY_PLUS:              
      addCharToQuery('+');
      break;
    case KEY_MINUS:              
      addCharToQuery('-');
      break;
    case KEY_MULTIPLY:              
      addCharToQuery('*');
      break;
    case KEY_DIVIDE:              
      addCharToQuery('/');
      break;
    case KEY_OPEN_PARENTHESIS:              
      addCharToQuery('(');
      break;
    case KEY_CLOSE_PARENTHESIS:              
      addCharToQuery(')');
      break;
    case KEY_DELETE:              
      if(cursorIndex > 0) {
        cursorIndex--;
        query[cursorIndex] = '\0';
      }
      break;
    case KEY_CLEAR:              
      clearQuery();
      break;
  }

  // Change state


  lcd.setCursor(0,0);
  lcd.print(query);
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

