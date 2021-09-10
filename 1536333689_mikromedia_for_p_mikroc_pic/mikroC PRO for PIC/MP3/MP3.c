/* Project name:
     MP3
 * Copyright:
     (c) Mikroelektronika, 2010-2018.
 * Revision History:
     20180906:
       - initial release;     
 * Description:
     This project demonstrates communication with VS1011E mp3 codec.
     Program reads one mp3 file from MMC and sends it to VS1053E for decoding
     and playing.
     MMC and MP3_SCI share Hardware SPI module.
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
     - SD card must contain a file called "sound.mp3"
     - Make sure that MMC card contains appropriate mp3 file.
     - MMC FAT library is for PIC18 MCUs only.
     - UART is initialized at 9600 baud rate.
 */

#include <built_in.h>

sbit Mmc_Chip_Select           at LATD0_bit;
sbit MP3_CS                    at LATF5_bit;
sbit MP3_RST                   at LATF4_bit;
sbit DREQ                      at PORTF.B3;
sbit BSYNC                     at LATF6_bit;

sbit Mmc_Chip_Select_Direction at TRISD0_bit;
sbit MP3_CS_Direction          at TRISF5_bit;
sbit MP3_RST_Direction         at TRISF4_bit;
sbit DREQ_Direction            at TRISF3_bit;
sbit BSYNC_Direction           at TRISF6_bit;

// VS1053 constants
const char WRITE_CODE  = 0x02;
const char READ_CODE   = 0x03;
const char SCI_MODE_ADDR   = 0x00;
const char SCI_CLOCKF_ADDR = 0x03;
const char SCI_VOL_ADDR    = 0x0B;
const char SCI_BASS_ADDR = 0x02;

// global variables
char filename[14] = "sound.mp3";
unsigned long i, file_size;
char data_buffer_32[32];
const BUFFER_SIZE = 512;
char BufferLarge[BUFFER_SIZE];
char volume_left, volume_right;

// Write text and goto new line CR and LF
void UART_Write_Line (char *text) {
  UART_Write_Text(text);
  UART_Write(13);
  UART_Write(10);
}

// Writes one byte to MP3 SCI
void MP3_SCI_Write(char address, unsigned int data_in) {
  BSYNC = 1;

  MP3_CS = 0;                             // select MP3 SCI
  SPI1_Write(WRITE_CODE);
  SPI1_Write(address);
  SPI1_Write(Hi(data_in));                // high byte
  SPI1_Write(Lo(data_in));                // low byte
  MP3_CS = 1;                             // deselect MP3 SCI
  while (DREQ == 0);                      // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

// Reads words_count words from MP3 SCI
void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer) {
  unsigned int temp;

  MP3_CS = 0;                             // select MP3 SCI
  SPI1_Write(READ_CODE);
  SPI1_Write(start_address);

  while (words_count--) {                 // read words_count words byte per byte
    temp = SPI1_Read(0);
    temp <<= 8;
    temp += SPI1_Read(0);
    *(data_buffer++) = temp;
  }
  MP3_CS = 1;                             // deselect MP3 SCI
  while (DREQ == 0);                      // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

// Write one byte to MP3 SDI
void MP3_SDI_Write(char data_) {

  MP3_CS = 1;
  BSYNC = 0;

  while (DREQ == 0);                      // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  SPI1_Write(data_);
  BSYNC = 1;
}

// Write 32 bytes to MP3 SDI
void MP3_SDI_Write_32(char *data_) {
  char i;

  MP3_CS = 1;
  BSYNC = 0;

  while (DREQ == 0);                      // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  for (i=0; i<32; i++)
  SPI1_Write(data_[i]);
  BSYNC = 1;
}

// Set volume
void Set_Volume(char left,char right) {
  unsigned int volume;

  volume = (left<<8) + right;             // calculate value
  MP3_SCI_Write(SCI_VOL_ADDR, volume);        // Write value to VOL register
}
// If volume Buttons are pressed update volume

void MP3_init() {
  BSYNC = 1;
  MP3_CS = 1;

  // Hardware reset
  MP3_RST = 0;
  Delay_ms(10);
  MP3_RST = 1;
  
  while (DREQ == 0);
  MP3_SCI_Write(SCI_MODE_ADDR, 0x0800);
  MP3_SCI_Write(SCI_BASS_ADDR, 0x7A00);
  MP3_SCI_Write(SCI_CLOCKF_ADDR, 0x2000); // default 12 288 000 Hz


  volume_left  = 0x00;                      // Set volume to initial value
  volume_right = 0x00;
  Set_Volume(volume_left,volume_right);
}


void Init() {

  ANSELA = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  ANSELF = 0;
  ANSELG = 0;

  TRISF7_bit = 0;
  LATF7_bit = 1;                   // Disable Serial Flash module

  MP3_CS_Direction  = 0;                  // Configure MP3_CS as output
  MP3_CS            = 1;                  // Deselect MP3_CS
  MP3_RST_Direction = 0;                  // Configure MP3_RST as output
  MP3_RST           = 1;                  // Set MP3_RST pin

  DREQ_Direction  = 1;                    // Configure DREQ as input
  BSYNC_Direction = 0;                    // Configure BSYNC as output
  BSYNC           = 0;                    // Clear BSYNC
  BSYNC           = 1;                    // Clear BSYNC
}


// main
void main() {
  Init();

  // Initialize USART for signaling
  UART4_Init(9600);
  Delay_100ms();

  UART_Write_Line("Initializing SPI");
  
  Unlock_IOLOCK();
  PPS_Mapping(_RC5, _OUTPUT, _SDO1_SDA1);
  Lock_IOLOCK();
  
//  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_END, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);

  UART_Write_Line("Initializing VS1053E decoder interface");
  MP3_init();

  UART_Write_Line("Initializing MMC_FAT");
  if (Mmc_Fat_Init() == 0) {
    if (Mmc_Fat_Assign(&filename, 0) ) {
      UART_Write_Line("File Assigned");
      Mmc_Fat_Reset(&file_size);          // Call Reset before file reading,
                                          //   procedure returns size of the file
      // send file blocks to MP3 SDI
      while (file_size > BUFFER_SIZE) {

        for (i=0; i<BUFFER_SIZE; i++) {
          Mmc_Fat_Read(BufferLarge + i);
        }
        for (i=0; i<BUFFER_SIZE/32; i++) {
          MP3_SDI_Write_32(BufferLarge + i*32);
        }
        file_size -= BUFFER_SIZE;
     }

      // send the rest of the file to MP3 SDI
      for (i=0; i<file_size; i++) {
        Mmc_Fat_Read(BufferLarge + i);
      }

      for (i=0; i<file_size; i++) {
        MP3_SDI_Write(BufferLarge[i]);
      }
    }
    else {
      UART_Write_Line("File not assigned");
    }
  }
  else {
    UART_Write_Line("MMC FAT not initialized");
  }
}