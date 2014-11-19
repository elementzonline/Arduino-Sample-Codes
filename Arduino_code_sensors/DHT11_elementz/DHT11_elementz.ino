
/*
DHT11 Sample Code
Author : Jayasenan
Company : Elementz Engineers Guild Pvt Ltd

Website: http://www.elementzonline.com
*/



#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);

  dht.setup(6); // data pin 2
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  Serial.print(dht.getHumidity());
  Serial.print("\t");
  Serial.println(dht.getTemperature());
}
