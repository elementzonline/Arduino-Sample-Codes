/*
 * 
 * Hardware used : https://www.elementzonline.com/pulse-sensor-amped-heart-rate-sensor-for-arduino-raspberry-pi
  ReadHearRate Sensor
  Connection -

  Arduino pin   -- Sensor PIN
  3.3V          -- V+ (+ marking)
  GND           -- V- (- marking)
  A0            -- S (S marking)


Instructions:

Open serial monitor with baud rate 115200, 

At first you will not see anything in serial monitor,

Place the sensor on a flat surface with LED facing upwards ( Heart sysmbol faces on top )
Sit on a seat such that the heart and finger are on same level. 
Gently place the finger tip covering the led and sensor.
No need to apply more pressure with the finger. Only a gentle contact will be enough.
Now observe the serial monitor for the BPM to be printed.   
 
*/


int peak=0;
int bottom = 1023;
int sample_count = 0;

long previousMillis = 0;
long previousPeakMillis = 0;
long previousLowMillis = 0;
long newPeakMillis = 0;
long newLowMillis = 0;
long peakDiff = 0;
long lowDiff = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {

  long nextMillis = millis();
  sample_count++;
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // if a new peak is found, update the peak variable and save the time in which the peak is obtained
  if (sensorValue > peak){
    peak = sensorValue;    // update new peak
    newPeakMillis = nextMillis;

  }

  // if a new low is found, update the bottom variable and save the time in which the low is obtained
  if (sensorValue < bottom){
    bottom = sensorValue; 
    newLowMillis = nextMillis; 
  }

  if ((nextMillis - previousMillis) > 750)    // Find the alternate peak difference every 750 milli seconds
  { 
//    Serial.print("Bottom: ");
//    Serial.println(peak); 
//    Serial.print("Peak: ");
//    Serial.println(bottom); 

    

//    Serial.print("previousPeakMillis: ");
//    Serial.println(previousPeakMillis); 
//    Serial.print("previousLowMillis: ");
//    Serial.println(previousLowMillis); 

    peakDiff = newPeakMillis - previousPeakMillis;            // Find the difference between consecutive peaks
    lowDiff = newLowMillis - previousLowMillis;               // Find the difference between consecutive lows/bottom
//    Serial.print("PeakDiff: "); 
//    Serial.println(peakDiff);
//    Serial.print("LowDiff: ");
//    Serial.println(lowDiff);
    
    // If the consecutive lowDifference of peak and bottom are more or less same, then we can consider the we get two valid heart pulses. 
    // If two valid heart pulses are obtained satisfying the above condition, we can calculate the BPM(Beats per minute), note that all timing are in Milliseconds
    if (abs(peakDiff - lowDiff) < 25){                     
        Serial.println("Valid beat found: ");

        // Take the average of the peak and low differences and save this to "value"
        long value = (peakDiff + lowDiff)/2;

       // BPM is caluclated as (1000 milliseconds / value in milliseconds) * 60
        Serial.print("BPM =  ");
        Serial.println((float)1000/(float)value * 60);
    } 
    

    // Save the previous peak and low millis to a variable for next calculation
    previousPeakMillis = newPeakMillis;
    previousLowMillis = newLowMillis;

    // reset the peak and bottom variables to find new peak and bottom
    peak = 0;  
    bottom = 1024;

    // reset previousMillis to enter this loop after 750 ms
    previousMillis = nextMillis;
  }
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
//  Serial.println(sensorValue);
  delay(2); // read every 2 ms
}
