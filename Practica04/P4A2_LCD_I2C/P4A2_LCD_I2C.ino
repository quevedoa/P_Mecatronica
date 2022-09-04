//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int start = 15;

void setup()
{
  lcd.init();
  lcd.backlight();
}


void loop()
{
  lcd.setCursor(16,0);
  lcd.print("Andres_Q");
  lcd.setCursor(16,1);
  lcd.print("Jesus_V");
  
  if (start >= 0) {
    lcd.scrollDisplayLeft();
  }
  start = start - 1;
  delay(500);
}
