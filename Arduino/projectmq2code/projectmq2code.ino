int gasSensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  delay(1000);  // Adjust the delay based on your preferences
}