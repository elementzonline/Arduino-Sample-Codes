/*
Developed by Nandu, Anandu, Unnikrishnan 
Company: Elementz Engineers Guild Pvt Ltd
*/
#include<SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
#define sw 5
#define led 7
int flag = 1;
int flag1 = 0;
int state=0;
String Publish = "led/publish"; //Publish Topic
String Subscribe = "led/subscribe"; //Subscribe Topic

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(sw, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //AT Commands for setting up the client id and Server
  //Need to be executed once -- Open serial terminal doe seeing the debug messages
  Serial.println("Connecting To Server........");
  mySerial.println("ATE0");
  delay(2000);
  mySerial.println("AT+CMQTTSTART"); //Establishing MQTT Connection
  delay(2000); 
  mySerial.println("AT+CMQTTACCQ=0,\"elementz/123\""); //Client ID - change this for each client as this need to be unique
  delay(2000);
  mySerial.println("AT+CMQTTCONNECT=0,\"tcp://test.mosquitto.org:1883\",90,1"); //MQTT Server Name for connecting this client
  delay(2000);

  //SUBSCRIBE MESSAGE
  //Need to be executed once
  mySerial.println("AT+CMQTTSUBTOPIC=0,9,1"); //AT Command for Setting up the Subscribe Topic Name 
  delay(2000);
  mySerial.println(Subscribe); //Topic Name
  delay(2000);
  mySerial.println("AT+CMQTTSUB=0,4,1,1"); //Length of message
  delay(2000);
  mySerial.println("HAII"); //message
  delay(2000);
  Serial.println("Done");
}

void loop() 
{
  String a;
  if(state==0)
  {

    if(digitalRead(sw) == 0 && flag1 == 0)
    {
      //PUBLISH MESSAGE
      flag1 = 1;
      digitalWrite(led, HIGH);
      Serial.println("Publishing Message: LED ON");
      mySerial.println("AT+CMQTTTOPIC=0,8"); //AT Command for Setting up the Publish Topic Name
      delay(1000);
      mySerial.println(Publish); //Topic Name
      delay(1000);
      mySerial.println("AT+CMQTTPAYLOAD=0,1"); //Payload length
      delay(1000);
      mySerial.println("a"); //Payload message
      delay(1000);
      mySerial.println("AT+CMQTTPUB=0,1,60"); //Acknowledgment
      delay(1000);
    }
    else if(digitalRead(sw) == 0 && flag1 == 1)
    {
      flag1 = 0;
     digitalWrite(led, LOW); 
      Serial.println("Publishing Message: LED OFF");
      mySerial.println("AT+CMQTTTOPIC=0,8"); //AT Command for Setting up the Publish Topic Name
      delay(1000);
      mySerial.println(Publish); //Topic Name
      delay(1000);
      mySerial.println("AT+CMQTTPAYLOAD=0,1"); //Payload length
      delay(1000);
      mySerial.println("b"); //Payload message
      delay(1000);
      mySerial.println("AT+CMQTTPUB=0,1,60"); //Acknowledgment
      delay(1000);
    }
  }
  if(state==1)
  {
    if(digitalRead(sw) == 0 && flag1 == 0)
    {
      //PUBLISH MESSAGE
      flag1 = 1;
      digitalWrite(led, LOW);
      Serial.println("Publishing Message: LED OFF");
      mySerial.println("AT+CMQTTTOPIC=0,8"); //AT Command for Setting up the Publish Topic Name
      delay(1000);
      mySerial.println(Publish); //Topic Name
      delay(1000);
      mySerial.println("AT+CMQTTPAYLOAD=0,1"); //Payload length
      delay(1000);
      mySerial.println("b"); //Payload message
      delay(1000);
      mySerial.println("AT+CMQTTPUB=0,1,60"); //Acknowledgment
      delay(1000);
    }
    else if(digitalRead(sw) == 0 && flag1 == 1)
    {
      flag1 = 0;
      digitalWrite(led,HIGH); 
      Serial.println("Publishing Message: LED ON");
      mySerial.println("AT+CMQTTTOPIC=0,8"); //AT Command for Setting up the Publish Topic Name
      delay(1000);
      mySerial.println(Publish); //Topic Name
      delay(1000);
      mySerial.println("AT+CMQTTPAYLOAD=0,1"); //Payload length
      delay(1000);
      mySerial.println("a"); //Payload message
      delay(1000);
      mySerial.println("AT+CMQTTPUB=0,1,60"); //Acknowledgment
      delay(1000);
    }
  }

 //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    if(flag==0)
    {
      //Serial.println(a);
    flag = 1;
    }
    //Serial.println(b);
    if(a.indexOf("PAYLOAD") != -1)
    {
       flag = 0;
       int new1 = a.indexOf("PAYLOAD");
       String neww = a.substring(new1);
       int new2 = neww.indexOf('\n');
       String new3 = neww.substring(new2+1);
       int new4 = new3.indexOf('\n');
       String new5 = new3.substring(0,new4);
       
       Serial.println("Topic: led/subscribe");
       Serial.print("Message is: ");
       Serial.println(new5);
       new5.remove(new5.length()-1);
       if(new5 == "a")
       {
        state=1;
        Serial.println("LED ON");
        digitalWrite(led, HIGH);
       }
       else if(new5 == "b")
       {
        state=0;
        flag1=0;
        Serial.println("LED OFF");
        digitalWrite(led, LOW);
       }
    }      
  }
}
