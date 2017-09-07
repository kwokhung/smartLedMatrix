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
            int rowSize,
            int columnSize,
            int fontTableRowSize,
            int displayPanelRowSize,
            int shiftDelay,
            char *message);

  void setup();
  void putCharToDisplayMatrix(uint16_t column, uint16_t row, byte character, boolean inverse);
  void moveDisplayMatrixLeft(int noOfPixel, int startOfRow, int endOfRow);
  void loop();

  static void shiftOut(int row);
  static void scan();

  static int ic74595LatchPin;
  static int ic74595ClockPin;
  static int ic74595DataR1Pin;
  static int ic74595DataR2Pin;
  static int ic74138EnPin;
  static int ic74138LaPin;
  static int ic74138LbPin;
  static int ic74138LcPin;
  static int ic74138LdPin;
  static int rowSize;
  static int columnSize;
  static int fontTableRowSize;
  static int displayPanelRowSize;
  static int shiftDelay;
  static byte displayMatrix[256];
  static const uint8_t fontTable[1536];
  static int currentScanRow;
  
private:
  char *message;
  int messageIndex;
};

#endif