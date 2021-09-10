/*
 * Project name:
     Calculator
 * Copyright:
     (c) Mikroelektronika, 2018.
 * Revision History:
     20180906:
       - initial release;
 * Description:
     Simple Calculator Demo.
 * Test configuration:
     MCU:             PIC18F67K40
                      http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18(L)F67K40%20Data%20Sheet%2040001841D.pdf
     Dev.Board:       mikromedia for PIC18FK                      
                      https://www.mikroe.com/mikromedia-3-pic18fk
     Oscillator:      HS-PLL, 16.000 MHz Crystal, 64.000 MHz MCU Clock
     Modules:         TFT on-board module
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/en/compilers/mikroc/pro/pic/
 * NOTES:
     - None.
*/

#include "Calculator_objects.h"

void main() {

  Start_TP();

  while (1) {
    Check_TP();

  }

}