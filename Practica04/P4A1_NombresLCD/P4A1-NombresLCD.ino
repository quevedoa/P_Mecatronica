#include <LiquidCrystal.h>

int start = 15;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16,2);
}

void loop() {
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
