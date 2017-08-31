#ifndef LedMatrix_h
#define LedMatrix_h

class LedMatrix
{
  public:
    LedMatrix(int rPin, int gPin, int bPin);
    
    void setup();
    void light(int pin, int brightness);
    void lightR(int brightness);
    void lightG(int brightness);
    void lightB(int brightness);
    
  private:
    int rPin;
    int gPin;
    int bPin;
};

#endif