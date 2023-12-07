#include "HX711.h"

// Pin configurations
const int loadCellDataPin = 2;
const int loadCellClockPin = 3;

HX711 scale;

void setup() {
  Serial.begin(9600);

  // Initialize the HX711
  scale.begin(loadCellDataPin, loadCellClockPin);
}

void loop() {
  // Read the weight value
  float weight = scale.get_units(10);

  // Print the weight to the Serial Monitor
  Serial.print("Weight: ");
  Serial.println(weight);

  delay(500); // Adjust the delay based on your preferences
}