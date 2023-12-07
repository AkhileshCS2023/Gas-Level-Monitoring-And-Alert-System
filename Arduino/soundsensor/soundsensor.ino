const int soundSensorPin = A0; // Analog pin where the sound sensor is connected

void setup() {
  Serial.begin(9600); // Initialize serial communication
}
void loop() {
  int sensorValue = analogRead(soundSensorPin); // Read the analog value from the sound sensor
  Serial.print("Sound Sensor Value: ");
  Serial.println(sensorValue); // Print the sensor value to the serial monitor
  delay(1000); // Delay for 1 second (adjust as needed)
}