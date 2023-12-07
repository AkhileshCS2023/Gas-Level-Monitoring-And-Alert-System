const int flameSensorPin = 7; // Define the pin to which the flame sensor is connected

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(flameSensorPin, INPUT); // Set flame sensor pin as input
}

void loop() {
  int flameSensorValue = digitalRead(flameSensorPin); // Read the digital value from the flame sensor

  if (flameSensorValue == HIGH) {
    Serial.println("Flame detected!"); // Print a message if flame is detected
  } else {
    Serial.println("No flame detected."); // Print a message if no flame is detected
  }

  delay(1000); // Delay for 1 second before reading the sensor again
}
