#ifndef App_h
#define App_h

#define LEDMATRIX_LATCH_PIN 8
#define LEDMATRIX_CLOCK_PIN 12

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