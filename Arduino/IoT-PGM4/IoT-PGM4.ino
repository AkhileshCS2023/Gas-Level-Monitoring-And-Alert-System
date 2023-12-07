//declaration
int led=6;
//setup
void setup(){
Serial.begin(9600);
  pinMode(led,OUTPUT);
}
//loop
void loop(){
  digitalWrite(led,HIGH);
  delay(5000);
  Serial.println("LED is on");
  digitalWrite(led,LOW);
  delay(5000);
  Serial.println("LED is off");
}