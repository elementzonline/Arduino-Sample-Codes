#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ElementzGSM.h"


char message[29] = "Sending from Arduino Success";
uint8_t email_timeout = 30;//in seconds
SoftwareSerial myserialOut(6,7);
ElementzGSMshield GSM(&myserialOut);
String testString = "";
void setup() {

  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Starting");
  delay(1000);



  GSM.turnOnGPRS("WWW.MYAIRTELGPRS.COM");
  GSM.setupEmailServer("xx-xx-x.xxxxxx.xxx", 25, email_timeout); //outgoing server address and port 25 is default port. You can get this from email client setup section of your mail
  GSM.setupEmailAuthorization("user@mail.com", "password", "Your Name"); //username(mail ID), password, Name;
  GSM.setupEmailToAddress("recepient@mail.com");//To address
  GSM.setEmailSubject("Testing from Arduino part2");//Subject
  GSM.sendEmailWithContent(message, 28); //Content

  //-------or send a string data as------------//

   GSM.turnOnGPRS("WWW.MYAIRTELGPRS.COM");
  GSM.setupEmailServer("xx-xx-x.xxxxxx.xxx", 25, email_timeout); //outgoing server address and port 25 is default port. You can get this from email client setup section of your mail
  GSM.setupEmailAuthorization("user@mail.com", "password", "Your Name"); //username(mail ID), password, Name;
  GSM.setupEmailToAddress("recepient@mail.com");//To address
  GSM.setEmailSubject("Testing from Arduino part2");//Subject
  GSM.sendEmailWithContent("Sending from Arduino Success", 28); //Content


}

void loop() {

}
