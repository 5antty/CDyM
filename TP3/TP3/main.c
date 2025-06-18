/*
 * TP3.c
 *
 * Created: 02/06/2025 15:21:40
 * Author : santi
 */ 
#include "main.h"
volatile uint8_t timer1Flag=0;

void modo1(void){
	char ok[34];
	fecha f;
	if(timer1Flag){
		f=i2c_getTime();
		sprintf(ok, "FECHA: %u/%u/%u HORA: %u:%u:%u\r\n", f.dia, f.mes, f.anio, f.hr, f.min, f.segs);
		uart_sendString(ok);
		timer1Flag=0;
	}
}

int main(void)
{
	/*
	unsigned char d1, d2;
	i2c_init();
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_write(79);
	i2c_write(69);
	i2c_stop();
	
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_stop();
	
	i2c_start();
	i2c_write(0b11010001);
	d1=i2c_read(0);
	d2=i2c_read(1);
	i2c_stop();
	*/
	i2c_init();
	timer1_Init();
	//uart_sendString("hola\r\n");
	fecha f;
	f.anio=25;
	f.mes=6;
	f.dia=9;
	f.hr=15;
	f.min=34;
	f.segs=23;
	i2c_setTime(f);
	
	
	
    while (1){//interrupcion para modo 1, no while true
		modo1();
	}
}

