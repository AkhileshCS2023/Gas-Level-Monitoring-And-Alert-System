#include <HX711.h>
HX711 scale;

#define DT A0
#define SCK A1
#define sw 9

const uint8_t gramm = 1;
const uint16_t kilogramm = 1000 * gramm;

long sample=0;
float val=0;
long count=0;

unsigned long readCount(void)
{
unsigned long Count;
unsigned char i;
pinMode(DT, OUTPUT);
digitalWrite(DT,HIGH);
digitalWrite(SCK,LOW);
Count=0;
pinMode(DT, INPUT);
while(digitalRead(DT));
for (i=0;i<24;i++)
{
digitalWrite(SCK,HIGH);
Count=Count<<1;
digitalWrite(SCK,LOW);
if(digitalRead(DT))
Count++;
}
digitalWrite(SCK,HIGH);
Count=Count^0x800000;
digitalWrite(SCK,LOW);
return(Count);
}

void setup()
{
pinMode(13, OUTPUT);
pinMode(SCK, OUTPUT);
pinMode(sw, INPUT_PULLUP);
Serial.print(" Weight ");
Serial.print(" Measurement ");
delay(1000);
calibrate();
}

void loop()
{

 if (scale.get_units() <= 250)
 {
   digitalWrite(13, HIGH);
    }
  else {
       digitalWrite(13, LOW);
          }
count= readCount();
int w=(((count-sample)/val)-2*((count-sample)/val));

Serial.print("Measured Weight");
Serial.print(w);
Serial.print("g ");

if(digitalRead(sw)==0)
{
val=0;
sample=0;
w=0;
count=0;
calibrate();
}
}

void calibrate()
{
Serial.print("Calibrating...");
Serial.print("Please Wait...");
for(int i=0;i<100;i++)
{
count=readCount();
sample+=count;
}
sample/=100;
Serial.print("Put 100g & wait");
count=0;
while(count<1000)
{
count=readCount();
count=sample-count;
}
Serial.print("Please Wait....");
delay(2000);
for(int i=0;i<100;i++)
{
count=readCount();
val+=sample-count;
}
val=val/100.0;
val=val/100.0; // put here your calibrating weight
}