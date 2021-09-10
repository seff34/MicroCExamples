
_main:

;UART_Test.c,26 :: 		void main() {
;UART_Test.c,27 :: 		ANSELA = 0;
	CLRF        ANSELA+0 
;UART_Test.c,28 :: 		ANSELB = 0;
	CLRF        ANSELB+0 
;UART_Test.c,29 :: 		ANSELD = 0;
	CLRF        ANSELD+0 
;UART_Test.c,30 :: 		ANSELE = 0;
	CLRF        ANSELE+0 
;UART_Test.c,31 :: 		ANSELF = 0;
	CLRF        ANSELF+0 
;UART_Test.c,32 :: 		ANSELG = 0;
	CLRF        ANSELG+0 
;UART_Test.c,41 :: 		UART4_Init(115200);
	BSF         BAUDCON4+0, 3, 0
	MOVLW       138
	MOVWF       SPBRG4+0 
	MOVLW       0
	MOVWF       SPBRG4+1 
	BSF         TXSTA4+0, 2, 0
	CALL        _UART4_Init+0, 0
;UART_Test.c,43 :: 		Delay_ms(100);                              // Wait for UART module to stabilize
	MOVLW       9
	MOVWF       R11, 0
	MOVLW       30
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	DECFSZ      R11, 1, 1
	BRA         L_main0
	NOP
;UART_Test.c,52 :: 		UART_Write_Text("Start");
	MOVLW       ?lstr1_UART_Test+0
	MOVWF       FARG_UART_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_UART_Test+0)
	MOVWF       FARG_UART_Write_Text_uart_text+1 
	CALL        _UART_Write_Text+0, 0
;UART_Test.c,53 :: 		UART_Write(13);
	MOVLW       13
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;UART_Test.c,54 :: 		UART_Write(10);
	MOVLW       10
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;UART_Test.c,57 :: 		while (1) {
L_main1:
;UART_Test.c,67 :: 		if (UART_Data_Ready()) {     // If data is received,
	CALL        _UART_Data_Ready+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main3
;UART_Test.c,68 :: 		uart_rd = UART_Read();     // read the received data,
	CALL        _UART_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _uart_rd+0 
;UART_Test.c,69 :: 		UART_Write(uart_rd);       // and send data via UART
	MOVF        R0, 0 
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;UART_Test.c,70 :: 		}
L_main3:
;UART_Test.c,72 :: 		}
	GOTO        L_main1
;UART_Test.c,73 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
