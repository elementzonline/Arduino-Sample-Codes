#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElementzGSM.h"

char phone_number[11] = "9605xxxxxx";
String phone2 = "7356xxxxxx";
SoftwareSerial myserialOut(3, 2);
ElementzGSMshield GSM(&myserialOut);
String testString = "";
void setup() {
  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Starting");
  delay(1000);
  Serial.println("Calling First Number");
  GSM.makeCall(phone_number);//number const char type
  delay(10000);
  Serial.println("Disconnecting First call");
  GSM.hangUp();
  Serial.println("Calling Second Number");
  GSM.makeCall(phone2);//number is string type
  delay(10000);
  Serial.println("Disconnecting Second call");
  GSM.hangUp();



}

void loop() {

}
