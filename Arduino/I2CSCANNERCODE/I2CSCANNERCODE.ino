#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace with your LCD I2C address if different

void setup() {
  // LCD initialization
  lcd.begin(0x27, 16, 2);
  lcd.print("LCD Test");
}

void loop() {
  // Display a scrolling message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, Arduino!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LCD Test");
  delay(1000);
}