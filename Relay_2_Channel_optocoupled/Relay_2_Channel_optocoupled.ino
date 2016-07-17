/*

Created by: Dhanish Vijayan
Company: Elementz Engineers Guild Pvt Ltd ( http://www.elementzonline.com )

This code demosntrate the interfacing and control of 2-Channel optocoupled relay board 

Las Modified Date: 17/07/2016

*/


int RelayControlPin1 = 2;
int RelayControlPin2 = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(RelayControlPin1, OUTPUT);
  pinMode(RelayControlPin2, OUTPUT);

}

void loop() {
  /*
  * Turn ON all relays 
  * Note: The control logic should be LOW for the optocoupler relay to be turned on
  */
  
  digitalWrite(RelayControlPin1, LOW);
  digitalWrite(RelayControlPin2, LOW);

  
  delay(10000); /* 10 seconds delay  */
  
  /*
  * Turn OFF all relays 
  * Note: The control logic should be HIGH for the optocoupler relay to be turned off
  */
  
  digitalWrite(RelayControlPin1, HIGH);
  digitalWrite(RelayControlPin2, HIGH);


  delay(10000); /* 10 seconds delay  */  
  
}
