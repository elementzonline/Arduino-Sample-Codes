/*
Author: Dhanish
Created on: 19-08-2014
Company: Elementz Engineers Guild Pvt Ltd


Run this code only after SIM900A Module has powered and connected to a Network.
Please make a call to the module knowing whether the connect is established.
If connected a ring will be heard at the caller end
*/

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
   // print the serial data to GSM
  Serial.print("ATD9020XXXXXX;" );   // change here to call a number using SIM900A                    
  // wait 10 seconds before the next loop
  delay(10000); 
  Serial.print("ATH" ); // hold the call
}

void loop() { 
}
