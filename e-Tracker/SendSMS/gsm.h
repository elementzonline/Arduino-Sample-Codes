#ifndef GSM_H
#define GSM_H
#include <Arduino.h>
#include "SoftwareSerial.h"

#define PinRX 2
#define PinTX 3

#define DEBUG 1

class GSM{
public:
   GSM(char RxPin, char TxPin)
    {
      SoftwareSerial mySerial(RxPin,TxPin);
      gsmSerial = &mySerial;
    }
  void initGSM(unsigned long BaudRate);
  int SendAT(SoftwareSerial *gsmSerial, const char* ATCommand,const char* exptReply, int timeout, int retry);
  int waitResponse(SoftwareSerial *gsmSerial, const char* exptReply, int timeout);
private:
  SoftwareSerial *gsmSerial;
};



#endif
