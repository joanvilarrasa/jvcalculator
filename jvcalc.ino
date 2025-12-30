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

void setup() {
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                     // LCD driver initialization
  lcd.backlight();                // Open the backlight
  lcd.setCursor(0,0);             // Move the cursor to row 0, column 0
  lcd.print("hello world");       // The print content is displayed on the LCD
  Serial.begin(115200);           // Initialize serial communication
  IR_Init(irPin);                 // Initialize infrared receiver
}

void loop() {
  if(flagCode){
    int irValue = IR_Decode(flagCode);
    Serial.println(irValue, HEX);
    lcd.setCursor(0,1);             // Move the cursor to row 1, column 0
    // Handle the commands
    switch (irValue) {
      case 0xFF6897:              // Receive the number '0'
        lcd.print("0");
        break;
      case 0xFF30CF:              // Receive the number '1'
        lcd.print("1");
        break;
      case 0xFF18E7:              // Receive the number '2'
        lcd.print("2");
        break;
      case 0xFF7A85:              // Receive the number '3'
        lcd.print("3");
        break;
    }
    IR_Release();
  }
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

