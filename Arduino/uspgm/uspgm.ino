//Pin configuration
const int trigPin = 12;  // GPIO pin for the trigger pin of the ultrasonic sensor
const int echoPin = 14;  // GPIO pin for the echo pin of the ultrasonic sensor
const int buzzerPin=6;
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin,OUTPUT);
}

void loop() {
  // Trigger pulse for the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters based on the speed of sound (343 meters/second)
  // Divide by 2 because the sound wave has to travel to the object and back
  float distance_cm = (duration * 0.0343) / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
    if (distance_cm < 5) {
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Wait for a short delay before taking the next measurement
  delay(1000);
}