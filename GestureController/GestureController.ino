/****************************************************************
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

To perform a NEAR gesture, hold your hand
far above the sensor and move it close to the sensor (within 2
inches). Hold your hand there for at least 1 second and move it
away.

To perform a FAR gesture, hold your hand within 2 inches of the
sensor for at least 1 second and then move it above (out of
range) of the sensor.

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt

****************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <FastLED.h>
#include <SparkFun_APDS9960.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
#define APDS9960_INT 25 // Needs to be an interrupt pin
#define DATA_PIN 26

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

const int NUM_LEDS = 24;
CRGB leds[NUM_LEDS];
int LEDCoordinateX = 12;
bool Gesture_Up, Gesture_Down, Gesture_Left, Gesture_Right, Gesture_Far, Gesture_Near;

// Functions
void interruptRoutine();
void handleGesture();
void ControlLEDStrip();
void UpdateI2CDisplay();

void setup()
{
  Serial.begin(115200);
  delay(2000);

  // ----------------I2C DISPLAY----------------
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  else
  {
    Serial.println("---------I2C Display - 0x3C----------");
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  // display.clearDisplay();
  // UpdateI2CDisplay();
  display.clearDisplay();

  // -------------------------------------------

  // ---------------- APDS 9960 ----------------
  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if (apds.init())
  {
    Serial.println(F("APDS-9960 initialization complete"));
  }
  else
  {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true))
  {
    Serial.println(F("Gesture sensor is now running"));

    // if (apds.setLEDDrive(0))
    // {
    //   Serial.println("LED Drive Set");
    // }
    if (apds.setGestureGain(GGAIN_2X))
    {
      Serial.println("Gesture Gain Set");
    }
  }
  else
  {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  // -------------------------------------------

  // ----------------WS2812B LED----------------
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // for (int i; i < NUM_LEDS; i++)
  // {
  //   leds[i] = CRGB::White;
  // }
  // FastLED.show();
}

void loop()
{
  if (isr_flag == 1)
  {
    detachInterrupt(APDS9960_INT);
    // Serial.println("Interrupt Function");
    handleGesture();
    ControlLEDStrip();
    isr_flag = 0;
    attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);
  }
}

void interruptRoutine()
{
  isr_flag = 1;
}

void handleGesture()
{
  bool GestureAvailability = apds.isGestureAvailable();
  // Serial.print("Gesture Avail : ");
  // Serial.println(GestureAvailability);

  if (GestureAvailability)
  {
    int GestureType = apds.readGesture();
    // Serial.print("Gesture Type : ");
    // Serial.println(GestureType);

    switch (GestureType)
    {
    case DIR_UP:
      Serial.println("UP");
      Gesture_Up = true;
      break;
    case DIR_DOWN:
      Serial.println("DOWN");
      Gesture_Down = true;
      break;
    case DIR_LEFT:
      Serial.println("LEFT");
      Gesture_Left = true;
      break;
    case DIR_RIGHT:
      Serial.println("RIGHT");
      Gesture_Right = true;
      break;
    case DIR_NEAR:
      Serial.println("NEAR");
      Gesture_Near = true;
      break;
    case DIR_FAR:
      Serial.println("FAR");
      Gesture_Far = true;
      break;
    default:
      Serial.println("NONE");
    }
  }
}

void UpdateI2CDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(1, 1);     // Start at top-left corner
  display.println(F("APDS 9960 & WS2812B"));

  display.setCursor(0, 24);
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print(F("X : "));
  if (LEDCoordinateX <= 9)
  {
    display.print("0");
    display.println(LEDCoordinateX);
  }
  else
  {
    display.println(LEDCoordinateX);
  }

  display.display();
}

void ControlLEDStrip()
{
  // --------------GESTURE UP--------------
  if (Gesture_Up)
  {
    if (LEDCoordinateX < NUM_LEDS - 1)
    {
      leds[LEDCoordinateX] = CRGB::Black;
      for (int i = 0; i <= 2; i++)
      {
        if (!(LEDCoordinateX >= NUM_LEDS - 1))
        {
          LEDCoordinateX++;
          leds[LEDCoordinateX] = CRGB::Red;
          FastLED.show();
          FastLED.delay(30);
          leds[LEDCoordinateX] = CRGB::Black;
        }
      }
      if (LEDCoordinateX >= NUM_LEDS - 1)
      {
        LEDCoordinateX = NUM_LEDS - 1;
        leds[LEDCoordinateX] = CRGB::Red;
      }
      else
      {
        LEDCoordinateX++;
        leds[LEDCoordinateX] = CRGB::Red;
      }
      UpdateI2CDisplay();
    }
    Gesture_Up = false;
  }

  // -------------GESTURE DOWN-------------
  if (Gesture_Down)
  {
    if (LEDCoordinateX > 0)
    {
      leds[LEDCoordinateX] = CRGB::Black;
      for (int j = 0; j <= 2; j++)
      {
        if (!(LEDCoordinateX - 1 <= 0))
        {
          LEDCoordinateX--;
          leds[LEDCoordinateX] = CRGB::Red;
          FastLED.show();
          FastLED.delay(30);
          leds[LEDCoordinateX] = CRGB::Black;
        }
      }

      if (LEDCoordinateX <= 0)
      {
        LEDCoordinateX = 0;
        leds[LEDCoordinateX] = CRGB::Red;
      }
      else
      {
        LEDCoordinateX--;
        leds[LEDCoordinateX] = CRGB::Red;
      }
      UpdateI2CDisplay();
    }
    Gesture_Down = false;
  }

  // -------------GESTURE LEFT-------------
  if (Gesture_Left)
  {
    if (LEDCoordinateX > 0)
    {
      leds[LEDCoordinateX] = CRGB::Black;
      LEDCoordinateX--;
      leds[LEDCoordinateX] = CRGB::Red;
      FastLED.show();
      UpdateI2CDisplay();
    }
    Gesture_Left = false;
  }

  // ------------GESTURE RIGHT-------------
  if (Gesture_Right)
  {
    if (LEDCoordinateX < NUM_LEDS - 1)
    {
      leds[LEDCoordinateX] = CRGB::Black;
      LEDCoordinateX++;
      leds[LEDCoordinateX] = CRGB::Red;
      FastLED.show();
      UpdateI2CDisplay();
    }
    Gesture_Right = false;
  }

  // -------------GESTURE NEAR-------------
  if (Gesture_Near)
  {
    for (int k = 0; k < NUM_LEDS; k++)
    {
      leds[k] = CRGB::Black;
    }
    FastLED.show();
    Gesture_Near = false;
  }

  // -------------GESTURE FAR-------------
  if (Gesture_Far)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
    Gesture_Far = false;
  }
}