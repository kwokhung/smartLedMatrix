#ifndef LedMatrix_h
#define LedMatrix_h

#define displayMatrixRowSize 32
#define displayMatrixColumnSize 8
#define fontTableRowSize 16
#define displayPanelRowSize 16

class LedMatrix
{
public:
  LedMatrix(int latchPin,
            int clockPin,
            int data_R1,
            int data_R2,
            int en_74138,
            int la_74138,
            int lb_74138,
            int lc_74138,
            int ld_74138);

  void setup();
  void putCharToDisplayMatrix(uint16_t column, uint16_t row, byte character, boolean inverse);
  void moveDisplayMatrixLeft(int noOfPixel, int startOfRow, int endOfRow);
  void shiftOut(int row);
  void scan();
  void loop();

private:
  int latchPin;
  int clockPin;
  int data_R1;
  int data_R2;
  int en_74138;
  int la_74138;
  int lb_74138;
  int lc_74138;
  int ld_74138;
  byte displayMatrix[256];
  uint8_t fontTable[1536];
  int currentScanRow;
  int messageIndex;
};

#endif