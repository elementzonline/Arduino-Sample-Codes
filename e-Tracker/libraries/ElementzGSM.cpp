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

static void serialFlush(Stream *gsmSerial) {
  while (gsmSerial->available() > 0) {
    char t = gsmSerial->read();
    // Serial.write(t);
  }
}

boolean ElementzGSMshield::checkForExptReplyinRcvdString(String recvdString, const char* exptReply)
{
  if (strstr(recvdString.c_str(), exptReply) != 0)
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

boolean ElementzGSMshield::waitResponse(const char* exptReply, uint32_t timeout) {
  String inputString = "";
  inputString = readReply(timeout);
#if (DEBUG == 1)
  Serial.println(inputString);
#endif
  boolean response = checkForExptReplyinRcvdString(inputString, exptReply);
  return response;
}

boolean ElementzGSMshield::waitResponse(const char* exptReply, uint32_t timeout, uint8_t noOflines) {
  String inputString = "";
  inputString = readReply(timeout, noOflines);
#if (DEBUG == 1)
  Serial.println(inputString);
#endif
  boolean response = checkForExptReplyinRcvdString(inputString, exptReply);
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

boolean ElementzGSMshield::SendAT(const char* ATCommand, const char* exptReply, uint32_t timeout, int retry) {
  int itr = 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry)
  { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
#endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply, timeout);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

boolean ElementzGSMshield::SendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry) {
  int itr = 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry) { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
#endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply, timeout);
    if (status == true)
    {
      return true;
    }
  }
  return false;
}

boolean ElementzGSMshield::SendAT(String ATCommand, const char* exptReply, uint32_t timeout, int retry, uint8_t noOflines) {
  int itr = 0;
  serialFlush(mySerial); /*Flush all the pending inputs in serial buffer*/
  while (itr++ < retry) { /*wait for this many times till we get exptReply*/
    delay(100); /*wait for minimum before sending next AT command*/
#if (DEBUG == 1)
    Serial.print("Sending ");
    Serial.println(ATCommand);
#endif
    mySerial->println(ATCommand); /*Send AT command to the GSM RX pin*/
    boolean status = waitResponse(exptReply, timeout, noOflines);
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
  while (millis() - previousTime < timeout)
  {
    if (mySerial->available())
    {
      char inChar = (char)mySerial->read();
      if ((inChar != '\n') && (inChar != '\r'))
      { /*Append data till enter character received*/
        receivedString += inChar;
      }
      else
      {
        return receivedString;
      }
    }
  }

}

String ElementzGSMshield::readReply(uint32_t timeout, uint8_t expctd_num_of_lines)
{
  uint8_t line_number = 0;
  uint32_t previousTime = millis();
  String receivedString = "";
  while (millis() - previousTime < timeout)
  {
    if (mySerial->available())
    {
      char inChar = (char)mySerial->read();
      if ((inChar != '\n') && (inChar != '\r'))
      { /*Append data till enter character received*/
        receivedString += inChar;
      }
      else if ((inChar == '\n'))
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
      else if (inChar == '\r')
      {
        receivedString += inChar;
        if (line_number >= expctd_num_of_lines)
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
  boolean state = SendAT("ATE0", "OK", 3000, 2, 1);
  return state;
}

boolean ElementzGSMshield::EchoON()
{
  boolean state = SendAT("ATE1", "OK", 3000, 2, 1);
  return state;
}


boolean ElementzGSMshield::makeCall(const char* phone_number)
{
  String dialString = "ATD" + String(phone_number) + ";";
  boolean status = SendAT(dialString, "OK", 1000, 1, 1);
  dialString = "";
  return status;
}

boolean ElementzGSMshield::makeCall(String phone_number)
{
  String dialString = "ATD" + phone_number + ";";
  boolean status = SendAT(dialString, "OK", 1000, 1, 1);
  dialString = "";
  return status;
}

boolean ElementzGSMshield::hangUp(void)
{
  boolean status = SendAT("ATH", "OK", 2000, 1, 1);
  return status;
}

boolean ElementzGSMshield::sendSMSintextFormat(void)
{
  boolean  status = SendAT("AT+CMGF=1", "OK", 1000, 1, 1);
  return status;
}

boolean ElementzGSMshield::sendSMSinPDUformat(void)
{
  boolean  status = SendAT("AT+CMGF=0", "OK", 1000, 1, 1);
  return status;
}

boolean ElementzGSMshield::sendSms(const char* phone_number, const char* Content)
{

  boolean  status = false;
  String SMSsenderString = "AT+CMGS=\"" + String(phone_number) + "\"";
  status = SendAT(SMSsenderString, "> ", 500, 1, 1);
  if (status == true) {
    mySerial->println(Content);
    mySerial->write(0x1A);
    SMSsenderString = readReply(10000);
    if (SMSsenderString == "ERROR") {
      status = false;
    }
  }

  return status;
}

boolean ElementzGSMshield::sendSms(String phone_number, String Content)
{

  boolean  status = false;
  String SMSsenderString = "AT+CMGS=\"" + phone_number + "\"";
  status = SendAT(SMSsenderString, "> ", 500, 1, 1);
  if (status == true) {
    mySerial->println(Content);
    mySerial->write(0x1A);
    SMSsenderString = readReply(60000);
    if (SMSsenderString == "ERROR") {
      status = false;
    }
  }
  return status;
}

String ElementzGSMshield::readSMS(uint8_t index)
{
  String readString = "";
  readString = "AT+CMGR=" + String(index);
  SendAT(readString);
  readString = readReply(5000, MESSAGELINES);
  return readString;
}

boolean ElementzGSMshield::turnOnGPRS(const char* APN)
{
  boolean GPRS_status = turnOffGPRS();
  if (GPRS_status == true) {
    GPRS_status = SendAT("AT+CGATT=1", "OK", 10000, 1, 1);
    if (GPRS_status == true) {
      GPRS_status = SendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000, 1, 1);
      if (GPRS_status) {
        GPRS_status = SendAT("AT+SAPBR=3,1,\"APN\",\"" + String(APN) + "\"", "OK", 2000, 1, 1);
        if (GPRS_status) {
          GPRS_status = SendAT("AT+SAPBR=1,1", "OK", 85000, 1, 1);
        }
      }
    }
  }
  return GPRS_status;
}

boolean ElementzGSMshield::turnOnGPRS(String APN)
{
  boolean GPRS_status = turnOffGPRS();
  if (GPRS_status == true) {
    GPRS_status = SendAT("AT+CGATT=1", "OK", 10000, 1, 1);
    if (GPRS_status == true) {
      GPRS_status = SendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000, 1, 1);
      if (GPRS_status) {
        GPRS_status = SendAT("AT+SAPBR=3,1,\"APN\",\"" + APN + "\"", "OK", 2000, 1, 1);
        if (GPRS_status) {
          GPRS_status = SendAT("AT+SAPBR=1,1", "OK", 85000, 1, 1);
        }
      }
    }
  }
  return GPRS_status;
}

boolean ElementzGSMshield::checkGprsStatus(void)
{
  boolean gprsStatus = false;
  gprsStatus = SendAT("AT+SAPBR=2,1", "+SAPBR: 1,1", 2000, 1, 1);
  return gprsStatus;
}

boolean ElementzGSMshield::turnOffGPRS(void)
{
  boolean GPRS_status = checkGprsStatus();
  if (GPRS_status == true)
  {
    GPRS_status = SendAT("AT+SAPBR=0,1", "OK", 65000, 1, 1);
  }
  GPRS_status = SendAT("AT+CGATT=0", "OK", 10000, 1, 1);

  return GPRS_status;
}

boolean ElementzGSMshield::setupEmailServer(String OutGoingServer, uint16_t Port, uint8_t emailtimeout)
{
  boolean email_status = SendAT("AT+EMAILCID=1", "OK", 2000, 1, 1);
  if (email_status == true)
  {
    email_status = SendAT("AT+EMAILTO=" + String(emailtimeout), "OK", 2000, 1, 1);
    if (email_status == true)
    {
      email_status = SendAT("AT+SMTPSRV=\"" + OutGoingServer + "\"," + String(Port), "OK", 2000, 1, 1);
    }
  }
  return email_status;
}

boolean ElementzGSMshield::setupEmailAuthorization(String Username, String Password, String Name)
{
  boolean email_status = SendAT("AT+SMTPAUTH=1,\"" + Username + "\",\"" + Password + "\"", "OK", 2000, 1, 1);
  if (email_status == true) {
    email_status = setupEmailFromAddress(Username, Name);
  }
  return email_status;

}

boolean ElementzGSMshield::setupEmailAuthorization(String Username, String Password)
{
  boolean email_status = SendAT("AT+SMTPAUTH=1,\"" + Username + "\",\"" + Password + "\"", "OK", 2000, 1, 1);
  if (email_status == true) {
    email_status = setupEmailFromAddress(Username);
  }
  return email_status;

}

boolean ElementzGSMshield::setupEmailFromAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPFROM=\"" + mailId + "\",\"" + Name + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailFromAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPFROM=\"" + mailId + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailToAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=0,0,\"" + mailId + "\",\"" + Name + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailToAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=0,0,\"" + mailId + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailCcAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=1,0,\"" + mailId + "\",\"" + Name + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailCcAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=1,0,\"" + mailId + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailBccAddress(String mailId, String Name)
{
  boolean email_status = SendAT("AT+SMTPRCPT=2,0,\"" + mailId + "\",\"" + Name + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setupEmailBccAddress(String mailId)
{
  boolean email_status = SendAT("AT+SMTPRCPT=2,0,\"" + mailId + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::setEmailSubject(String Subject)
{
  boolean email_status = SendAT("AT+SMTPSUB=\"" + Subject + "\"", "OK", 2000, 1, 1);
  return email_status;
}

boolean ElementzGSMshield::sendEmailWithContent(String Content, uint8_t length)
{
  boolean email_status = false;
  if (Content.length() == length)
  {
    email_status = SendAT("AT+SMTPBODY=" + String(length), "DOWNLOAD", 2000, 1, 1);
    if (email_status == true)
    {
      mySerial->println(Content);
      String replyString = readReply(2000, 2);
      if (strstr(replyString.c_str(), "OK") != 0)
      {
        replyString = "";
        email_status = SendAT("AT+SMTPSEND", "OK", 2000, 1, 1);
        if (email_status == true) {
          replyString = readReply(120000, 2);
          Serial.println(replyString);
          if (strstr(replyString.c_str(), "+SMTPSEND: 1") != 0)
          {
            Serial.println("Mail Send Successfully");
          }
          else
          {
            email_status = false;
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
  if (strlen(Content) == length)
  {
    email_status = SendAT("AT+SMTPBODY=" + String(length), "DOWNLOAD", 2000, 1, 1);
    if (email_status == true)
    {
      mySerial->println(Content);
      String replyString = readReply(2000, 2);
      if (strstr(replyString.c_str(), "OK") != 0)
      {
        replyString = "";
        email_status = SendAT("AT+SMTPSEND", "OK", 2000, 1, 1);
        if (email_status == true) {
          replyString = readReply(120000, 2);
          Serial.println(replyString);
          if (strstr(replyString.c_str(), "+SMTPSEND: 1") != 0)
          {
            Serial.println("Mail Send Successfully");
          }
          else
          {
            email_status = false;
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
  boolean gnss_stat = SendAT("AT+CGNSPWR=1", "OK", 2000, 1, 1);
  return gnss_stat;
}

boolean ElementzGSMshield::turnOffGNSS(void)
{
  boolean gnss_stat = SendAT("AT+CGNSPWR=0", "OK", 2000, 1, 1);
  return gnss_stat;
}

String ElementzGSMshield::getGNSSInfo(void)
{
  SendAT("AT+CGNSINF");
  String infoString = readReply(5000, 5);
  return infoString;
}

String ElementzGSMshield::getProcessedGNSSInfo(void)
{
  SendAT("AT+CGNSINF");
  String infoString = readReply(5000, 5);
  infoString.replace("\r\n\r\nOK\r\n", "");
  infoString.replace("\r\n+CGNSINF", "GNSINFO");
  return infoString;
}

boolean ElementzGSMshield::initializeHTTPService(void)
{
  boolean http_status = SendAT("AT+HTTPINIT", "OK", 1000, 1, 1);
  if (http_status == true)
  {
    http_status = SendAT("AT+HTTPPARA=\"CID\",1", "OK", 2000, 1, 1);
  }
  return http_status;

}

boolean ElementzGSMshield::terminateHTTPService(void)
{
  boolean http_status = SendAT("AT+HTTPTERM", "OK", 1000, 1, 1);
  return http_status;
}

boolean ElementzGSMshield::sendHTTPDATA(const char* URL_attached_with_data)
{
  boolean http_status = initializeHTTPService();
  if (http_status == true )
  {
    http_status = SendAT("AT+HTTPPARA=\"URL\",\"" + String(URL_attached_with_data) + "\"", "OK", 10000, 1, 1);
    if (http_status == true)
    {
      http_status = SendAT("AT+HTTPACTION=0", "200", 10000, 1, 3);
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
    http_status = SendAT("AT+HTTPPARA=\"URL\",\"" + URL_attached_with_data + "\"", "OK", 10000, 1, 1);
    if (http_status == true)
    {
      http_status = SendAT("AT+HTTPACTION=0", "200", 10000, 1, 3);
    }
  }

  terminateHTTPService();
  return http_status;
}

//--------------------------modified---------------------------------//

boolean ElementzGSMshield::restartGSMmodem(void)
{
  boolean restartStatus = false;
  restartStatus = SendAT("AT+CFUN=1,1", "OK", 1000, 1, 1);
  return restartStatus;
}

boolean ElementzGSMshield::urgentPowerDown(void)
{
  boolean shutdownStatus = false;
  shutdownStatus = SendAT("AT+CPOWD=0", "OK", 1000, 1, 1);
  return shutdownStatus;
}

boolean ElementzGSMshield::normalPowerDown(void)
{
  boolean shutdwonStatus = false;
  shutdwonStatus = SendAT("AT+CPOWD=1", "OK", 1000, 1, 1);
  return shutdwonStatus;
}

boolean ElementzGSMshield::writeTomemory(void)
{
  boolean writeTomemoryStatus = false;
  writeTomemoryStatus = SendAT("AT&W", "OK", 1000, 1, 1);
  return writeTomemoryStatus;
}

boolean ElementzGSMshield::checkSDmode(void)
{
  return SendAT("AT+SDMODE?", "+SDMODE: 1", 1000, 1, 1);
}

boolean ElementzGSMshield::prepareForSDcard(void)
{
  boolean sdStatus = false;
  sdStatus = SendAT("AT+SDMODE=1", "OK", 1000, 1, 1);
  if (sdStatus == true)
  {
    sdStatus = writeTomemory();
    if (sdStatus == true)
    {
      sdStatus = restartGSMmodem();
    }

  }
  return sdStatus;
}

char ElementzGSMshield::getDriveLabel(char requiredDrive)
{
  /*Type LOCAL for Local drive or SD for SD card*/
  if (requiredDrive == SDCARD)
  {
    SendAT("AT+FSDRIVE=1");
  }
  else
  {
    SendAT("AT+FSDRIVE=0");
  }

  String driveLabel = readReply(2000, 3);
#if (DEBUG == 1)
  Serial.println(driveLabel);
#endif
  if (strstr(driveLabel.c_str(), "+FSDRIVE") != 0)
  {
    driveLabel.replace("\r\n+FSDRIVE: ", "");
    driveLabel.replace("\r\n\r\nOK", "");
    char drive[2];
    driveLabel.toCharArray(drive, 2);
    return drive[0];
  }
  return 0;
}

void ElementzGSMshield::viewFileStorageMemoryInfo(void)
{
  SendAT("AT+FSMEM");
  String memoryInfo = readReply(5000, 3);
  memoryInfo.replace("\r\n+FSMEM: ", "");
  memoryInfo.replace("\r\n\r\nOK", "");
  Serial.println(memoryInfo);
}

boolean ElementzGSMshield::createFile(char path, const char *fileName)
{

  boolean fileCreationStatus = false;
  if (strlen(fileName) <= 63)
  {
    fileCreationStatus = SendAT("AT+FSCREATE=" + String(path) + ":\\" + String(fileName), "OK", 2000, 1, 1);

  }
  else
  {
    Serial.println("File Name length exceeds maximum");
  }

  return fileCreationStatus;
}

boolean ElementzGSMshield::createFile(const char *path, const char *fileName)
{
  boolean fileCreationStatus = false;
  if ((strlen(path) + strlen(fileName)) <= 64)
  {
    fileCreationStatus = SendAT("AT+FSCREATE=" + String(path) + String(fileName), "OK", 2000, 1, 1);
  }
  else
  {
    Serial.println("File Name length exceeds maximum");
  }

  return fileCreationStatus;
}

boolean ElementzGSMshield::createDirectory(char path, const char *directoryname)
{
  boolean directoryCreationStatus = false;
  if (strlen(directoryname) <= 63)
  {
    directoryCreationStatus =  SendAT("AT+FSMKDIR=" + String(path) + ":\\" + String(directoryname), "OK", 2000, 1, 1);
  }
  else
  {
    Serial.println("Directory Name length exceeds maximum");
  }

  return directoryCreationStatus;
}

boolean ElementzGSMshield::createDirectory(const char *path, const char *directoryname)
{
  boolean directoryCreationStatus = false;
  if (strlen(path) + strlen(directoryname) <= 64)
  {
    directoryCreationStatus = SendAT("AT+FSMKDIR=" + String(path) + String(directoryname), "OK", 2000, 1, 1);
  }
  else
  {
    Serial.println("Directory Name length exceeds maximum");
  }

  return directoryCreationStatus;
}

void ElementzGSMshield::viewFilelist(char path, char noOffiles)
{
  SendAT("AT+FSLS=" + String(path) + ":\\");
  Serial.println(readReply(10000, noOffiles));
}

void ElementzGSMshield::viewFilelist(const char *path, char noOffiles)
{
  SendAT("AT+FSLS=" + String(path));
  Serial.println(readReply(10000, noOffiles));
}

boolean ElementzGSMshield::renameFile(const char *oldNamewithPath, const char *newNamewithPath)
{
  boolean renamingStatus = SendAT("AT+FSRENAME=" + String(oldNamewithPath) + "," + String(newNamewithPath), "OK", 2000, 1, 1);
  return renamingStatus;
}

boolean ElementzGSMshield::removeDirectory(const char *directoryNameWithPath)
{
  boolean removingStatus = SendAT("AT+FSRMDIR=" + String(directoryNameWithPath), "OK", 2000, 1, 1);
  return removingStatus;
}

boolean ElementzGSMshield::removeFile(const char *fileNameWithPath)
{
  boolean removingStatus = SendAT("AT+FSDEL=" + String(fileNameWithPath), "OK", 2000, 1, 1);
  return removingStatus;
}

boolean ElementzGSMshield::writeTotheBeginningofFile(const char *fileNameWithPath, const char *Content, uint16_t sizeOftheFile, uint8_t timeInSeconds)
{
  boolean writingStatus = false;
  if (sizeOftheFile <= 10240)
  {
    if (strlen(Content) == sizeOftheFile)
    {
      writingStatus = SendAT("AT+FSWRITE=" + String(fileNameWithPath) + ",0," + String(sizeOftheFile) + "," + String(timeInSeconds), ">", 500, 1, 1);
      if (writingStatus == true)
      {
        mySerial->print(Content);
        String replyString = readReply(2000, 1);
#if (DEBUG == 1)
        Serial.println(replyString);
#endif
        if (strstr(replyString.c_str(), "OK") != 0)
        {
          writingStatus = true ;
        }
        else
        {
          writingStatus = false;
        }
        replyString = "";
      }

    }
    else
    {
      Serial.println("Size mismatch");
    }

  }
  else
  {
    Serial.println("Size exceeds Maximum");
  }
  return writingStatus;
}

boolean ElementzGSMshield::appendContenttoTheEndoftheFile(const char *fileNameWithPath, const char *Content, uint16_t sizeOftheFile, uint8_t timeInSeconds)
{
  boolean writingStatus = false;
  if (sizeOftheFile <= 10240)
  {
    if (strlen(Content) == sizeOftheFile)
    {
      writingStatus = SendAT("AT+FSWRITE=" + String(fileNameWithPath) + ",1," + String(sizeOftheFile) + "," + String(timeInSeconds), ">", 500, 1, 1);
      if (writingStatus == true)
      {
        mySerial->print(Content);
        String replyString = readReply(2000, 1);
#if (DEBUG == 1)
        Serial.println(replyString);
#endif
        if (strstr(replyString.c_str(), "OK") != 0)
        {
          writingStatus = true;
        }
        else
        {
          writingStatus = false;
        }
        replyString = "";
      }

    }
    else
    {
      Serial.println("Size mismatch");
    }

  }
  else
  {
    Serial.println("Size exceeds Maximum");
  }
  return writingStatus;
}

String ElementzGSMshield::readFromtheBeginningOftheFile(const char *fileNameWithPath, uint16_t sizeTobeRead, uint8_t linesTobeRead)
{
  SendAT("AT+FSREAD=" + String(fileNameWithPath) + ",0," + String(sizeTobeRead) + ",0");
  String replyString = readReply(10000, linesTobeRead);
  return replyString;
}

String ElementzGSMshield::readFromposition(const char *fileNameWithPath, uint16_t sizeTobeRead, uint16_t position, uint8_t linesTobeRead)
{
  SendAT("AT+FSREAD=" + String(fileNameWithPath) + ",1," + String(sizeTobeRead) + "," + String(position));
  String replyString = readReply(10000, linesTobeRead);
  return replyString;
}

uint16_t ElementzGSMshield::getFileSize(const char *fileNameWithPath)
{
  SendAT("AT+FSFLSIZE=" + String(fileNameWithPath));
  String replyString = readReply(2000, 1);
  if (strstr(replyString.c_str(), "+FSFLSIZE") != 0)
  {
    replyString.replace("\r\n+FSFLSIZE: ", "");
    return replyString.toInt();
  }
  return 0;
}
