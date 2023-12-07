#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "HX711.h"

// Pin definitions
const int gasSensorPin = A0;
const int loadCellDataPin = 2;
const int loadCellClockPin = 3;

// Thresholds for gas level and weight
const int gasThreshold = 500;  // Adjust as needed
const float weightThreshold = 100.0;  // Adjust as needed

// GSM module configuration
SoftwareSerial gsmSerial(7, 8); // RX, TX
String phoneNumber = "your_phone_number"; // Replace with your actual phone number

// LCD display configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace with your LCD I2C address if different

HX711 scale;

void setup() {
  Serial.begin(9600);

  // Gas sensor setup
  // Add any initialization code specific to the gas sensor if needed

  // Load cell setup
  scale.begin(loadCellDataPin, loadCellClockPin);

  // GSM module setup
  gsmSerial.begin(9600);
  
  // LCD display setup
  lcd.begin(11, 2);
  lcd.print("Gas Monitoring");
}

void loop() {
  // Gas sensor reading
  int gasLevel = analogRead(gasSensorPin);
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Load cell reading
  float weight;  // Declare weight variable here
  if (scale.is_ready()) {
    weight = scale.get_units();
    Serial.print("Weight: ");
    Serial.println(weight);

    // Check thresholds for gas level and weight
    if (gasLevel > gasThreshold && weight > weightThreshold) {
      sendSMS("Gas level and weight thresholds reached. Booking initiated.");
      // Add your booking logic here
      delay(5000); // Delay to avoid multiple readings triggering booking
    }
  } else {
    Serial.println("Error reading from load cell");
  }

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: " + String(gasLevel));
  lcd.setCursor(0, 1);
  lcd.print("Weight: " + String(weight) + " g");

  delay(1000);  // Adjust the delay based on your preferences
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(100);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.write(26); // Send Ctrl+Z to finish message
  delay(1000); // Wait for the message to be sent
}