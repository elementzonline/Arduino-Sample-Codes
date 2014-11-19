/*
IR Sensor Sample Code
Author : Jayasenan
Company : Elementz Engineers Guild Pvt Ltd

Website: http://www.elementzonline.com
*/


#define OUTPin 13 // Onboard LED
#define INPin 10 // Onboard LED
void setup() {
 Serial.begin (9600);

 pinMode(OUTPin, OUTPUT); // Use LED indicator (if required)
  pinMode(INPin, INPUT); // Use LED indicator (if required)
}
int OUT;
void loop()
{
  digitalWrite(OUTPin,LOW);
  // print the sensor values:
  OUT=digitalRead(INPin);
  Serial.print(OUT);
  // print a tab between values:
  Serial.print("\t");
  if(OUT==1){
    digitalWrite(OUTPin,HIGH);
  }  }
  
