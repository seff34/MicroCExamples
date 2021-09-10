 /* Project name:
     UART
 * Copyright:
     (c) Mikroelektronika, 2018.
 * Revision History:
     20180905:
       - initial release;
 * Description:
     Simple UART demo
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
     - UART is initialized at 9600 baud rate.
*/
#define USB_UART

char uart_rd;

void main() {
  ANSELA = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  ANSELF = 0;
  ANSELG = 0;

  #ifdef UART_HED
  PPS_Mapping(_RC6, _OUTPUT, _TX2_CK2);       // Map UART TX
  PPS_Mapping(_RC7, _INPUT, _RX2);               // Map UART RX

  UART2_Remappable_Init(115200);                // Initialize UART module at 9600 bps
  #endif
  #ifdef USB_UART
  UART4_Init(115200);
  #endif
  Delay_ms(100);                              // Wait for UART module to stabilize

  #ifdef UART_HED
  UART2_Remappable_Write_Text("Start");
  UART2_Remappable_Write(13);
  UART2_Remappable_Write(10);
  #endif
  
  #ifdef USB_UART
  UART_Write_Text("Start");
  UART_Write(13);
  UART_Write(10);
  #endif
  
  while (1) {    
    // Endless loop
    #ifdef UART_HED
    if (UART2_Remappable_Data_Ready()) {     // If data is received,
      uart_rd = UART2_Remappable_Read();     // read the received data,
      UART2_Remappable_Write(uart_rd);       // and send data via UART
    }
    #endif
    
    #ifdef USB_UART
    if (UART_Data_Ready()) {     // If data is received,
      uart_rd = UART_Read();     // read the received data,
      UART_Write(uart_rd);       // and send data via UART
    }
    #endif
  }
}