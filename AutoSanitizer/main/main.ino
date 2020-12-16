#include <Arduino.h>

#define DEBUG

int IRData = 10;           //PB2
int R_Out = 9;             //PB1
int Debug_Led = 8;         //PB0
int Relay_ON_Time = 500;
int Wait_Time = 1500;

/* sets pin 3 going at the IR modulation rate
*/
void setIrModOutput(){                            
  pinMode(3, OUTPUT);

  // Just enable output on Pin 3 and disable it on Pin 11    
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); 
  TCCR2B = _BV(WGM22) | _BV(CS22);
  
  // defines the frequency 51 = 38.4 KHz, 54 = 36.2 KHz, 58 = 34 KHz, 62 = 32 KHz
  OCR2A = 51;                                     
  
  // defines the duty cycle - Half the OCR2A value for 50%
  OCR2B = 25;                                     

  // select a prescale value of 8:1 of the system clock
  TCCR2B = (TCCR2B & 0b00111000) | 0x2;             
}

void setup(){

  setIrModOutput();
  // initialize the digital pins.
  pinMode(R_Out, OUTPUT);
  pinMode(IRData, INPUT);

 #ifdef DEBUG
    Serial.begin(9600);
    pinMode(Debug_Led, OUTPUT);
    digitalWrite(Debug_Led, HIGH);
    Serial.println("Initialising...");
    delay(1000); 
    digitalWrite(Debug_Led, LOW);
  #endif
}

void loop(){

  if(digitalRead(IRData) == LOW){
    digitalWrite(R_Out, HIGH);      // turn the Relay on
    #ifdef DEBUG
      Serial.println("Relay ON");
      digitalWrite(Debug_Led, HIGH);
    #endif
    delay(Relay_ON_Time);           // wait for a Relay_ON_Time
    digitalWrite(R_Out, LOW);       // turn the Relay off
    #ifdef DEBUG
      Serial.println("Relay OFF");
      digitalWrite(Debug_Led, LOW);
    #endif
    delay(Wait_Time);               // wait for a Wait_Time

  }
  
}
