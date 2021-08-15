#line 1 "C:/Users/sefae/Downloads/pic18f-master/unit_14_I2C/01_code/unit_14_i2c_simple_eco.c"
#line 38 "C:/Users/sefae/Downloads/pic18f-master/unit_14_I2C/01_code/unit_14_i2c_simple_eco.c"
void test(char err){
 if(err == _I2C_TIMEOUT_RD)
 RD5_bit = 1;
 if(err == _I2C_TIMEOUT_WR)
 RD6_bit = 1;
}

void main(){

 ANSELA = 0;
 ANSELB = 0;
 ANSELC = 0;


 TRISB = 0;
 TRISD = 0;
 LATB = 0;
 LATD = 0;


 I2C1_Init(100000);

 while (1) {

 I2C1_SetTimeoutCallback(1000,&test);
 I2C1_Start();

 I2C1_Wr(0xA2);
 I2C1_Wr(2);

 I2C1_Wr(0xAA);

 I2C1_Stop();

 Delay_100ms();

 I2C1_Start();
 I2C1_Wr(0xA2);
 I2C1_Wr(2);
 I2C1_Repeated_Start();
 I2C1_Wr(0xA3);
 LATB = I2C1_Rd(0);
 I2C1_Stop();

 Delay_ms(4000);
 }
}
