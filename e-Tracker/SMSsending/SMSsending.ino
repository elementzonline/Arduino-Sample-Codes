#include <Arduino.h>
#include <SoftwareSerial.h>
 #include "ElementzGSM.h"


SoftwareSerial myserialOut(2,3);
ElementzGSMshield GSM(&myserialOut);
String testString = "";
void setup() {
  Serial.begin(9600);
   GSM.begin(9600);
  Serial.println("Starting");
  delay(1000);
  
   boolean sms_status = GSM.sendSms("7356xxxxxx", "Test Message");//you can input the number also as a String object 
   if (sms_status == true)
   {
     Serial.println("SMS Send");
   }
   else
   {
     Serial.println("SMS sending Failed");
   }
 

  

}

void loop() {

}
