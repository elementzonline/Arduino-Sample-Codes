/*
ADXL335 Sample Code
Author : Jayasenan
Company : Elementz Engineers Guild Pvt Ltd

Website: http://www.elementzonline.com
*/



#define XPin A2// X Pin
#define YPin A3// Y Pin
#define ZPin A4// Z Pin

void setup() {
 Serial.begin (9600);
 pinMode(XPin, INPUT);
 pinMode(YPin, INPUT);
 pinMode(ZPin, INPUT); 
}


void loop()
{
  // print the sensor values:
  Serial.print(analogRead(XPin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(YPin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ZPin));
  Serial.println();
  // delay before next reading:
  delay(1000);
}
