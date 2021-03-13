/*
* Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
* http://www.libelium.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see .
*
* Version 0.1
* Author: Alejandro Gállego
*/

#include <Arduino.h>

int led = 13;
int onModulePin = 2; // the pin to switch on the module (without press on button)
char data[255];
char latitude[11], longitude[12];
char date[6], UTC_time[8];
char speed_OG[6], altitude[6];
char response[128];

int x, y;
void switchModule()
{
  digitalWrite(onModulePin, HIGH);
  delay(2000);
  digitalWrite(onModulePin, LOW);
}

void setup()
{
  Serial.begin(115200); // UART baud rate
  delay(2000);
  pinMode(led, OUTPUT);
  pinMode(onModulePin, OUTPUT);
  switchModule(); // switches the module ON
  for (int i = 0; i < 5; i++)
  {
    delay(5000);
  }
  Serial.println("AT+CGSOCKCONT=1,\"IP\",\"myapn\"");
  Serial.flush();
  x = 0;
  do
  {
    while (Serial.available() == 0)
      ;
    response[x] = Serial.read();
    x++;
  } while (!check_response("OK"));
  Serial.println("AT+CGPSURL=\"supl.google.com:7276\""); // sets GPS server
  delay(100);
  while (Serial.read() != 'K')
    ;
  Serial.println("AT+CGPSSSL=0"); // without certificate
  delay(100);
  while (Serial.read() != 'K')
    ;
  Serial.println("AT+CGPS=1,2"); // starts GPS session in based mode
  delay(100);
  while (Serial.read() != 'K')
    ;
}
void loop()
{
  delay(5000);
  Serial.println("AT+CGPSINFO"); // request GPS info
  Serial.flush();
  for (x = 0; x < 255; x++)
  {
    data[x] = '\0';
  }
  x = 0;
  do
  {
    do
    {
      digitalWrite(led, HIGH);
    } while (Serial.available() == 0);

    digitalWrite(led, LOW);
    data[x] = Serial.read();
    x++;
  } while (Serial.read() != 'K');
  x = 24;
  y = 0;
  if (data[x] != ',')
  {
    Serial.print("Latitude: "); //shows actual latitude
    do
    {
      latitude[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
      if (y == 2)
      {
        Serial.print(0xF8);
      }
      if (y == 4)
      {
        Serial.print(".");
      }
    } while (data[x] != ',');
    x++;
    Serial.print(" ");
    Serial.println(data[x]); //north or south
    x += 2;
    y = 0;
    Serial.print("Longitude: "); //shows actual longitude
    do
    {
      longitude[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
      if (y == 3)
      {
        Serial.print(0xF8);
      }
      if (y == 5)
      {
        Serial.print(".");
      }
    } while (data[x] != ',');
    x++;
    Serial.print(" ");
    Serial.println(data[x]); //west or east
    x += 2;
    y = 0;
    Serial.print("Date: "); //shows date
    do
    {
      date[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
    } while (data[x] != ',');
    x++;

    y = 0;
    Serial.print("\r\nUTC time: "); //shows UTC time
    do
    {
      UTC_time[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
    } while (data[x] != ',');
    x++;
    y = 0;
    Serial.print("\r\nAltitude: "); //shows altitude
    do
    {
      UTC_time[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
    } while (data[x] != ',');
    Serial.println(" m");
    x++;
    y = 0;
    Serial.print("Speed: "); //shows speed
    do
    {
      speed_OG[y] = data[x];
      Serial.print(data[x]);
      y++;
      x++;
    } while (data[x] != 0x0D);
    Serial.println(" knots");
  }
  else
  {
    Serial.println("GPS information not available, please wait...");
  }
}

boolean check_response(char *str)
{

  int i = 0;
  int j = 0;
  char b[10];
  // reading the message and cutting
  // initials and finals
  while (Serial.available() > 0)
  {
    if (j == 0 || j == 1)
    {
      Serial.read();
      j++;
    }
    else if (Serial.peek() == 13)
    {
      b[i] = 0;
      Serial.read();
    }
    else if (Serial.peek() == 10)
    {
      Serial.read();
    }
    else
    {
      b[i++] = Serial.read();
    }
  }
  // comparing
  int cont = 0;
  int cont2 = 0;
  boolean ok = false;
  while (b[cont] != -1)
  {
    if (b[cont] == str[cont2])
    {
      while (str[cont2] != -1)
      {
        if (b[cont + cont2] != b[cont2])
        {
          cont2++;
          ok = true;
        }
        else
        {
          ok = false;
          break;
        }
      }
    }
    if (ok)
      break;
    cont++;
  }

  if (ok)
  {
    return true;
  }

  return false;
}