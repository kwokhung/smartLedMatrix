#include <Arduino.h>

#include "LedMatrix.h"
#include "App.h"

const char *message = "Date & Time: 2016/06/21 13:37:21   ";

App::App()
    : ledMatrix(new LedMatrix(LED_R_PIN, LED_G_PIN, LED_B_Pin))
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
