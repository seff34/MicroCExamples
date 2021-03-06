/* Project: Unit 01 - IO
      Code: unit_01_03_pushAndBlinkAndDebounce.c

   Objective:     Blinking LED attached on PORTD's Pin 0; Now we're using flag variables to control
                  the flow on/off LED:) while pressing a button on PORTB's Pin 0 (Momentary button);
                  In this project 8 LEDs are connected to PORTD and 8 buttons are on PORTB
                  of PIC18F4520 uC, running under 8 MHZ crystal (set sw1 dip = 9, LEDs on PORTD);

      Author:   microgenios, edited by J3

  What is debounce?
                 Bouncing is the tendency of any two metal contacts in an electronic
                 device to generate multiple signals as the contacts close or open;
                 debouncing is any kind of hardware device or software that ensures
                 that only a single signal will be acted upon for a single opening
                 or closing of a contact.

   PIC Lessons: How to Start to Program PIC 18 - Step-by-step for Beginners!

   Hardware:    Development Boards(OPTIONS):
                   PicGenios:   PIC18F4520 chip   ( https://loja.microgenios.com.br/produto/kit-picgenios-pic18f4520-com-gravador-usb-microicd-licen-a-compilador-mikroc-pro-for-pic/23507 )
                   EasyPIC? 7:  PIC18F45K22 chip  ( https://www.microchip.com/Developmenttools/ProductDetails/TMIK013 )
   Software:    Development Programmer/Debugger(OPTIONS):
                                PICkit? 2         ( http://ww1.microchip.com/downloads/en/DeviceDoc/PICkit%202%20v2.61.00%20Setup%20A.zip )
                          mikroProg suite for PIC ( https://www.mikroe.com/blog/mikroprog-suite-for-pic-version-2-3-1-released )
    PDL:    is a free-format English-like text that describes the flow of control and data in a
                program. PDL is not a programming language. It is a collection of some keywords that enable
                a programmer to describe the operation of a program in a stepwise and logical manner:

              BEGIN
              
                  Initialize auxiliary flag as unsigned char to button's seal-in
                  
                  Pre-compilation Directives (config PORTB and PORTD as digital)

                  Configure PORTB register bit 0 as digital input (just one button)
                  Configure all PORTD as digital output (init all LED off)

                  DO FOREVER
                      IF Button on PORTB reg. bit 0 is pressed & flag is down THEN
                           Toggle LED on PORTD's pin 0 (use LAT buffer)
                           Set flag up
                           Wait .04s
                      ENDIF
                      IF Button on PORTB reg. bit 0 is NOT pressed & flag is up THEN
                           Set flag down
                           Wait .04s
                      ENDIF
                  ENDDO
              END

       Date:   Oct 2019
*/

void main() {
unsigned char flag = 0;              // Auxiliary flag to button's seal-in;
                                     // After a momentary switch has been pressed and released it generate a bunch of signals (bouncing)
                                     // For PIC18F45K22
#ifdef PIC18F45K22
       ANSELB = 0;                   // Config all the PORTB's pins as digital
       ANSELD = 0;                   // Config all the PORTD's pins as digital
                                     // For PIC18F4520
#else
       ADCON1 |= 0X0F;               // Config all ADC's pins as digital on PIC18F4520
#endif

  /* BEGINNING TO CODE FROM HERE! */
  // Button on PORTB RB0
  TRISB.RB0 = 1;                     // Config RB0 as Input (1=I:)
  PORTB.RB0 = 1;                     // Optional, the MCU do it automatically ;)

  // LEDs on PORTD RD0
  TRISD = 0;                         // Config all PORTD's pins as Output (0=0:)
  PORTD = 0;                         // Config all PORTD's pins as LOW,
                                     // then all LEDs attached to it will be OFF;)

  /* Remember that all pin's are initialize as analogue,
     so we need to config ANSEL (PIC18F45K22) or ADCON1 (PIC18F4520);
     PLEASE GOTO init of this main routine and set directive like this:
     #ifdef/#else/#endif... */

  while(1)
        {                            // Triggered by low level;
                                     // Note: the LED keeps blinking while pressing the button
                                     // Solving: Create a local variable named flag to control the status of the pin (ZERO is closed ONE is opened)
                                     // The flag deals with this debounce problem, avoiding the event of pressing a button being trapped in the first loop below
           if(PORTB.RB0 == 0 && flag == 0 )
          {
                                     // Toggle LED on PORTD's pin 0;
            PORTD.RD0 = ~ LATD.RD0;
            flag = 1;                // force breaking this loop when the user are still pressing the button (the MC works in nonoseconds;)
            Delay_ms(40);            // treat debounce
          }

          if(PORTB.RB0 == 1 && flag == 1 )
          {
            flag = 0;                // Resetting the flag just when the user release the button; ready for the first loop; init cycle again:)
            Delay_ms(40);            // treat debounce
          }

        }
}