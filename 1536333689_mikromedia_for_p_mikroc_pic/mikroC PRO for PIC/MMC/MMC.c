/* Project name:
     MMC
 * Copyright:
     (c) MikroElektronika, 2010 - 2018
 * Revision History:
     20180906:
       - initial release;
 * Description:
     This project consists of several blocks that demonstrate various aspects of
     usage of the Mmc library. These are:
     - Creation of new file and writing down to it;
     - Opening existing file and re-writing it (writing from start-of-file);
     - Opening existing file and appending data to it (writing from end-of-file);
     - Opening a file and reading data from it (sending it to USART terminal);
     - Creating and modifying several files at once;
     - Reading file contents;
     - Deleting file(s);
     - Creating the swap file (see Help for details);
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
     - Make sure that MMC card is properly formatted (FAT16 or just FAT)
       before testing it on this example.
     - This example expects the MMC card to be inserted before reset, otherwise
       the FAT_ERROR message is displayed.
 */

// MMC module connections
sbit Mmc_Chip_Select at LATD0_bit;
sbit Mmc_Chip_Select_Direction at TRISD0_bit;
// eof MMC module connections

const LINE_LEN = 43;
char err_txt[20]       = "FAT16 not found";
char file_contents[LINE_LEN] = "XX MMC/SD FAT16 library by Anton Rieckert\n";
char           filename[14] = "MIKRO00x.TXT";          // File names
unsigned short loop, loop2;
unsigned long  i, size;
char           Buffer[512];

// UART4 write text and new line (carriage return + line feed)
void UART4_Write_Line(char *uart_text) {
  UART4_Write_Text(uart_text);
  UART4_Write(13);
  UART4_Write(10);
}

// Creates new file and writes some data to it
void M_Create_New_File() {
  filename[7] = 'A';
  Mmc_Fat_Set_File_Date(2010, 4, 19, 9, 0, 0); // Set file date & time info
  Mmc_Fat_Assign(&filename, 0xA0);             // Find existing file or create a new one
  Mmc_Fat_Rewrite();                           // To clear file and start with new data
  for(loop = 1; loop <= 99; loop++) {
    UART4_Write('.');
    file_contents[0] = loop / 10 + 48;
    file_contents[1] = loop % 10 + 48;
    Mmc_Fat_Write(file_contents, LINE_LEN-1);   // write data to the assigned file
  }
}

// Creates many new files and writes data to them
void M_Create_Multiple_Files() {
  for(loop2 = 'B'; loop2 <= 'Z'; loop2++) {
    UART4_Write(loop2);                          // signal the progress
    filename[7] = loop2;                         // set filename
    Mmc_Fat_Set_File_Date(2010, 4, 19, 9, 0, 0); // Set file date & time info
    Mmc_Fat_Assign(&filename, 0xA0);             // find existing file or create a new one
    Mmc_Fat_Rewrite();                           // To clear file and start with new data
    for(loop = 1; loop <= 44; loop++) {
      file_contents[0] = loop / 10 + 48;
      file_contents[1] = loop % 10 + 48;
      Mmc_Fat_Write(file_contents, LINE_LEN-1);  // write data to the assigned file
    }
  }
}

// Opens an existing file and rewrites it
void M_Open_File_Rewrite() {
  filename[7] = 'C';
  Mmc_Fat_Assign(&filename, 0);
  Mmc_Fat_Rewrite();
  for(loop = 1; loop <= 55; loop++) {
    file_contents[0] = loop / 10 + 48;
    file_contents[1] = loop % 10 + 48;
    Mmc_Fat_Write(file_contents, LINE_LEN-1);    // write data to the assigned file
  }
}

// Opens an existing file and appends data to it
//               (and alters the date/time stamp)
void M_Open_File_Append() {
   filename[7] = 'B';
   Mmc_Fat_Assign(&filename, 0);
   Mmc_Fat_Set_File_Date(2010, 4, 19, 9, 20, 0);
   Mmc_Fat_Append();                                    // Prepare file for append
   Mmc_Fat_Write(" for mikroElektronika 2011\n", 27);   // Write data to assigned file
}

// Opens an existing file, reads data from it and puts it to UART
void M_Open_File_Read() {
  char character;
  
  filename[7] = 'B';
  Mmc_Fat_Assign(&filename, 0);
  Mmc_Fat_Reset(&size);            // To read file, procedure returns size of file
  for (i = 1; i <= size; i++) {
    Mmc_Fat_Read(&character);
    UART4_Write(character);        // Write data to UART
  }
}

// Deletes a file. If file doesn't exist, it will first be created
// and then deleted.
void M_Delete_File() {
  filename[7] = 'F';
  Mmc_Fat_Assign(filename, 0);
  Mmc_Fat_Delete();
}

// Tests whether file exists, and if so sends its creation date
// and file size via UART
void M_Test_File_Exist() {
  unsigned long  fsize;
  unsigned int   year;
  unsigned short month, day, hour, minute;
  unsigned char  outstr[12];

  filename[7] = 'B';
//  filename[7] = 'F';
  if (Mmc_Fat_Assign(filename, 0)) {
    //--- file has been found - get its create date
    Mmc_Fat_Get_File_Date(&year, &month, &day, &hour, &minute);
    UART4_Write_Text(" created: ");
    WordToStr(year, outstr);
    UART4_Write_Text(outstr);
    ByteToStr(month, outstr);
    UART4_Write_Text(outstr);
    WordToStr(day, outstr);
    UART4_Write_Text(outstr);
    WordToStr(hour, outstr);
    UART4_Write_Text(outstr);
    WordToStr(minute, outstr);
    UART4_Write_Text(outstr);
    
    //--- file has been found - get its modified date
    Mmc_Fat_Get_File_Date_Modified(&year, &month, &day, &hour, &minute);
    UART4_Write_Text(" modified: ");
    WordToStr(year, outstr);
    UART4_Write_Text(outstr);
    ByteToStr(month, outstr);
    UART4_Write_Text(outstr);
    WordToStr(day, outstr);
    UART4_Write_Text(outstr);
    WordToStr(hour, outstr);
    UART4_Write_Text(outstr);
    WordToStr(minute, outstr);
    UART4_Write_Text(outstr);
    
    //--- get file size
    fsize = Mmc_Fat_Get_File_Size();
    LongToStr((signed long)fsize, outstr);
    UART4_Write_Line(outstr);
  }
  else {
    //--- file was not found - signal it
    UART4_Write(0x55);
    Delay_ms(1000);
    UART4_Write(0x55);
  }
}
// Tries to create a swap file, whose size will be at least 100
// sectors (see Help for details)
void M_Create_Swap_File() {
  unsigned int i;

  for(i=0; i<512; i++)
    Buffer[i] = i;

  size = Mmc_Fat_Get_Swap_File(5000, "mikroE.txt", 0x20);   // see help on this function for details

  if (size) {
    LongToStr((signed long)size, err_txt);
    UART4_Write_Line(err_txt);

    for(i=0; i<5000; i++) {
      Mmc_Write_Sector(size++, Buffer);
      UART4_Write('.');
    }
  }
}

// Main. Uncomment the function(s) to test the desired operation(s)
void main() {
  #define COMPLETE_EXAMPLE         // comment this line to make simpler/smaller example
  Delay_ms(150);
  ANSELA = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  ANSELF = 0;
  ANSELG = 0;

//  TRISH5_bit = 0;
//  LATH5_bit = 0;   // Turn off TFT backlight
  
  //Disable other peripheral modules on the same SPI bus
  TRISF7_bit = 0;
  LATF7_bit = 1;   // Disable Serial Flash module
  TRISF5_bit = 0;
  LATF5_bit = 1;   // Disable MP3 module
  
  // Initialize UART4 module
  UART4_Init(19200);
  Delay_ms(10);

  UART4_Write_Line("PIC-Started"); // PIC present report

  PPS_Mapping(_RC5, _OUTPUT, _SDO1_SDA1);

  // Set SPI1 module to master mode, clock = Fosc/4, data sampled at the middle of interval,
  // clock idle state low and data transmitted at low to high edge:
  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);

  // use fat16 quick format instead of init routine if a formatting is needed

//  if (Mmc_Fat_QuickFormat(5) == 0) {
  if (Mmc_Fat_Init() == 0) {
    // reinitialize spi at higher speed
    //SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV4, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
    //--- Test start
    UART4_Write_Line("Test Start.");
    //--- Test routines. Uncomment them one-by-one to test certain features
    M_Create_New_File();
    #ifdef COMPLETE_EXAMPLE
      M_Create_Multiple_Files();
      M_Open_File_Rewrite();
      M_Open_File_Append();
      M_Open_File_Read();
      M_Delete_File();
      M_Test_File_Exist();
      M_Create_Swap_File();
    #endif
    UART4_Write_Line("Test End.");

  }
  else {
    UART4_Write_Line(err_txt); // Note: Mmc_Fat_Init tries to initialize a card more than once.
                               //       If card is not present, initialization may last longer (depending on clock speed)
  }

}