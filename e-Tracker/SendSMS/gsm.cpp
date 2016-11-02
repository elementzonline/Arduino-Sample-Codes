#include <Arduino.h>
#include <SoftwareSerial.h>
#include "gsm.h"

 
//void GSM::initGSM(SoftwareSerial *gsmSerial, unsigned long baud) {
//  gsmSerial->begin(baud);
//}



void GSM::initGSM(unsigned long BaudRate)
{
  gsmSerial -> begin(BaudRate);
}

static void serialFlush(SoftwareSerial *gsmSerial) {
  while (gsmSerial->available() > 0) {
    char t = gsmSerial->read();
    // Serial.write(t);
  }
}

int GSM::waitResponse(SoftwareSerial *gsmSerial, const char* exptReply, int timeout) {
  uint16_t previousTime = millis();
  String inputString = "";
  while ((millis() - previousTime) < timeout) { /*Loop till the timeout occurs*/
    if (gsmSerial->available()) {
      char inChar = (char)gsmSerial->read();
      if ((inChar != '\n') && (inChar != '\r')) { /*Append data till enter character received*/
        inputString += inChar;
      }
      else {/*enter string comparison when we get enter character*/
#if (DEBUG == 1)
        Serial.println(inputString);
#endif
        if (inputString.substring(0) == exptReply) {
#if (DEBUG == 1)
          Serial.println("Got OK");
#endif
          return 1;
        }
        else if (inputString.substring(0) == "ERROR") {
#if (DEBUG == 1)
          Serial.println("Got ERROR");
          return 0;
#endif
        }
        inputString = "";
      }
    }
  }
}

int GSM::SendAT(SoftwareSerial *gsmSerial, const char* ATCommand, const char* exptReply, int timeout, int retry) {
  int itr = 0;
  serialFlush(gsmSerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry) { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
#endif
    gsmSerial->println(ATCommand); /*Send AT command to the GSM RX pin*/

    if (waitResponse(gsmSerial, exptReply, timeout)) {
      return 1;
    }

  }

  return -1;
}

//int GSM::SendSMS()
