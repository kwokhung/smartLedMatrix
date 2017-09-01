#ifndef App_h
#define App_h

#define LEDMATRIX_LATCH_PIN 8
#define LEDMATRIX_CLOCK_PIN 12
#define LEDMATRIX_DATA_R1_PIN 10
#define LEDMATRIX_DATA_R2_PIN 11
#define LEDMATRIX_EN_74138_PIN 2
#define LEDMATRIX_LA_74138_PIN 3
#define LEDMATRIX_LB_74138_PIN 4
#define LEDMATRIX_LC_74138_PIN 5
#define LEDMATRIX_LD_74138_PIN 6

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