#include "SPI.h"
#include "Adafruit_WS2801.h"

int led = 13; // LED connected to digital pin 13
byte inR = 0;// byte received on the serial port
byte inG = 0;
byte inB = 0;
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels
byte numLights;
Adafruit_WS2801 strip;
int i = 0;

 
void setup() {
    //initialize serial port, and wait for the first byte of
    // data telling us how many lights exist
    Serial.begin(9600);
    while (Serial.available() < 1);
    numLights = Serial.read();
    strip = Adafruit_WS2801(numLights, dataPin, clockPin);
    strip.begin();
}
 
void loop()
{
  // if serial port is available, read incoming bytes
    while (Serial.available() > 2)
    {
        inR = Serial.read();
        inG = Serial.read();
        inB = Serial.read();
     
        strip.setPixelColor(i, Color(inR, inG, inB));
        i++;
        if (i >= numLights)
        {
            i = 0;
            strip.show();
        }
    }
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}

