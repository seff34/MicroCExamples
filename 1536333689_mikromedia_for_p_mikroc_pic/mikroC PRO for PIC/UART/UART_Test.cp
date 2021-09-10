#line 1 "C:/Users/NOOR TECH ARGE/Desktop/1536333689_mikromedia_for_p_mikroc_pic/mikroC PRO for PIC/UART/UART_Test.c"
#line 24 "C:/Users/NOOR TECH ARGE/Desktop/1536333689_mikromedia_for_p_mikroc_pic/mikroC PRO for PIC/UART/UART_Test.c"
char uart_rd;

void main() {
 ANSELA = 0;
 ANSELB = 0;
 ANSELD = 0;
 ANSELE = 0;
 ANSELF = 0;
 ANSELG = 0;
#line 41 "C:/Users/NOOR TECH ARGE/Desktop/1536333689_mikromedia_for_p_mikroc_pic/mikroC PRO for PIC/UART/UART_Test.c"
 UART4_Init(115200);

 Delay_ms(100);
#line 52 "C:/Users/NOOR TECH ARGE/Desktop/1536333689_mikromedia_for_p_mikroc_pic/mikroC PRO for PIC/UART/UART_Test.c"
 UART_Write_Text("Start");
 UART_Write(13);
 UART_Write(10);


 while (1) {
#line 67 "C:/Users/NOOR TECH ARGE/Desktop/1536333689_mikromedia_for_p_mikroc_pic/mikroC PRO for PIC/UART/UART_Test.c"
 if (UART_Data_Ready()) {
 uart_rd = UART_Read();
 UART_Write(uart_rd);
 }

 }
}
