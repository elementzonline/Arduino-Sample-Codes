
/*
Reed Sensor Sample Code
Author : Dhanish
Company : Elementz Engineers Guild Pvt Ltd
Website: http://www.elementzonline.com
*/

// set pin numbers:
const int PIRPin = 6;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin


int sensorState = 0;      

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  
  pinMode(PIRPin, INPUT);     
}

void loop(){

  sensorState = digitalRead(PIRPin);

  if (sensorState == HIGH) {  
    Serial.println("High");   
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    Serial.println("Low");
    digitalWrite(ledPin, LOW); 
  }
}
