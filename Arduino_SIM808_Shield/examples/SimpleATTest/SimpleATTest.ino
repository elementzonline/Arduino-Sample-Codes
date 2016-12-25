#include <Arduino.h>
#include "SoftwareSerial.h"
#include "ElementzGSM.h"

SoftwareSerial myserialOut(6, 7);
ElementzGSMshield GSM(&myserialOut);

void setup(/* arguments */) {
  /* code */
  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Starting");
  delay(2000);

  GSM.SendAT("AT", "OK", 1000, 2);
  GSM.SendAT("AT+CREG?", "+CREG: 0,0", 1000, 2);
}



void loop(/* arguments */) {



}
