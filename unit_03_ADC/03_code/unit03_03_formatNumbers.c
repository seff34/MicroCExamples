/* Project: Unit 03 - ADC
      Code: unit_03_03_formatNumbers.c

   Objective:   This code tells you how you can format the number you will present on screen:)
                We will  read channels (0 & 1) and present at LCD screen, like this:
                [AN0: ranged 0-100%]  ie: S1: 56%
                [AN1: ranged 0-255 ]  ie: S2: 255


   Lib Notes :  Select these Libraries (LIB.MANAGER) for mikroC PRO for PIC compiler:)
                 > ADC
                 > LCD
                 > Conversions

      Author:   microgenios, edited by J3

   PIC Lessons: How to Start to Program PIC 18 - Step-by-step for Beginners!

   Hardware:    Development Boards (OPTIONS):
                   PicGenios:   PIC18F4520 chip   ( https://loja.microgenios.com.br/produto/kit-picgenios-pic18f4520-com-gravador-usb-microicd-licen-a-compilador-mikroc-pro-for-pic/23507 )
                   EasyPIC� 7:  PIC18F45K22 chip  ( https://www.microchip.com/Developmenttools/ProductDetails/TMIK013 )
   Software:    Development Programmer/Debugger:
                                PICkit� 2         ( http://ww1.microchip.com/downloads/en/DeviceDoc/PICkit%202%20v2.61.00%20Setup%20A.zip )
                          mikroProg suite for PIC ( https://www.mikroe.com/blog/mikroprog-suite-for-pic-version-2-3-1-released )
   The LCD is connected to the microcontroller as follows:
                        easyPIC v7 board:                     microgenios board:
                    Microcontroller      LCD               Microcontroller      LCD
                    ===============      ===               ===============      ===
                        RB0              D4                    RB4              D4
                        RB1              D5                    RB5              D5
                        RB2              D6                    RB6              D6
                        RB3              D7                    RB7              D7
                        RB4              E                     RB1              E
                        RB5              R/S                   RB2              R/S
                        GND              RW                    GND              RW


        PDL:    is a free-format English-like text that describes the flow of control and data in a
                program. PDL is not a programming language. It is a collection of some keywords that enable
                a programmer to describe the operation of a program in a stepwise and logical manner:

              BEGIN
                  Choose the board to work with (easyPIC or microgenios)
                  Configure  LCD module connections
                  CAll CONFIGMCU
                  
                  Initialize the LCD
                  Clear the LCD
                  Set cursor off

                DO FOREVER

                    Read ADC Ch 00 and Ch 01
                    Convert number to txt
                    Show the result in LCD
                    Wait .2s
                ENDDO

                BEGIN/CONFIGMCU
                    Configure PORTB as digital outputs
                    Configure PORTA as digital outputs
                    Configure PORTD as digital outputs
                    Configure ADC's Registers (ADCON0,1 & 2)
                END/CONFIGMCU


              END

       Date:   Nov 2019
*/
#define TRUE 1

                                      // PIC18F45K22  - easyPIC v7 Board
                                      // LCD module connections
/*sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;*/
                                      // End LCD module connections

                                      // picMicrogenios board

sbit LCD_RS at LATE2_bit;
sbit LCD_EN at LATE1_bit;
sbit LCD_D4 at LATD4_bit;
sbit LCD_D5 at LATD5_bit;
sbit LCD_D6 at LATD6_bit;
sbit LCD_D7 at LATD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


void ConfigMCU();                    // Function prototype

void ConfigMCU()                     // Config MCU's PORTS
{
#ifdef P18F45K22
  ANSELB = 0;
  ANSELA.B0 = 1;                     // AN0
  ANSELA.B1 = 1;                     // AN1
#else
  ADCON1 |= 0B00001101;              // AN0 e AN1 see datasheet
#endif

  TRISA.RA0 = 1;
  PORTA.RA0 = 1;

  TRISA.RA1 = 1;
  PORTA.RA1 = 1;

}
void main(){
  unsigned int read_ADC;
  unsigned char txt[10];

  ConfigMCU();                       // Init MCU

  Lcd_Init();                        // Init display Mode 4 bits
  Lcd_Cmd(_LCD_CLEAR);               // Display clear
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  Lcd_Out(1,1,"S1:");                // Line x Column
  Lcd_Out(2,1,"S2:");

  ADC_Init();

 while(TRUE)
 {
                                     // *****S1
   read_ADC = ADC_Read(0);           // S1 -> AN0
                                     // S2 -> AN1
   read_ADC = (int)read_ADC * (100./1023.);
   WordToStr(read_ADC, txt);        // 65535 + 0 = 6 positions
   LCD_Out(1,4, txt);
   LCD_Chr_Cp('%');
   Delay_ms(20);

                                     // *****S2
   read_ADC = ADC_Read(1);           // S1 -> AN0
                                     // S2 -> AN1
   read_ADC = (int)read_ADC * (255./1023.);
   WordToStr(read_ADC, txt);         // 65535 + 0 = 6 positions
   LCD_Out(2,4, txt);
   Delay_ms(20);
 }
}