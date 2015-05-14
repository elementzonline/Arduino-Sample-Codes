/*
Gas sensor Sample Code
Author : Dhanish
Company : Elementz Engineers Guild Pvt Ltd

Website: http://www.elementzonline.com
*/



#define SensorPin A5// Gas sensor input

void setup() {
 Serial.begin (9600);
 pinMode(SensorPin, INPUT);
}


void loop()
{
  // print the sensor values:
  Serial.println(analogRead(SensorPin));
  // delay before next reading:
  delay(1000);
}
