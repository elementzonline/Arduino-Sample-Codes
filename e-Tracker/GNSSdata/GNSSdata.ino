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
  GSM.turnOnGNSS();
  String testString = GSM.getGNSSInfo();
  Serial.println(testString);
  GSM.turnOffGNSS();

}

void loop() {

}
