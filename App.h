#ifndef App_h
#define App_h

#define LED_R_PIN 5 // GPIO5 / E1 / D3
#define LED_G_PIN 4 // GPIO4 / E2 / D4
#define LED_B_Pin 0 // GPIO0 / E3 / D8

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