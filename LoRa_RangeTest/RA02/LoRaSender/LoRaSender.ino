/*
Developed by Dhanish Vijayan - Elementz Engineers Guild Pvt. Ltd.
Instructions

Tested with the Elementz Lora board with Arduino Pro mini 8 MHz bootloader
Led blink on every packet transmit

*/

#include <SPI.h>
#include "LoRa.h"

int counter = 0;
int LED_BUILTIN1 = 3;
int ID = 2;  // 0x11 for 1 and 0x22 for 2
int SyncWord = 0x22;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
  LoRa.setSignalBandwidth(62.5E3 );           // for -139dB (page - 112)
  LoRa.setCodingRate4(8);                   // for -139dB (page - 112)
  LoRa.setSyncWord(SyncWord);

  Serial.print("current spreading factor : ");
  Serial.println(LoRa.getSpreadingFactor());
  Serial.print("current bandwidth : ");
  Serial.println(LoRa.getSignalBandwidth());
  Serial.println("LoRa init succeeded.");
}

void loop() {
  //LoRa.setSyncWord(1);
  LoRa.idle();
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("ID: ");
  LoRa.print(ID);
  LoRa.print(" HELLO ");
  LoRa.print(counter);
  LoRa.endPacket();
  LoRa.sleep();
  counter++;
  digitalWrite(LED_BUILTIN1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN1, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
  delay(5000);
}
