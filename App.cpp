#include <Arduino.h>

#include "LedMatrix.h"
#include "App.h"

App::App()
    : ledMatrix(new LedMatrix(LEDMATRIX_IC74595_LATCH_PIN,
                              LEDMATRIX_IC74595_CLOCK_PIN,
                              LEDMATRIX_IC74595_DATA_R1_PIN,
                              LEDMATRIX_IC74595_DATA_R2_PIN,
                              LEDMATRIX_IC74138_EN_PIN,
                              LEDMATRIX_IC74138_LA_PIN,
                              LEDMATRIX_IC74138_LB_PIN,
                              LEDMATRIX_IC74138_LC_PIN,
                              LEDMATRIX_IC74138_LD_PIN,
                              LEDMATRIX_ROWSIZE,
                              LEDMATRIX_COLUMNSIZE,
                              LEDMATRIX_FONTTABLE_ROWSIZE,
                              LEDMATRIX_DISPLAYPANEL_ROWSIZE,
                              LEDMATRIX_MESSAGE))
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
