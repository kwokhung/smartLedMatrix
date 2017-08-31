#include <Arduino.h>

#include "LedMatrix.h"

LedMatrix::LedMatrix(int rPin, int gPin, int bPin)
    : rPin(rPin),
      gPin(gPin),
      bPin(bPin)
{
}

void LedMatrix::setup()
{
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    digitalWrite(rPin, HIGH);
    digitalWrite(gPin, HIGH);
    digitalWrite(bPin, HIGH);
}

void LedMatrix::light(int pin, int brightness)
{
    if (brightness > 0)
    {
        analogWrite(pin, 1023 - brightness);
    }
    else if (brightness == 0)
    {
        analogWrite(pin, 1023);
        digitalWrite(pin, HIGH);
    }
}

void LedMatrix::lightR(int brightness)
{
    light(rPin, brightness);
}

void LedMatrix::lightG(int brightness)
{
    light(gPin, brightness);
}

void LedMatrix::lightB(int brightness)
{
    light(bPin, brightness);
}
