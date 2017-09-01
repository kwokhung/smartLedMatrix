#ifndef LedMatrix_h
#define LedMatrix_h

#define latchPin 8
#define clockPin 12
#define data_R1 10
#define data_R2 11
#define en_74138 2
#define la_74138 3
#define lb_74138 4
#define lc_74138 5
#define ld_74138 6

#define displayMatrixRowSize 32
#define displayMatrixColumnSize 8
#define fontTableRowSize 16
#define displayPanelRowSize 16

class LedMatrix
{
  public:
    LedMatrix(int rPin, int gPin, int bPin);
    
    void setup();
    void putCharToDisplayMatrix(uint16_t column, uint16_t row, byte character, boolean inverse);
    void moveDisplayMatrixLeft(int noOfPixel, int startOfRow, int endOfRow);
    void shiftOut(int row);
    void scan();
    void loop();
    
  private:
    int rPin;
    int gPin;
    int bPin;
    byte displayMatrix[256];
    uint8_t fontTable[1536];
    int currentScanRow;
    int messageIndex;
};

#endif