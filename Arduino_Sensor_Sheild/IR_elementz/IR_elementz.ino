/*
IR Sensor Sample Code
Author : Jayasenan
Company : Elementz Engineers Guild Pvt Ltd

Website: http://www.elementzonline.com
*/


#define OUTPin 13 // Onboard LED
#define INPin1 0 // 0 for IR1
#define INPin2 10 // 10 for IR2

void setup() {
 Serial.begin (9600);

 pinMode(OUTPin, OUTPUT); // Use LED indicator (if required)
  pinMode(INPin1, INPUT); // Use LED indicator (if required)
  pinMode(INPin2, INPUT); // Use LED indicator (if required)
}
int OUT;
void loop()
{
  delay(500);
  digitalWrite(OUTPin,LOW);
  // print the sensor values:
  OUT=digitalRead(INPin1);
  Serial.print(OUT);
  Serial.print("\t");
  OUT=digitalRead(INPin2);
  Serial.print(OUT);
  // print a tab between values:
  Serial.print("\n");
  if(OUT==1){
    digitalWrite(OUTPin,HIGH);
  }  }
  
