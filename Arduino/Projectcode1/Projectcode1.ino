#include <Wire.h>
#include <LiquidCrystalIO.h>
#include <SoftwareSerial.h>
#include <HX711.h>

// Pin definitions
const int gasSensorPin = A0;
const int loadCellDataPin = 2;
const int loadCellClockPin = 3;

// GSM module configuration
SoftwareSerial gsmSerial(7, 8); // RX, TX
String phoneNumber = "9739378190";

// LCD display configuration
LiquidCrystalIO lcd(0x27, 16, 2);

// Load cell configuration
HX711 scale;

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.print("Gas Monitoring");
  
  scale.begin(loadCellDataPin, loadCellClockPin);
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);
  float weight = scale.get_units();

  if (gasLevelThresholdReached(gasLevel) && weightThresholdReached(weight)) {
    sendSMS("Gas level and weight thresholds reached. Booking initiated.");
    // Add your booking logic here
    delay(5000); // Delay to avoid multiple readings triggering booking
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: " + String(gasLevel));
  lcd.setCursor(0, 1);
  lcd.print("Weight: " + String(weight) + " g");

  delay(5000);
}

bool gasLevelThresholdReached(int gasLevel) {
  // Add your logic to check if gas level threshold is reached
  // For example: return gasLevel > threshold;
}

bool weightThresholdReached(float weight) {
  // Add your logic to check if weight threshold is reached
  // For example: return weight > threshold;
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1");
  delay(100);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(100);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.write(26);
  delay(1000);
}