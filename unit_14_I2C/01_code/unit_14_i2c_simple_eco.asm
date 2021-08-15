
_test:

;unit_14_i2c_simple_eco.c,38 :: 		void test(char err){
;unit_14_i2c_simple_eco.c,39 :: 		if(err == _I2C_TIMEOUT_RD)
	MOVF        FARG_test_err+0, 0 
	XORLW       3
	BTFSS       STATUS+0, 2 
	GOTO        L_test0
;unit_14_i2c_simple_eco.c,40 :: 		RD5_bit = 1;
	BSF         RD5_bit+0, BitPos(RD5_bit+0) 
L_test0:
;unit_14_i2c_simple_eco.c,41 :: 		if(err == _I2C_TIMEOUT_WR)
	MOVF        FARG_test_err+0, 0 
	XORLW       4
	BTFSS       STATUS+0, 2 
	GOTO        L_test1
;unit_14_i2c_simple_eco.c,42 :: 		RD6_bit = 1;
	BSF         RD6_bit+0, BitPos(RD6_bit+0) 
L_test1:
;unit_14_i2c_simple_eco.c,43 :: 		}
L_end_test:
	RETURN      0
; end of _test

_main:

;unit_14_i2c_simple_eco.c,45 :: 		void main(){
;unit_14_i2c_simple_eco.c,47 :: 		ANSELA = 0;                              // Configure PORTA pins as digital
	CLRF        ANSELA+0 
;unit_14_i2c_simple_eco.c,48 :: 		ANSELB = 0;                                // Configure PORTB pins as digital
	CLRF        ANSELB+0 
;unit_14_i2c_simple_eco.c,49 :: 		ANSELC = 0;                                // Configure PORTC pins as digital
	CLRF        ANSELC+0 
;unit_14_i2c_simple_eco.c,52 :: 		TRISB = 0;                                 // Configure PORTB as output
	CLRF        TRISB+0 
;unit_14_i2c_simple_eco.c,53 :: 		TRISD = 0;                                 // Configure PORTB as output
	CLRF        TRISD+0 
;unit_14_i2c_simple_eco.c,54 :: 		LATB = 0;                                  // Clear PORTB
	CLRF        LATB+0 
;unit_14_i2c_simple_eco.c,55 :: 		LATD = 0;                                  // Clear PORTA
	CLRF        LATD+0 
;unit_14_i2c_simple_eco.c,58 :: 		I2C1_Init(100000);                         // initialize I2C communication
	MOVLW       20
	MOVWF       SSP1ADD+0 
	CALL        _I2C1_Init+0, 0
;unit_14_i2c_simple_eco.c,60 :: 		while (1) {                                // loop for capture both packets
L_main2:
;unit_14_i2c_simple_eco.c,62 :: 		I2C1_SetTimeoutCallback(1000,&test);       // enable error flag
	MOVLW       232
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+0 
	MOVLW       3
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+1 
	MOVLW       0
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+2 
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+3 
	MOVLW       _test+0
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+0 
	MOVLW       hi_addr(_test+0)
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+1 
	MOVLW       FARG_test_err+0
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+2 
	MOVLW       hi_addr(FARG_test_err+0)
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+3 
	CALL        _I2C1_SetTimeoutCallback+0, 0
;unit_14_i2c_simple_eco.c,63 :: 		I2C1_Start();                              // issue I2C start signal
	CALL        _I2C1_Start+0, 0
;unit_14_i2c_simple_eco.c,65 :: 		I2C1_Wr(0xA2);                             // send byte via I2C  (device address + W)
	MOVLW       162
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,66 :: 		I2C1_Wr(2);                                // send byte (address of EEPROM location)
	MOVLW       2
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,68 :: 		I2C1_Wr(0xAA);                             // send data (data to be written) 0B10101010
	MOVLW       170
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,70 :: 		I2C1_Stop();                               // issue I2C stop signal
	CALL        _I2C1_Stop+0, 0
;unit_14_i2c_simple_eco.c,72 :: 		Delay_100ms();
	CALL        _Delay_100ms+0, 0
;unit_14_i2c_simple_eco.c,74 :: 		I2C1_Start();                              // issue I2C start signal
	CALL        _I2C1_Start+0, 0
;unit_14_i2c_simple_eco.c,75 :: 		I2C1_Wr(0xA2);                             // send byte via I2C  (device address + W)
	MOVLW       162
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,76 :: 		I2C1_Wr(2);                                // send byte (data address)
	MOVLW       2
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,77 :: 		I2C1_Repeated_Start();                     // issue I2C signal repeated start
	CALL        _I2C1_Repeated_Start+0, 0
;unit_14_i2c_simple_eco.c,78 :: 		I2C1_Wr(0xA3);                             // send byte (device address + R)
	MOVLW       163
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;unit_14_i2c_simple_eco.c,79 :: 		LATB = I2C1_Rd(0);                         // Read the data (NO acknowledge)
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       LATB+0 
;unit_14_i2c_simple_eco.c,80 :: 		I2C1_Stop();                               // issue I2C stop signal
	CALL        _I2C1_Stop+0, 0
;unit_14_i2c_simple_eco.c,82 :: 		Delay_ms(4000);
	MOVLW       41
	MOVWF       R11, 0
	MOVLW       150
	MOVWF       R12, 0
	MOVLW       127
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	DECFSZ      R11, 1, 1
	BRA         L_main4
;unit_14_i2c_simple_eco.c,83 :: 		}
	GOTO        L_main2
;unit_14_i2c_simple_eco.c,84 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
