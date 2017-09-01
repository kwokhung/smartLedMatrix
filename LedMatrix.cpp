#include <Arduino.h>

#include "LedMatrix.h"

LedMatrix::LedMatrix(int ic74595LatchPin,
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
                     char *message)
    : ic74595LatchPin(ic74595LatchPin),
      ic74595ClockPin(ic74595ClockPin),
      ic74595DataR1Pin(ic74595DataR1Pin),
      ic74595DataR2Pin(ic74595DataR2Pin),
      ic74138EnPin(ic74138EnPin),
      ic74138LaPin(ic74138LaPin),
      ic74138LbPin(ic74138LbPin),
      ic74138LcPin(ic74138LcPin),
      ic74138LdPin(ic74138LdPin),
      displayMatrixRowSize(displayMatrixRowSize),
      displayMatrixColumnSize(displayMatrixColumnSize),
      fontTableRowSize(fontTableRowSize),
      displayPanelRowSize(displayPanelRowSize),
      message(message),
      displayMatrix({
          // Display buffer (which is scanned by the interrupt timer) of 8x32 bytes
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      }),
      fontTable({// full ASCII character set (8x16) (1536 bytes)
                 /*   (32) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* ! (33) */ 0x00, 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
                 /* " (34) */ 0x00, 0x00, 0x66, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* # (35) */ 0x00, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 0x00,
                 /* $ (36) */ 0x00, 0x18, 0x18, 0x7C, 0xC6, 0xC2, 0xC0, 0x7C, 0x06, 0x06, 0x86, 0xC6, 0x7C, 0x18, 0x18, 0x00,
                 /* % (37) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0xC6, 0x0C, 0x18, 0x30, 0x60, 0xC6, 0x86, 0x00, 0x00, 0x00,
                 /* & (38) */ 0x00, 0x00, 0x00, 0x38, 0x6C, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00,
                 /* ' (39) */ 0x00, 0x00, 0x30, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* ( (40) */ 0x00, 0x00, 0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00,
                 /* ) (41) */ 0x00, 0x00, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00,
                 /* * (42) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* + (43) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* , (44) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00,
                 /* - (45) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* . (46) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
                 /* / (47) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00,
                 /* 0 (48) */ 0x00, 0x00, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0xDB, 0xDB, 0xC3, 0xC3, 0x66, 0x3C, 0x00, 0x00, 0x00,
                 /* 1 (49) */ 0x00, 0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 0x00,
                 /* 2 (50) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0xC6, 0xFE, 0x00, 0x00, 0x00,
                 /* 3 (51) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x3C, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* 4 (52) */ 0x00, 0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00,
                 /* 5 (53) */ 0x00, 0x00, 0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* 6 (54) */ 0x00, 0x00, 0x00, 0x38, 0x60, 0xC0, 0xC0, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* 7 (55) */ 0x00, 0x00, 0x00, 0xFE, 0xC6, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
                 /* 8 (56) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* 9 (57) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x06, 0x0C, 0x78, 0x00, 0x00, 0x00,
                 /* : (58) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
                 /* ; (59) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00,
                 /* < (60) */ 0x00, 0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00,
                 /* = (61) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* > (62) */ 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00,
                 /* ? (63) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
                 /* @ (64) */ 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00, 0x00, 0x00,
                 /* A (65) */ 0x00, 0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00,
                 /* B (66) */ 0x00, 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 0x00,
                 /* C (67) */ 0x00, 0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0xC2, 0x66, 0x3C, 0x00, 0x00, 0x00,
                 /* D (68) */ 0x00, 0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00,
                 /* E (69) */ 0x00, 0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00,
                 /* F (70) */ 0x00, 0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00,
                 /* G (71) */ 0x00, 0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xDE, 0xC6, 0xC6, 0x66, 0x3A, 0x00, 0x00, 0x00,
                 /* H (72) */ 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00,
                 /* I (73) */ 0x00, 0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
                 /* J (74) */ 0x00, 0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00,
                 /* K (75) */ 0x00, 0x00, 0x00, 0xE6, 0x66, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00,
                 /* L (76) */ 0x00, 0x00, 0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00,
                 /* M (77) */ 0x00, 0x00, 0x00, 0xC3, 0xE7, 0xFF, 0xFF, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x00, 0x00, 0x00,
                 /* N (78) */ 0x00, 0x00, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00,
                 /* O (79) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* P (80) */ 0x00, 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00,
                 /* Q (81) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xDE, 0x7C, 0x0C, 0x0E, 0x00,
                 /* R (82) */ 0x00, 0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00,
                 /* S (83) */ 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x60, 0x38, 0x0C, 0x06, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* T (84) */ 0x00, 0x00, 0x00, 0xFF, 0xDB, 0x99, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
                 /* U (85) */ 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* V (86) */ 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00,
                 /* W (87) */ 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xDB, 0xDB, 0xFF, 0x66, 0x66, 0x00, 0x00, 0x00,
                 /* X (88) */ 0x00, 0x00, 0x00, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x66, 0xC3, 0xC3, 0x00, 0x00, 0x00,
                 /* Y (89) */ 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
                 /* Z (90) */ 0x00, 0x00, 0x00, 0xFF, 0xC3, 0x86, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0xC3, 0xFF, 0x00, 0x00, 0x00,
                 /* [ (91) */ 0x00, 0x00, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x00,
                 /* \ (92) */ 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00,
                 /* ] (93) */ 0x00, 0x00, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00, 0x00, 0x00,
                 /* ^ (94) */ 0x00, 0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* _ (95) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
                 /* ` (96) */ 0x00, 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* a (97) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00,
                 /* b (98) */ 0x00, 0x00, 0x00, 0xE0, 0x60, 0x60, 0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x00, 0x00, 0x00,
                 /* c (99) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* d (100) */ 0x00, 0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x3C, 0x6C, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00,
                 /* e (101) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* f (102) */ 0x00, 0x00, 0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00,
                 /* g (103) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xCC, 0x78,
                 /* h (104) */ 0x00, 0x00, 0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00,
                 /* i (105) */ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
                 /* j (106) */ 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C,
                 /* k (107) */ 0x00, 0x00, 0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00,
                 /* l (108) */ 0x00, 0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00,
                 /* m (109) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE6, 0xFF, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB, 0x00, 0x00, 0x00,
                 /* n (110) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00,
                 /* o (111) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* p (112) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0,
                 /* q (113) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E,
                 /* r (114) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x76, 0x66, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00,
                 /* s (115) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x60, 0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00,
                 /* t (116) */ 0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00,
                 /* u (117) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00,
                 /* v (118) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00,
                 /* w (119) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0xDB, 0xDB, 0xFF, 0x66, 0x00, 0x00, 0x00,
                 /* x (120) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0xC3, 0x00, 0x00, 0x00,
                 /* y (121) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8,
                 /* z (122) */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCC, 0x18, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00,
                 /* { (123) */ 0x00, 0x00, 0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00,
                 /* | (124) */ 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
                 /* } (125) */ 0x00, 0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00,
                 /* ~ (126) */ 0x00, 0x00, 0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 /* BLK(127)*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}),
      currentScanRow(0),
      messageIndex(0)
{
}

void LedMatrix::setup()
{
    // Set up Timer2 as the scanning interrupt timer
    cli();

    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;

    // Set 1024 prescaler
    TCCR2B |= (1 << CS22) | (1 << CS20);

    // 160Hz scan rate = 10 frames / second (16 pairs of rows)
    // 97 = (16,000,000 / (1024 * 160)) - 1
    OCR2A = 97;

    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    pinMode(ic74595LatchPin, OUTPUT);
    pinMode(ic74595ClockPin, OUTPUT);
    pinMode(ic74595DataR1Pin, OUTPUT);
    pinMode(ic74595DataR2Pin, OUTPUT);

    pinMode(ic74138EnPin, OUTPUT);
    pinMode(ic74138LaPin, OUTPUT);
    pinMode(ic74138LbPin, OUTPUT);
    pinMode(ic74138LcPin, OUTPUT);
    pinMode(ic74138LdPin, OUTPUT);

    digitalWrite(ic74138EnPin, LOW);
    digitalWrite(ic74595DataR1Pin, HIGH);
    digitalWrite(ic74595DataR2Pin, HIGH);

    sei();
}

// Routine to put a single character in one of 8 columns in buffer
// Inputs:
// column is one of (0 - 7),
// row (0 or 16),
// character is either (0 to 9) or an ascii value,
// inverse is true for an inverted character
void LedMatrix::putCharToDisplayMatrix(uint16_t column, uint16_t row, byte character, boolean inverse)
{
    byte characterBytes[16];
    int fontIndex;

    // invalid character
    if ((character > 9) && (character < 32))
    {
        return;
    }

    if ((character >= 0) && (character <= 9))
    {
        fontIndex = (character + 16) * fontTableRowSize;
    }
    else
    {
        fontIndex = (character - 32) * fontTableRowSize;
    }

    int index = (row << 3) + column;
    byte *bufferPointer = &displayMatrix[index];

    for (int i = 0; i < fontTableRowSize; i++)
    {
        // fill up the charbytes array with the right bits
        characterBytes[i] = pgm_read_byte(&(fontTable[fontIndex + i]));

        if (inverse)
        {
            characterBytes[i] = ~characterBytes[i];
        }
    };

    // point at the first set of 8 pixels
    byte *characterPointer = characterBytes;

    for (int i = 0; i < fontTableRowSize; i++)
    {
        // populate the destination byte
        *bufferPointer = *characterPointer;

        // go to next row on buffer
        bufferPointer += 8;

        // go to next set of 8 pixels in character
        characterPointer++;
    }
};

void LedMatrix::moveDisplayMatrixLeft(int noOfPixel, int startOfRow, int endOfRow)
{
    // routine to move certain rows on the screen "pixels" pixels to the left
    for (int column = 0; column < 8; column++)
    {
        for (int row = startOfRow; row < endOfRow; row++)
        {
            int index = (row << 3) + column;

            if (column == 7)
            {
                // shuffle pixels left on last column and fill with a blank
                displayMatrix[index] = displayMatrix[index] << noOfPixel;
            }
            else
            {
                // shuffle pixels left and add leftmost pixels from next column
                int incomingchar = displayMatrix[index + 1];

                displayMatrix[index] = displayMatrix[index] << noOfPixel;

                for (int x = 0; x < noOfPixel; x++)
                {
                    displayMatrix[index] += ((incomingchar & (128 >> x)) >> (7 - x)) << (noOfPixel - x - 1);
                };
            }
        }
    }
};

// shift 8 columns of a row from buffer via ic74595DataR1Pin (first 16 rows) and ic74595DataR2Pin (second 16 rows)
void LedMatrix::shiftOut(int row)
{
    for (int column = 0; column < 8; column++)
    {
        // index = row(0-31), column(0-8)
        int index = (row << 3) + column;

        for (int i = 0; i < 8; i++)
        {
            // set ic74595DataR1Pin and ic74595DataR2Pin to LOW;
            PORTB &= ~(3 << (ic74595DataR1Pin - 8));

            // set ic74595ClockPin to LOW
            PORTB &= ~(1 << (ic74595ClockPin - 8));

            // top set of rows
            // set ic74595DataR1Pin to high if displayMatrix[index] reverse i is low
            PORTB |= !((displayMatrix[index] >> (7 - i)) & 0x01) << (ic74595DataR1Pin - 8);

            // bottom set of rows
            // set ic74595DataR2Pin to high if displayMatrix[index + 128] reverse i is low
            PORTB |= !((displayMatrix[index + 128] >> (7 - i)) & 0x01) << (ic74595DataR2Pin - 8);

            // set ic74595ClockPin to HIGH
            PORTB |= 1 << (ic74595ClockPin - 8);
        };
    };
};

void LedMatrix::loop()
{
    putCharToDisplayMatrix(displayMatrixColumnSize - 1 /* right most column */,
                           0 /* first 16 rows */,
                           message[messageIndex % (strlen(message) - 1)],
                           false);
    putCharToDisplayMatrix(displayMatrixColumnSize - 1 /* right most column */,
                           displayMatrixRowSize / 2 /* second 16 rows */,
                           message[messageIndex % (strlen(message) - 1)],
                           false);
    messageIndex++;

    for (int i = 0; i < 8; i++)
    {
        delay(640);

        moveDisplayMatrixLeft(1, 1, displayMatrixRowSize);
    };
}

void LedMatrix::scan()
{
    cli();

    // Turn off display
    digitalWrite(ic74138EnPin, HIGH);

    // Shift 8 columns for scanRow
    shiftOut(currentScanRow);

    digitalWrite(ic74595LatchPin, LOW);
    digitalWrite(ic74595LatchPin, HIGH);

    // Highlight row: pins 3 4 5 6 (ic74138LaPin ic74138LbPin ic74138LcPin ic74138LdPin)
    //PORTD = (currentScanRow << 3) | (PORTD & 0b10000111);
    if (currentScanRow == 1 || currentScanRow == 3 || currentScanRow == 5 || currentScanRow == 7 || currentScanRow == 9 || currentScanRow == 11 || currentScanRow == 13 || currentScanRow == 15)
    {
        digitalWrite(ic74138LaPin, HIGH);
    }
    else
    {
        digitalWrite(ic74138LaPin, LOW);
    }

    if (currentScanRow == 2 || currentScanRow == 3 || currentScanRow == 6 || currentScanRow == 7 || currentScanRow == 10 || currentScanRow == 11 || currentScanRow == 14 || currentScanRow == 15)
    {
        digitalWrite(ic74138LbPin, HIGH);
    }
    else
    {
        digitalWrite(ic74138LbPin, LOW);
    }

    if (currentScanRow == 4 || currentScanRow == 5 || currentScanRow == 6 || currentScanRow == 7 || currentScanRow == 12 || currentScanRow == 13 || currentScanRow == 14 || currentScanRow == 15)
    {
        digitalWrite(ic74138LcPin, HIGH);
    }
    else
    {
        digitalWrite(ic74138LcPin, LOW);
    }

    if (currentScanRow == 8 || currentScanRow == 9 || currentScanRow == 10 || currentScanRow == 11 || currentScanRow == 12 || currentScanRow == 13 || currentScanRow == 14 || currentScanRow == 15)
    {
        digitalWrite(ic74138LdPin, HIGH);
    }
    else
    {
        digitalWrite(ic74138LdPin, LOW);
    }

    // Turn on display
    digitalWrite(ic74138EnPin, LOW);

    // Do the next pair of rows next time this routine is called
    currentScanRow++;

    if (currentScanRow == displayPanelRowSize)
    {
        currentScanRow = 0;
    }

    sei();
};
