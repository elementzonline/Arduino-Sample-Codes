/*
Developed by Dhanish Vijayan - Elementz Engineers Guild Pvt. Ltd.
Instructions

Tested with the Elementz Lora board with Arduino Pro mini 8 MHz bootloader
Led blinks at every packet reception

ToDo: 
// Receive from multiple clients
// Parameter tuning to achive more range

*/

#include <SPI.h>
#include "LoRa.h"

int LED_BUILTIN1 = 3;
int SyncWord = 0x22;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED_BUILTIN1, OUTPUT);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

   LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
   LoRa.setSignalBandwidth(62.5E3);           // for -139dB (page - 112)
   LoRa.setCodingRate4(8);                   // for -139dB (page - 112)
   LoRa.setSyncWord(SyncWord);           // ranges from 0-0xFF, default 0x12, see API docs

  Serial.print("current spreading factor : ");
  Serial.println(LoRa.getSpreadingFactor());
  Serial.print("current bandwidth : ");
  Serial.println(LoRa.getSignalBandwidth());
  Serial.println("LoRa init succeeded.");
}

void loop() {
  // try to parse packet
//  if (SyncWord == 0x22)  SyncWord = 0x11; else SyncWord = 0x22;
//  LoRa.setSyncWord(SyncWord);
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.print(LoRa.packetRssi());
    Serial.println(" Snr: " + String(LoRa.packetSnr()));
    digitalWrite(LED_BUILTIN1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(LED_BUILTIN1, LOW);    // turn the LED off by making the voltage LOW
    delay(200); 
  }
}
