#include <Arduino.h>

#include "LedMatrix.h"
#include "App.h"

const char *message = "Date & Time: 2016/06/21 13:37:21   ";

App::App()
    : ledMatrix(new LedMatrix(LEDMATRIX_LATCH_PIN,
                              LEDMATRIX_CLOCK_PIN,
                              LEDMATRIX_DATA_R1_PIN,
                              LEDMATRIX_DATA_R2_PIN,
                              LEDMATRIX_EN_74138_PIN,
                              LEDMATRIX_LA_74138_PIN,
                              LEDMATRIX_LB_74138_PIN,
                              LEDMATRIX_LC_74138_PIN,
                              LEDMATRIX_LD_74138_PIN,
                              LEDMATRIX_ROWSIZE,
                              LEDMATRIX_COLUMNSIZE,
                              LEDMATRIX_FONTTABLE_ROWSIZE,
                              LEDMATRIX_DISPLAYPANEL_ROWSIZE))
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
