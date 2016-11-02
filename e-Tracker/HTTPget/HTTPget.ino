#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElementzGSM.h"


SoftwareSerial myserialOut(3,2);
ElementzGSMshield GSM(&myserialOut);

void setup() {
 
  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Starting");
  delay(1000);

  GSM.turnOnGPRS("WWW.MYAIRTELGPRS.COM");
  GSM.sendHTTPDATA("http://ec2-52-24-224-220.us-west-2.compute.amazonaws.com/tgps.php?Data=thisisanewdata");
  //check this url to view data http://ec2-52-24-224-220.us-west-2.compute.amazonaws.com/tgps808log.txt

}
void loop() {

}
