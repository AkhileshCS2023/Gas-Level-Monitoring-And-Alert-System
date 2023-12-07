//declaration
int led=42;
//setup
void setup(){ 
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}
//loop
void loop(){
  digitalWrite(led,HIGH);
  Serial.println("LED is on");
  delay(5000);
  digitalWrite(led,LOW);
  Serial.println("LED is off");
  delay(5000);
}