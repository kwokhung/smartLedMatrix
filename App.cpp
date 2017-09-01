#include <Arduino.h>

#include "LedMatrix.h"
#include "App.h"

const char *message = "Date & Time: 2016/06/21 13:37:21   ";

App::App()
    : ledMatrix(new LedMatrix(LEDMATRIX_LATCH_PIN, LEDMATRIX_CLOCK_PIN))
{
}

void App::setup()
{
    ledMatrix->setup();
}

LedMatrix *App::getLedMatrix()
{
    return ledMatrix;
}
