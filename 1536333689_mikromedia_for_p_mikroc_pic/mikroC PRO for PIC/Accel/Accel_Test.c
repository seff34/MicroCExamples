/*
 * Project name:
     Accelerometer Test
 * Copyright:
     (c) MikroElektronika, 2005-2018.
  * Revision History:
     20180906:
       - initial release (FK);
       - measurement displayed on TFT (FK);
 * Description:
     This is a simple project which demonstrates the use of Accel on-board module.
     Measured coordinates (X,Y,Z) are being shown on TFT display.
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

// ADXL345 Register Definition
#define _POWER_CTL      0x2D
#define _DATA_FORMAT    0x31
#define _BW_RATE        0x2C
#define _DATAX0         0x32
#define _DATAX1         0x33
#define _DATAY0         0x34
#define _DATAY1         0x35
#define _DATAZ0         0x36
#define _DATAZ1         0x37
#define _FIFO_CTL       0x38
#define _SPEED          0x0F                       // Buffer Speed - 3200Hz

#define _ACCEL_ERROR    0x02

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

unsigned short temp;
char out[16];
int readings[3] = {0, 0, 0};                       // X, Y and Z

void ADXL345_Write(unsigned short address, unsigned short data1) {
  I2C2_Start();              // issue I2C start signal
  I2C2_Wr(0x3A);             // send byte via I2C  (device address + W)
  I2C2_Wr(address);          // send byte (address of the location)
  I2C2_Wr(data1);            // send data (data to be written)
  I2C2_Stop();               // issue I2C stop signal
}

unsigned short ADXL345_Read(unsigned short address) {
  unsigned short tmp = 0;

  I2C2_Start();              // issue I2C start signal
  I2C2_Wr(0x3A);             // send byte via I2C (device address + W)
  I2C2_Wr(address);          // send byte (data address)
  
  I2C2_Start();              // issue I2C signal repeated start
  I2C2_Wr(0x3B);             // send byte (device address + R)
  tmp = I2C2_Rd(0);          // Read the data (NO acknowledge)
  I2C2_Stop();               // issue I2C stop signal

  return tmp;
}

char ADXL345_Init(void) {
  char id = 0x00;

  // Go into standby mode to configure the device.
  ADXL345_Write(0x2D, 0x00);

  id = ADXL345_Read(0x00);
  if (id != 0xE5) {
    return _ACCEL_ERROR;
  }
  else {
    ADXL345_Write(_DATA_FORMAT, 0x08);       // Full resolution, +/-2g, 4mg/LSB, right justified
    ADXL345_Write(_BW_RATE, 0x0A);           // Set 100 Hz data rate
    ADXL345_Write(_FIFO_CTL, 0x80);          // stream mode
    ADXL345_Write(_POWER_CTL, 0x08);         // POWER_CTL reg: measurement mode
    return 0x00;
  }
}

// Read X Axis
int Accel_ReadX(void) {
  char low_byte;
  int Out_x;

  Out_x = ADXL345_Read(_DATAX1);
  low_byte = ADXL345_Read(_DATAX0);

  Out_x = (Out_x << 8);
  Out_x = (Out_x | low_byte);

  return Out_x;
}

// Read Y Axis
int Accel_ReadY(void) {
  char low_byte;
  int Out_y;

  Out_y = ADXL345_Read(_DATAY1);
  low_byte = ADXL345_Read(_DATAY0);

  Out_y = (Out_y << 8);
  Out_y = (Out_y | low_byte);

  return Out_y;
}

// Read Z Axis
int Accel_ReadZ(void) {
  char low_byte;
  int Out_z;

  Out_z = ADXL345_Read(_DATAZ1);
  low_byte = ADXL345_Read(_DATAZ0);

  Out_z = (Out_z << 8);
  Out_z = (Out_z | low_byte);

  return Out_z;
}

// Calculate the average values of the X, Y and Z axis reads
void Accel_Average(void) {
  int i, sx, sy, sz;

  // sum
  sx = sy = sz = 0;
  
  // average accelerometer reading over last 16 samples
  for (i=0; i<16; i++) {
    sx += Accel_ReadX();
    sy += Accel_ReadY();
    sz += Accel_ReadZ();
  }
  // average
  readings[0] = sx >> 4;
  readings[1] = sy >> 4;
  readings[2] = sz >> 4;
}

// Display average X-axis read value on TFT
void Display_X_Value(void) {
  TFT_Rectangle(160, 100, 200, 115);
  TFT_Write_Text("X: ", 140, 100);
  IntToStr(readings[0], out);
  TFT_Write_Text(out, 160, 100);
  Delay_ms(100);
}

// Display average Y-axis read value on TFT
void Display_Y_Value(void) {
  TFT_Rectangle(160, 130, 200, 145);
  TFT_Write_Text("Y: ", 140, 130);
  IntToStr(readings[1], out);
  TFT_Write_Text(out, 160, 130);
  Delay_ms(100);
}

// Display average z-axis read value on TFT
void Display_Z_Value(void) {
  TFT_Rectangle(160, 160, 200, 175);
  TFT_Write_Text("Z: ", 140, 160);
  IntToStr(readings[2], out);
  TFT_Write_Text(out, 160, 160);
  Delay_ms(100);
}

void main() {
  Delay_ms(150);

  ANSELA = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  ANSELG = 0;
  ANSELF = 0;

  TFT_Set_Default_Mode();
  TFT_Init_ST7789V_8bit(320, 240);

  // Initialize I2C communication
  I2C2_Init(100000);

  TFT_Fill_Screen(CL_AQUA);
  TFT_Set_Pen(CL_AQUA, 1);
  TFT_Set_Brush(1, CL_AQUA, 0, 0, 0, 0);

  TFT_Write_Text("Starting Accel test...", 90, 100);
  Delay_ms(2000);
  TFT_Fill_Screen(CL_AQUA);

  // Initialize ADXL345 accelerometer
  if (ADXL345_Init() == 0) {
    TFT_Write_Text("Accel module initialized.", 80, 100);
    Delay_ms(2000);
    TFT_Fill_Screen(CL_AQUA);
  }
    else {
     TFT_Write_Text("Error during Accel module initialization.", 70, 100);
    }

  Delay_ms(150);

  while(1) {
    TFT_Write_Text("Reading axis values :", 80, 70);
    Accel_Average();               // Calculate average X, Y and Z reads
    Display_X_Value();             // Display average X value read
    Display_Y_Value();             // Display average Y value read
    Display_Z_Value();             // Display average Z value read
    Delay_ms(800);
  }
}