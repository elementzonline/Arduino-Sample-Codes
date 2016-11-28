#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElementzGSM.h"

String URL = "http://ec2-52-24-224-220.us-west-2.compute.amazonaws.com/tgps.php?Data=";
SoftwareSerial myserialOut(6,7);
ElementzGSMshield GSM(&myserialOut);
String testString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Starting");
  delay(1000);

  GSM.turnOnGPRS("WWW.MYAIRTELGPRS.COM");
  GSM.turnOnGNSS();
  testString = GSM.getProcessedGNSSInfo();
  Serial.println(testString);
  GSM.sendHTTPDATA(URL + testString);
  //go to this url to view data http://ec2-52-24-224-220.us-west-2.compute.amazonaws.com/tgps808log.txt

}
void loop() {

}
