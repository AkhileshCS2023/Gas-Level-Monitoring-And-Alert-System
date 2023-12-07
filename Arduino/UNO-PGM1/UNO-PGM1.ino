//declaration
int led=LED_BUILTIN;
//setup
void setup(){
  pinMode(led,OUTPUT);
}
//loop
void loop(){
  digitalWrite(led,HIGH);
  delay(5000);
  digitalWrite(led,LOW);
  delay(5000);
}