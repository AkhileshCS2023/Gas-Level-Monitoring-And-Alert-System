// Pin configuration
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