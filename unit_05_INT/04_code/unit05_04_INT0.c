/* Project: Unit 05 - INT
      Code: unit_05_04_INT0.c

   Objective:   In this project let's use INT0 INTERRUPTION: By pressing 
                PORTB.RB0(INT0) an LED(PORTD.RD4) will light up \o/
                All external interrupts (INT0, INT1 and INT2) 
                can wakeup the processor from Idle or Sleep modes "/

      Author:   microgenios, edited by J3

   PIC Lessons: How to Start to Program PIC 18 - Step-by-step for Beginners!

   Hardware:    Development Boards (OPTIONS):
                   PicGenios:   PIC18F4520 chip   ( https://loja.microgenios.com.br/produto/kit-picgenios-pic18f4520-com-gravador-usb-microicd-licen-a-compilador-mikroc-pro-for-pic/23507 )
                   EasyPIC� 7:  PIC18F45K22 chip  ( https://www.microchip.com/Developmenttools/ProductDetails/TMIK013 )
   Software:    Development Programmer/Debugger:
                                PICkit� 2         ( http://ww1.microchip.com/downloads/en/DeviceDoc/PICkit%202%20v2.61.00%20Setup%20A.zip )
                          mikroProg suite for PIC ( https://www.mikroe.com/blog/mikroprog-suite-for-pic-version-2-3-1-released )

        PDL:    is a free-format English-like text that describes the flow of control and data in a
                program. PDL is not a programming language. It is a collection of some keywords that enable
                a programmer to describe the operation of a program in a stepwise and logical manner:

              BEGIN
                     Call CONFIGMCU
                     Call CONFIGGLABALINTERRUPTION
                     Call CONFIGINDIVIDUALVCTINT0
                 DO FOREVER(ISR)
                        IF Timer0 overflow THEN
                           Toggle PORTD reg. bit 0 on/off
                           Clear TMR0's overflow flag
                        ENDIF
                 ENDDO(ISR)
                 BEGIN/CONFIGMCU
                     Pre-compilation Directives (config PORTD as digital)
                     Configure options for PIC18F45K22 & PIC18F4520
                     Configure all PORTD as digital output (init all LEDs off)
                     Configure RB0/INT0 pin as input (simulate input signal)
                 END/CONFIGMCU
                 BEGIN/CONFIGGLABALINTERRUPTION
                     Config general interruptions High & Low (GIEH & GIEL)
                     Config interruption priority (IPEN)
                 END/CONFIGGLABALINTERRUPTION
                 BEGIN/CONFIGINDIVIDUALVCTINT0
                     Config IF, IP* & IE vectors (Flag, Prior & Enable)
                     Config INTCON2.INTEDG0 = 1(Peculiar to this peripheral only)
                 END/CONFIGINDIVIDUALVCTINT0
              END

       Date:   Nov 2019
*/
                                       // Prototypes
 void configMCU();                     // Config PORTS & TRIS
 void configGlobalInterruption();      // Config GIEH, GIEL & IPEN
 void configIndividualVctINT0();       // Individual peripheral configs (INT0)

 void INTERRUPCAO_HIGH() iv 0x0008 ics ICS_AUTO {
  if(INTCON.INT0IF == 1)
   {
     PORTD.RD4 ^= 1;                   // toggle pin RBO
     INTCON.INT0IF = 0;
   }
}

void ConfigMCU()
{
#ifdef P18F45K22
 ANSELD = 0;                           // WPUR (Weak Pull-ups Resistors) set up:
 INTCON2.RBPU = 0;                     // Remember, RBPU is negated, zero turn it on!
                                       // Turn on pull-ups resistor to PORTB;
                                       // For PIC18F45K22 RBPU is like general key;
                                       // For PIC18F45K22 WPUB is responsable for control
                                       // each pin individual resistors;
 WPUB.WPUB0 = 1 ;                      // Turn on pull-ups at RB0's pin.
#else
 ADCON1 |= 0X0F;
 INTCON2.RBPU = 0;
#endif

 TRISD = 0;
 PORTD = 0;

 TRISB.RB0 = 1;                        // RB0/INT0 pin as input

}

void configGlobalInterruption()
{                                      // General glebal interruptions set up
  INTCON.GIEH = 1;
  INTCON.GIEL = 1;
  RCON.IPEN = 1;
}

void configIndividualVctINT0()
{                                      // Individual peripheral configs (INT0)
  INTCON.INT0IF = 0;                   // Overflow's Flag; this sets on/off interruptions;
  //IP = 1;                            // There is no priority bit associated with INT0;
                                       // It is always a high-priority interrupt source;
  INTCON.INT0IE = 1;                   // Besides IF, IP & IF, there is EDGE Configuration, too!
                                       // Set (= 1), the interrupt is triggered by a rising edge;
                                       // If the bit is clear,the trigger is on the falling edge:
  INTCON2.INTEDG0 = 1;                 // 1 - > rising edge
                                       // 0 - > falling edge
}

void main() {
  configMCU();
  configGlobalInterruption();
  configIndividualVctINT0();

 while(1);                              // I stopped processing!

}