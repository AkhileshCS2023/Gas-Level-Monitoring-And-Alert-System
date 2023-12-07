//Load cell HX711
#include "HX711.h"
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;


HX711 scale;

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);
  Serial.println("Gms");

  scale.power_down();			        // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}


//MQ2 Gas Sensor
const int gasSensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the gas sensor
  int gasLevel = analogRead(gasSensorPin);

  // Print the gas level to the Serial Monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  delay(1000); // Adjust the delay based on your preferences

}



// Pin configuration flame sensor
const int flameSensorPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the flame sensor
  int flameValue = analogRead(flameSensorPin);

  // Print the flame sensor value to the Serial Monitor
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);

  // You can add logic here based on the flame sensor value

  delay(1000); // Adjust the delay based on your preferences
}



//LCD
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Jai Shree Ram");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("Jai Hanuman");
}

void loop() {
}



//GSM 800L

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
String phoneNumber = "+919739378190"; // Replace with your actual phone number

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