#ifndef App_h
#define App_h

#define SERIAL_RATE 115200

#define LEDMATRIX_IC74595_LATCH_PIN 8
#define LEDMATRIX_IC74595_CLOCK_PIN 12
#define LEDMATRIX_IC74595_DATA_R1_PIN 10
#define LEDMATRIX_IC74595_DATA_R2_PIN 11
#define LEDMATRIX_IC74138_EN_PIN 2
#define LEDMATRIX_IC74138_LA_PIN 3
#define LEDMATRIX_IC74138_LB_PIN 4
#define LEDMATRIX_IC74138_LC_PIN 5
#define LEDMATRIX_IC74138_LD_PIN 6

#define LEDMATRIX_ROWSIZE 32
#define LEDMATRIX_COLUMNSIZE 8
#define LEDMATRIX_FONTTABLE_ROWSIZE 16
#define LEDMATRIX_DISPLAYPANEL_ROWSIZE 16

#define LEDMATRIX_MESSAGE "Date & Time: 2016/06/21 13:37:21   "

#include "LedMatrix.h"

class App
{
public:
  App();

  void setup();
  LedMatrix *getLedMatrix();

private:
  LedMatrix *ledMatrix;
};

#endif