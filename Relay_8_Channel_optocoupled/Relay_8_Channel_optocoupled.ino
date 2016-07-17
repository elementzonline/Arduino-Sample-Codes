/*

Created by: Dhanish Vijayan
Company: Elementz Engineers Guild Pvt Ltd ( http://www.elementzonline.com )

This code demosntrate the interfacing and control of 8-Channel optocoupled relay board 

Product Link: http://elementzonline.com/8-channel-relay-board-with-optocoupler-254

Las Modified Date: 17/07/2016

*/


int RelayControlPin1 = 2;
int RelayControlPin2 = 3;
int RelayControlPin3 = 4;
int RelayControlPin4 = 5;
int RelayControlPin5 = 6;
int RelayControlPin6 = 7;
int RelayControlPin7 = 8;
int RelayControlPin8 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(RelayControlPin1, OUTPUT);
  pinMode(RelayControlPin2, OUTPUT);
  pinMode(RelayControlPin3, OUTPUT);
  pinMode(RelayControlPin4, OUTPUT);
  pinMode(RelayControlPin5, OUTPUT);
  pinMode(RelayControlPin6, OUTPUT);
  pinMode(RelayControlPin7, OUTPUT);
  pinMode(RelayControlPin8, OUTPUT);
}

void loop() {
  /*
  * Turn ON all relays 
  * Note: The control logic should be LOW for the optocoupler relay to be turned on
  */
  
  digitalWrite(RelayControlPin1, LOW);
  digitalWrite(RelayControlPin2, LOW);
  digitalWrite(RelayControlPin3, LOW);
  digitalWrite(RelayControlPin4, LOW);
  digitalWrite(RelayControlPin5, LOW);
  digitalWrite(RelayControlPin6, LOW);
  digitalWrite(RelayControlPin7, LOW);
  digitalWrite(RelayControlPin8, LOW);
  
  delay(10000); /* 10 seconds delay  */
  
  /*
  * Turn OFF all relays 
  * Note: The control logic should be HIGH for the optocoupler relay to be turned off
  */
  
  digitalWrite(RelayControlPin1, HIGH);
  digitalWrite(RelayControlPin2, HIGH);
  digitalWrite(RelayControlPin3, HIGH);
  digitalWrite(RelayControlPin4, HIGH);
  digitalWrite(RelayControlPin5, HIGH);
  digitalWrite(RelayControlPin6, HIGH);
  digitalWrite(RelayControlPin7, HIGH);
  digitalWrite(RelayControlPin8, HIGH);

  delay(10000); /* 10 seconds delay  */  
  
}
