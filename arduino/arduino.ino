/* Ping))) Sensor

   This sketch reads a PING))) ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse
   to return.  The length of the returning pulse is proportional to
   the distance of the object from the sensor.

   The circuit:
    * +V connection of the PING))) attached to +5V
    * GND connection of the PING))) attached to ground
    * SIG connection of the PING))) attached to digital pin 7

   http://www.arduino.cc/en/Tutorial/Ping

   created 3 Nov 2008
   by David A. Mellis
   modified 30 Aug 2011
   by Tom Igoe

   This example code is in the public domain.

 */
#include <stdio.h>
#include "airmouselib.h"
// this constant won't change.  It's the pin number
// of the sensor's output:
int pingPin = 7;
#define numSensors 2
char *locationData;

String stringDistance;
int distance[numSensors];


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  stringDistance="";
}

int getSmoothValue(int newValue, smoothValue old){
    int newValue_i = old.lastValue +1;
    if (newValue_i == averageLength) {
       newValue_i = 0;
    }

    old.values[newValue_i] = newValue;

    int average;
    for (int i=0; i < averageLength; i++){
        average += old.values[i];
    }
    return average  / averageLength;
}
        
    
void loop()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration[numSensors];
  int inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  for (int i = 0; i < numSensors; i++)
  {
    pingPin = i + 7;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
 

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(pingPin, INPUT);
    duration[i] = (duration[i]*9 +pulseIn(pingPin, HIGH)/10);
   

   
  }

    stringDistance += (duration[0]/4);
    stringDistance += ":";
    stringDistance += (duration[1]/4);
   

    Serial.println(stringDistance);
    stringDistance ="";
   
    delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
