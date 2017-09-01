#ifndef LedMatrix_h
#define LedMatrix_h

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
            int ld_74138,
            int displayMatrixRowSize,
            int displayMatrixColumnSize,
            int fontTableRowSize,
            int displayPanelRowSize,
            char *message);

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
  int displayMatrixRowSize;
  int displayMatrixColumnSize;
  int fontTableRowSize;
  int displayPanelRowSize;
  char *message;
  byte displayMatrix[256];
  uint8_t fontTable[1536];
  int currentScanRow;
  int messageIndex;
};

#endif