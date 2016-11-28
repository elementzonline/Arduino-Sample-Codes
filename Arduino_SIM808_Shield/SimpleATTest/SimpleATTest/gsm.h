#ifndef GSM_H
#define GSM_H
#include <Arduino.h>
#include "SoftwareSerial.h"

#define PinRX 2
#define PinTX 3

#define DEBUG 1

class GSM{
public:
  void initGSM(SoftwareSerial *gsmSerial, unsigned long baud);
  int SendAT(SoftwareSerial *gsmSerial, const char* ATCommand,const char* exptReply, int timeout, int retry);
  int waitResponse(SoftwareSerial *gsmSerial, const char* exptReply, int timeout);
private:
};



#endif
