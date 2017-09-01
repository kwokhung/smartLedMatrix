#ifndef LedMatrix_h
#define LedMatrix_h

class LedMatrix
{
public:
  LedMatrix(int ic74595LatchPin,
            int ic74595ClockPin,
            int ic74595DataR1Pin,
            int ic74595DataR2Pin,
            int ic74138EnPin,
            int ic74138LaPin,
            int ic74138LbPin,
            int ic74138LcPin,
            int ic74138LdPin,
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
  int ic74595LatchPin;
  int ic74595ClockPin;
  int ic74595DataR1Pin;
  int ic74595DataR2Pin;
  int ic74138EnPin;
  int ic74138LaPin;
  int ic74138LbPin;
  int ic74138LcPin;
  int ic74138LdPin;
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