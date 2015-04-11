#include "Serial.h"
#include <stdio.h>

#define NUM_PIXELS 96

void fillBuffer(char* buffer, int length, char* color)
{
    for (int i = 0; i < length; i++)
    {
        buffer[i] = color[i % 3];
    }
}

int main() {
    char* whitePixel = new char[3];
    whitePixel[0] = whitePixel[1] = whitePixel[2] = (char)0xFF;

    char* redPixel = new char[3];
    redPixel[0] = (char)0xFF;
    redPixel[1] = redPixel[2] = (char)0x00;

    char* greenPixel = new char[3];
    greenPixel[1] = (char)0xFF;
    greenPixel[0] = greenPixel[2] = (char)0x00;

    char* bluePixel = new char[3];
    bluePixel[2] = (char)0xFF;
    bluePixel[0] = bluePixel[1] = (char)0x00;

    Serial serial = Serial("COM5");
    if (!serial.IsConnected())
    {
        fprintf_s(stderr, "Serial port communication failure. Aborting.");
        return 1;
    }
    else
    {
        fprintf_s(stdout, "Serial port communication initialized.");
    }

    char numberOfLights = NUM_PIXELS;
    serial.WriteData(&numberOfLights, 1);

    int numLights = (int)numberOfLights;
    int optBufSize = numLights * 3;

    char* redBuffer = new char[optBufSize];
    char* greenBuffer = new char[optBufSize];
    char* blueBuffer = new char[optBufSize];

    fillBuffer(redBuffer, optBufSize, redPixel);
    fillBuffer(greenBuffer, optBufSize, greenPixel);
    fillBuffer(blueBuffer, optBufSize, bluePixel);


    while (1 < 2)
    {
        serial.WriteData(redBuffer, optBufSize);
        serial.WriteData(greenBuffer, optBufSize);
        serial.WriteData(blueBuffer, optBufSize);
    }

    return 0;
}