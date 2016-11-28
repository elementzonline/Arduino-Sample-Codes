#ifndef ELEMENTZGSM_H
#define ELEMENTZGSM_H
#include <Arduino.h>
#include "SoftwareSerial.h"

#define MESSAGELINES 5
//#define PinRX 2
//#define PinTX 3

#define DEBUG 1

class ElementzGSMshield{
public:
  ElementzGSMshield(SoftwareSerial *);
//  GSM(uint8_t PinRX, uint8_t PinTX);
  void    begin(long );
  void    SendAT(String ATCommand);
  void    SendAT(const char ATCommand);
  boolean SendAT(const char* ATCommand,const char* exptReply, uint32_t timeout, int retry);
  boolean SendAT(String ATCommand,const char* exptReply, uint32_t timeout, int retry);
  boolean SendAT(String ATCommand,const char* exptReply, uint32_t timeout, int retry, uint8_t noOflines);
  boolean waitResponse(const char* exptReply, uint32_t timeout);
  boolean waitResponse(const char* exptReply, uint32_t timeout,uint8_t noOflines);
  boolean EchoOFF();
  boolean EchoON();
  String  readReply(uint32_t timeout);
  String  readReply( uint32_t timeout,uint8_t expctd_num_of_lines);
  boolean makeCall(const char* phone_number);
  boolean makeCall(String phone_number);
  boolean hangUp(void);
  boolean sendSms(const char* phone_number, const char* Content);
  boolean sendSms(String phone_number, String Content);
  String  readSMS(uint8_t index);
  boolean turnOnGPRS(String APN);
  boolean turnOnGPRS(const char* APN);
  boolean turnOffGPRS(void);
  boolean setupEmailServer(String OutGoingServer,uint16_t Port,uint8_t timeout);
  boolean setupEmailAuthorization(String Username, String Password, String Name);
  boolean setupEmailAuthorization(String Username, String Password);
  boolean setupEmailToAddress(String mailId, String Name);
  boolean setupEmailToAddress(String mailId);
  boolean setupEmailCcAddress(String mailId, String Name);
  boolean setupEmailCcAddress(String mailId);
  boolean setupEmailBccAddress(String mailId, String Name);
  boolean setupEmailBccAddress(String mailId);
  boolean setEmailSubject(String Subject);
  boolean sendEmailWithContent(String Content, uint8_t length);
  boolean sendEmailWithContent(const char* Content, uint8_t length);
  boolean turnOnGNSS(void);
  boolean turnOffGNSS(void);
  String  getGNSSInfo(void);
  boolean sendHTTPDATA(const char* URL_attached_with_data);
  boolean sendHTTPDATA(String URL_attached_with_data);
  String  getProcessedGNSSInfo(void);


private:
  boolean setupEmailFromAddress(String mailId, String Name);
  boolean setupEmailFromAddress(String mailId);
  boolean checkForExptReplyinRcvdString(String recvdString, const char* exptReply);
  boolean initializeHTTPService(void);
  boolean terminateHTTPService(void);

  Stream *mySerial;
  SoftwareSerial *gsmSerial;
};

#endif
