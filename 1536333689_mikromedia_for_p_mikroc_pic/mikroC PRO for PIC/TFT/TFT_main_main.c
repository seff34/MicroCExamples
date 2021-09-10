/*
 * Project name:
     TFT
 * Copyright:
     (c) MikroElektronika
 * Revision History:
     20180907 (FG):
       - initial release;
 * Description:
     This code demonstrates how to use 320x240 TFT Screen.
     TFT is first initialized, after that you can see full-color picture.
 * Test configuration:
     MCU:             PIC18F67K40
                      http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18(L)F67K40%20Data%20Sheet40001841D.pdf
     Dev.Board:       mikromedia for PIC18FK
                      https://www.mikroe.com/mikromedia-3-pic18fk
     Oscillator:      HS-PLL, 16.000 MHz Crystal, 64.000 MHz MCU Clock
     Modules:         TFT on-board module
     SW:              mikroC PRO for PIC
                      https://www.mikroe.com/mikroc-pic
 * NOTES:
     - None.
 */

#include "TFT_main_objects.h"

void main() {
  Start_TP();
}