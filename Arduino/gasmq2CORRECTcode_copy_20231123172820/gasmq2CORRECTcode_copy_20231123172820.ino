
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