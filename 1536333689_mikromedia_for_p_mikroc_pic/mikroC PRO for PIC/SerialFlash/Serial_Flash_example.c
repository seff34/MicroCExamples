/* Project name:
     SerialFlash example (Demonstration of usage of the SerialFlash board)
 * Copyright:
     (c) MikroElektronika, 2010-2018.
 * Revision History:
     20180906:
       - initial release;
 * Description:
      Demonstration of SerialFlash usage (chip erase, read Flash ID, simple writing and reading back a simple byte,
      simple writing and reading back an array of 16 bytes).
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
// TFT module connections
char TFT_DataPort at PORTE;
char TFT_DataPort_Direction at TRISE;
sbit TFT_RST at LATH3_bit;
sbit TFT_BLED at LATG4_bit;
sbit TFT_RS at LATG3_bit;
sbit TFT_CS at LATF2_bit;
sbit TFT_RD at LATG0_bit;
sbit TFT_WR at LATG1_bit;
sbit TFT_RST_Direction at TRISH3_bit;
sbit TFT_BLED_Direction at TRISG4_bit;
sbit TFT_RS_Direction at TRISG3_bit;
sbit TFT_CS_Direction at TRISF2_bit;
sbit TFT_RD_Direction at TRISG0_bit;
sbit TFT_WR_Direction at TRISG1_bit;
// End TFT module connections

sbit CS_Serial_Flash_bit at LATF7_bit;
sbit CS_Serial_Flash_Direction_bit at TRISF7_bit;

#define _DATA_ARRAY_SIZE 16
#include <built_in.h>
#include "Serial_Flash_driver.h"

unsigned char Refresh_Cmd_Menu = 1;
unsigned char write_array[_DATA_ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
unsigned char read_array[_DATA_ARRAY_SIZE] = {0};

void main() {
  unsigned char temp, SerialFlashID, txt[12];
  unsigned char i, success;

  TFT_Set_Default_Mode();
  TFT_Init_ST7789V_8bit(320, 240);
  TFT_Fill_Screen(CL_AQUA);
  Delay_ms(500);

  // Disable other peripheral modules on the same SPI bus
  TRISD0_bit = 0;
  LATD0_bit  = 1;                  // Disable MMC module
  TRISF5_bit = 0;
  LATF5_bit  = 1;                  // Disable MP3 module


  Unlock_IOLOCK();

  PPS_Mapping(_RC5, _OUTPUT, _SDO1_SDA1);

  Lock_IOLOCK();

  // Set SPI1 module to master mode, clock = Fosc/4, data sampled at the middle of interval,
  // clock idle state low and data transmitted at low to high edge:
  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);


  SerialFlash_init();
  SerialFlash_WriteEnable();
  Delay_ms(500);
  
  TFT_Write_Text("***Serial Flash Example***", 70, 15);

    //Erase entire flash
      TFT_Write_Text("Erasing chip... ", 110, 45);
      SerialFlash_ChipErase();
      TFT_Write_Text("Done!", 110, 65);


    //Read Flash ID
      SerialFlashID = SerialFlash_ReadID();
      ByteToStr(SerialFlashID, txt);
      TFT_Write_Text("Flash ID:", 110, 95);
      TFT_Write_Text(txt, 180, 95);
      Delay_ms(500);

    
    //Write and read back a single byte
      temp = 123;
      TFT_Write_Text("Writting:", 110, 125);
      ByteToStr(temp, txt);
      TFT_Write_Text(txt, 180, 125);
      SerialFlash_WriteByte(temp, 0x123456);

      temp = 0;
      TFT_Write_Text("Reading: ", 110, 145);
      temp = SerialFlash_ReadByte(0x123456);
      ByteToStr(temp, txt);
      TFT_Write_Text(txt, 180, 145);
      Delay_ms(500);

    //Write the repetitive pattern of data to fill the first 4K of memory
    //and then read the entire flash again and check the data correctness
      TFT_Write_Text("Writing array...", 110, 175);
      SerialFlash_WriteArray(0x0000, &write_array, _DATA_ARRAY_SIZE);
      Delay_ms(500);
      TFT_Write_Text("Reading array...", 110, 195);
      SerialFlash_ReadArray(0x0000, &read_array, _DATA_ARRAY_SIZE);
      Delay_ms(500);
      success = 1;
      for (i = 0; i<_DATA_ARRAY_SIZE; i++){
        if (read_array[i] != write_array[i]){
          success = 0;
          break;
        }
      }
      if (success)
        TFT_Write_Text("Success - Full match!", 110, 215);
      else
        TFT_Write_Text("Failed", 110, 215);

   while(1);
}