//Sample Code to check the working of PIR sensor
/*
  Code revision -- 02,November,2014
  Author -- Jayasenen
  
  Website: http://www.elementzonline.com
  
*/
void setup()
  {
    pinMode(13,OUTPUT);//define pin 13 as output LED pin
    pinMode(10,INPUT);//define pin 10 as input pin
    Serial.begin(9600);// initialize serial communications:
  }
  bool PIRValue;// variable to read the PIR sensor value
  void loop()
  {
    PIRValue=digitalRead(10);// read value from pin no:10
    Serial.println(PIRValue);// print value from pin no:10
    if(PIRValue==1)//check the condition for LED blinking
    {
      digitalWrite(13,HIGH);//set pin 13 to HIGH for switch on LED
      delay(1000);
      digitalWrite(13,LOW);//set pin 13 to LOW for switch off LED
      delay(1000);
      digitalWrite(13,HIGH);//set pin 13 to HIGH for switch on LED
      delay(1000);
      digitalWrite(13,LOW);//set pin 13 to LOW for switch off LED
    }
  }


