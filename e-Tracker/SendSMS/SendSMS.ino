#include <Arduino.h>
#include <SoftwareSerial.h>
#include "gsm.h"

GSM gsm(2,3);
void setup() {
  // put your setup code here, to run once:
  gsm.initGSM(9600);
  gsm.initGSM(*gsmSerial, baud)

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
