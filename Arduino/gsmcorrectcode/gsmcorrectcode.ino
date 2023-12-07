#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "HX711.h"

// Pin configurations
const int loadCellDataPin = 2;
const int loadCellClockPin = 3;
const int flameSensorPin = A1;
const int mq2GasSensorPin = A2;

// Thresholds for gas level (weight), flame sensor, and MQ2 gas sensor
const float weightThreshold = 200.0;  // Adjust as needed
const int flameThreshold = 50;       // Adjust as needed
const int mq2GasThreshold = 100;     // Adjust as needed

// GSM module configuration
SoftwareSerial gsmSerial(7, 8); // RX, TX
String phoneNumber = "your_phone_number"; // Replace with your actual phone number

// LCD display configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace with your LCD I2C address if different

HX711 scale;

void setup() {
  Serial.begin(9600);

  // Load cell setup
  scale.begin(loadCellDataPin, loadCellClockPin);

  // Flame sensor setup
  pinMode(flameSensorPin, INPUT);

  // GSM module setup
  gsmSerial.begin(9600);
  
  // LCD display setup
  lcd.begin(16, 2);
  lcd.print("Gas, Flame, and MQ2 Monitoring");
}

void loop() {
  // MQ2 Gas sensor reading
  int gasLevel = analogRead(mq2GasSensorPin);
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Load cell reading
  float weight;  // Declare weight variable here
  if (scale.is_ready()) {
    weight = scale.get_units();
    Serial.print("Weight: ");
    Serial.println(weight);

    // Flame sensor reading
    int flameValue = digitalRead(flameSensorPin);
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);

    // Check thresholds for gas level (weight), flame sensor, and MQ2 gas sensor
    if (weight < weightThreshold) {
      sendSMS("Gas level is low. Please book your order");
    }

    if (flameValue > flameThreshold) {
      sendSMS("Flame detected. Alert!");
    }

    if (gasLevel > mq2GasThreshold) {
      sendSMS("MQ2 Gas detected. Alert!");
    }

    // Add your logic here for individual sensor alerts

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