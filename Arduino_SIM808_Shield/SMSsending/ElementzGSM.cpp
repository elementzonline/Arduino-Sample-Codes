#include <Arduino.h>
#include "SoftwareSerial.h"
#include "ElementzGSM.h"


ElementzGSMshield::ElementzGSMshield(SoftwareSerial *serialInput)
{
  gsmSerial =  serialInput;
  mySerial =  gsmSerial;
}

void ElementzGSMshield::begin(long baudRate)
{
  gsmSerial -> begin(baudRate);
  EchoOFF();
}

static void serialFlush(Stream *gsmSerial){
  while(gsmSerial->available() > 0) {
    char t = gsmSerial->read();
    // Serial.write(t);
  }
}

boolean ElementzGSMshield::checkForExptReplyinRcvdString(String recvdString, const char* exptReply)
{
    if (strstr(recvdString.c_str(),exptReply)!=0)
    {
      #if (DEBUG == 1)
          Serial.println("Got Correct Reply");
      #endif
      recvdString = "";
      return true;
    }
    else
    {
      #if (DEBUG == 1)
          Serial.println("Got ERROR");
      #endif
      recvdString = "";
      return false;
    }

}

boolean ElementzGSMshield::waitResponse(const char* exptReply, uint32_t timeout){
      String inputString = "";
      inputString = readReply(timeout);
      #if (DEBUG == 1)
            Serial.println(inputString);
      #endif
      boolean response = checkForExptReplyinRcvdString(inputString,exptReply);
      return response;
  }

  boolean ElementzGSMshield::waitResponse(const char* exptReply, uint32_t timeout,uint8_t noOflines){
    String inputString = "";
    inputString = readReply(timeout,noOflines);
    #if (DEBUG == 1)
          Serial.println(inputString);
    #endif
    boolean response = checkForExptReplyinRcvdString(inputString,exptReply);
    return response;
  }

void ElementzGSMshield::SendAT(String ATCommand)
{
  serialFlush(mySerial);
  #if (DEBUG == 1)
  Serial.print("Sending ");
  Serial.println(ATCommand);
  #endif
  mySerial->println(ATCommand);
}

void ElementzGSMshield::SendAT(const char ATCommand)
{
  serialFlush(mySerial);
  #if (DEBUG == 1)
  Serial.print("Sending ");
  Serial.println(ATCommand);
  #endif
  mySerial->println(ATCommand);
}

boolean ElementzGSMshield::SendAT(const char* ATCommand,const char* exptReply, uint32_t timeout, int retry){
  int itr= 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while(itr++ < retry)
  { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
    #if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
    #endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply,timeout);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

boolean ElementzGSMshield::SendAT(String ATCommand,const char* exptReply, uint32_t timeout, int retry){
  int itr= 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while(itr++ < retry){ /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
    #if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
    #endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply,timeout);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

boolean ElementzGSMshield::SendAT(String ATCommand,const char* exptReply, uint32_t timeout, int retry, uint8_t noOflines){
  int itr= 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while(itr++ < retry){ /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
    #if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
    #endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply,timeout,noOflines);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

String ElementzGSMshield::readReply(uint32_t timeout)
{
    uint32_t previousTime = millis();
    String receivedString = "";
    while (millis()-previousTime<timeout)
    {
      if (mySerial->available())
      {
        char inChar = (char)mySerial->read();
        if ((inChar != '\n') && (inChar != '\r'))
        { /*Append data till enter character received*/
            receivedString += inChar;
        }
      }
  }
  return receivedString;
}

String ElementzGSMshield::readReply(uint32_t timeout, uint8_t expctd_num_of_lines)
{
  uint8_t line_number = 0;
  uint32_t previousTime = millis();
  String receivedString = "";
  while (millis()-previousTime<timeout)
  {
    if (mySerial->available())
    {
      char inChar = (char)mySerial->read();
      if ((inChar != '\n') && (inChar != '\r'))
      { /*Append data till enter character received*/
          receivedString += inChar;
      }
      else if((inChar == '\n'))
      {
        if (line_number < expctd_num_of_lines)
         {
           line_number++;
         }
         else
         {
           break;
         }
         receivedString += inChar;
      }
      else
      {
          receivedString += inChar;
          if(line_number >= expctd_num_of_lines)
          {
            break;
          }
      }
    }
}
return receivedString;

}

boolean ElementzGSMshield::EchoOFF()
{
  boolean state = SendAT("ATE0","OK",3000,2);
  return state;
}

boolean ElementzGSMshield::EchoON()
{
  boolean state = SendAT("ATE1","OK",3000,2);
  return state;
}


boolean ElementzGSMshield::makeCall(const char* phone_number)
{
  String dialString = "ATD"+String(phone_number)+";";
  boolean status = SendAT(dialString,"OK",1000,1);
  dialString = "";
  return status;
}

boolean ElementzGSMshield::makeCall(String phone_number)
{
  String dialString = "ATD"+phone_number+";";
  boolean status = SendAT(dialString,"OK",1000,1);
  dialString = "";
  return status;
}

boolean ElementzGSMshield::hangUp(void)
{
  boolean status = SendAT("ATH", "OK", 2000,1);
  return status;
}

boolean ElementzGSMshield::sendSms(const char* phone_number, const char* Content)
{

 boolean  status= SendAT("AT+CMGF=1","OK",1000,1);
 if (status == true) {
   String SMSsenderString = "AT+CMGS=\""+String(phone_number)+"\"";
   status = SendAT(SMSsenderString,"> ",2000,1);
   if (status == true) {
     mySerial->println(Content);
     mySerial->write(0x1A);
     SMSsenderString = readReply(10000);
     if (SMSsenderString == "ERROR") {
       status = false;
     }
   }
 }
 return status;
}

boolean ElementzGSMshield::sendSms(String phone_number, String Content)
{

 boolean  status= SendAT("AT+CMGF=1","OK",1000,1);
 if (status == true) {
   String SMSsenderString = "AT+CMGS=\""+phone_number+"\"";
   status = SendAT(SMSsenderString,"> ",2000,1);
   if (status == true) {
     mySerial->println(Content);
     mySerial->write(0x1A);
     SMSsenderString = readReply(60000);
     if (SMSsenderString == "ERROR") {
       status = false;
     }
   }
 }
 return status;
}

String ElementzGSMshield::readSMS(uint8_t index)
{
  String readString = "";
  boolean status= SendAT("AT+CMGF=1","OK",1000,1);
  if (status == true)
  {
    readString = "AT+CMGR="+String(index);
    SendAT(readString);
    readString = readReply(5000,MESSAGELINES);
  }
  return readString;
}

boolean ElementzGSMshield::turnOnGPRS(const char* APN)
{
  boolean GPRS_status = SendAT("AT+CGATT=0","OK",10000,1);
  if (GPRS_status == true) {
    GPRS_status = SendAT("AT+CGATT=1","OK",10000,1);
    if (GPRS_status == true) {
      GPRS_status = SendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"","OK",2000,1);
      if (GPRS_status) {
        GPRS_status = SendAT("AT+SAPBR=3,1,\"APN\",\""+String(APN)+"\"","OK",2000,1);
        if (GPRS_status) {
          GPRS_status = SendAT("AT+SAPBR=1,1","OK",2000,1);
        }
      }
    }
  }
  return GPRS_status;
}

boolean ElementzGSMshield::turnOnGPRS(String APN)
{
  boolean GPRS_status = SendAT("AT+CGATT=0","OK",10000,1);
  if (GPRS_status == true) {
    GPRS_status = SendAT("AT+CGATT=1","OK",10000,1);
    if (GPRS_status == true) {
      GPRS_status = SendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"","OK",2000,1);
      if (GPRS_status) {
        GPRS_status = SendAT("AT+SAPBR=3,1,\"APN\",\""+APN+"\"","OK",2000,1);
        if (GPRS_status) {
          GPRS_status = SendAT("AT+SAPBR=1,1","OK",2000,1);
        }
      }
    }
  }
  return GPRS_status;
}

boolean ElementzGSMshield::turnOffGPRS(void)
{
  boolean GPRS_status = SendAT("AT+CGATT=0","OK",10000,1);
  return GPRS_status;
}

boolean ElementzGSMshield::setupEmailServer(String OutGoingServer,uint16_t Port,uint8_t emailtimeout)
{
  boolean email_status = SendAT("AT+EMAILCID=1","OK",2000,1);
  if (email_status == true)
  {
    email_status = SendAT("AT+EMAILTO="+String(emailtimeout),"OK",2000,1);
    if (email_status == true)
     {
      email_status = SendAT("AT+SMTPSRV=\""+OutGoingServer+"\","+String(Port),"OK",2000,1);
    }
  }
  return email_status;
}

boolean ElementzGSMshield::setupEmailAuthorization(String Username, String Password, String Name)
{
  boolean email_status = SendAT("AT+SMTPAUTH=1,\""+Username+"\",\""+Password+"\"","OK",2000,1);
  if (email_status == true) {
    email_status = setupEmailFromAddress(Username,Name);
  }
  return email_status;

}

boolean ElementzGSMshield::setupEmailAuthorization(String Username, String Password)
{
  boolean email_status = SendAT("AT+SMTPAUTH=1,\""+Username+"\",\""+Password+"\"","OK",2000,1);
  if (email_status == true) {
    email_status = setupEmailFromAddress(Username);
  }
  return email_status;

}

boolean ElementzGSMshield::setupEmailFromAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPFROM=\""+mailId+"\",\""+Name+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailFromAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPFROM=\""+mailId+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailToAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=0,0,\""+mailId+"\",\""+Name+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailToAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=0,0,\""+mailId+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailCcAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=1,0,\""+mailId+"\",\""+Name+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailCcAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=1,0,\""+mailId+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailBccAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=2,0,\""+mailId+"\",\""+Name+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailBccAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=2,0,\""+mailId+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::setEmailSubject(String Subject)
{
  boolean email_status = SendAT("AT+SMTPSUB=\""+Subject+"\"","OK",2000,1);
  return email_status;
}

boolean ElementzGSMshield::sendEmailWithContent(String Content, uint8_t length)
{
  boolean email_status = false;
  if (Content.length()==length)
  {
    email_status = SendAT("AT+SMTPBODY="+String(length),"DOWNLOAD",2000,1);
    if (email_status == true)
    {
      mySerial->println(Content);
      if (readReply(2000) == "OK")
      {
        email_status = SendAT("AT+SMTPSEND","OK",2000,1);
        if (email_status == true) {
          String replyString = readReply((120000));
          if (replyString == "+SMTPSEND: 1")
          {
            Serial.println("Mail Send Succesfully");
          }
        }
      }
    }
  }
  else
  {
    Serial.print("Content length doesn't match given length");
    email_status = false;
  }
  return email_status;
}

boolean ElementzGSMshield::sendEmailWithContent(const char* Content, uint8_t length)
{
  boolean email_status = false;
  if (strlen(Content)==length)
  {
    email_status = SendAT("AT+SMTPBODY="+String(length),"DOWNLOAD",2000,1);
    if (email_status == true)
    {
      mySerial->println(Content);
      if (readReply(2000) == "OK")
      {
        email_status = SendAT("AT+SMTPSEND","OK",2000,1);
        if (email_status == true) {
          String replyString = readReply(120000);
          if (replyString == "+SMTPSEND: 1")
          {
            Serial.println("Mail Send Succesfully");
          }
        }
      }
    }
  }
  else
  {
    Serial.print("Content length doesn't match given length");
    email_status = false;
  }
  return email_status;
}

boolean ElementzGSMshield::turnOnGNSS(void)
{
  boolean gnss_stat = SendAT("AT+CGNSPWR=1","OK",2000,1);
  return gnss_stat;
}

boolean ElementzGSMshield::turnOffGNSS(void)
{
  boolean gnss_stat = SendAT("AT+CGNSPWR=0","OK",2000,1);
  return gnss_stat;
}

String ElementzGSMshield::getGNSSInfo(void)
{
  SendAT("AT+CGNSINF");
  String infoString = readReply(5000,5);
  return infoString;
}

String ElementzGSMshield::getProcessedGNSSInfo(void)
{
  SendAT("AT+CGNSINF");
  String infoString = readReply(5000,5);
  infoString.replace("\r\n\r\nOK\r\n","");
  infoString.replace("\r\n+CGNSINF","GNSINFO");
  return infoString;
}

boolean ElementzGSMshield::initializeHTTPService(void)
{
  boolean http_status = SendAT("AT+HTTPINIT","OK",1000,1);
  if (http_status == true)
  {
    http_status = SendAT("AT+HTTPPARA=\"CID\",1", "OK",2000,1);
  }
  return http_status;

}

boolean ElementzGSMshield::terminateHTTPService(void)
{
  boolean http_status = SendAT("AT+HTTPTERM","OK",1000,1);
  return http_status;
}

boolean ElementzGSMshield::sendHTTPDATA(const char* URL_attached_with_data)
{
  boolean http_status = initializeHTTPService();
  if (http_status == true )
  {
     http_status = SendAT("AT+HTTPPARA=\"URL\",\""+String(URL_attached_with_data)+"\"","OK",10000,1);
     if (http_status == true)
     {
       http_status = SendAT("AT+HTTPACTION=0","200",10000,1);
     }
  }

  terminateHTTPService();
  return http_status;
}

boolean ElementzGSMshield::sendHTTPDATA(String URL_attached_with_data)
{
  boolean http_status = initializeHTTPService();
  if (http_status == true )
  {
     http_status = SendAT("AT+HTTPPARA=\"URL\",\""+URL_attached_with_data+"\"","OK",10000,1);
     if (http_status == true)
     {
       http_status = SendAT("AT+HTTPACTION=0","200",10000,1);
     }
  }

  terminateHTTPService();
  return http_status;
}
