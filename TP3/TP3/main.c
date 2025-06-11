/*
 * TP3.c
 *
 * Created: 02/06/2025 15:21:40
 * Author : santi
 */ 

#include <avr/io.h>
#include "main.h"
#include <stdio.h>

int main(void)
{
	/*
	LCDinit();
	LCDGotoXY(0,0);
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
	LCDsendChar(d1);
	LCDsendChar(d2);
	*/
	i2c_init();
	uart_sendString("hola\r\n");
	fecha f, f2;
	f.anio=25;
	f.mes=6;
	f.dia=9;
	f.hr=15;
	f.min=34;
	f.segs=23;
	i2c_setTime(f);
	f2=i2c_getTime();
	
	char ok[34];
	sprintf(ok, "FECHA: %u/%u/%u HORA: %u:%u:%u\r\n", f2.dia, f2.mes, f2.anio, f2.hr, f2.min, f2.segs);
	
	uart_sendString(ok);
	uart_sendCar(f2.dia+48);
	uart_sendCar('\r');
	uart_sendCar('\n');
	uart_sendCar(f2.mes+48);
	uart_sendCar('\r');
	uart_sendCar('\n');
	uart_sendCar(f2.anio+48);
	uart_sendCar('\r');
	uart_sendCar('\n');
    while (1);
}

