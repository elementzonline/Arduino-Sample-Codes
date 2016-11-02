#include <Arduino.h>
#include "SoftwareSerial.h"
#include "gsm.h"

SoftwareSerial softSerial(2,3);
SoftwareSerial *gsmSerial = &softSerial;

GSM gsm;

void setup(/* arguments */) {
  /* code */
  gsm.initGSM(gsmSerial, 9600);
  Serial.begin(9600);

  delay(3000);

  gsm.SendAT(gsmSerial, "AT", "OK", 1000, 3);
 
   gsm.SendAT(gsmSerial, "AT+CREG?", "+CREG: 0,1", 1000, 3);
  


  // SendAT("ATD8129025513;", "OK", 1000, 3);
  // delay(15000);
  //
  // SendAT("ATH", "OK", 1000, 3);

}



void loop(/* arguments */) {



}
