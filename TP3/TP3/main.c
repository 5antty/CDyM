/*
 * TP3.c
 *
 * Created: 02/06/2025 15:21:40
 * Author : santi
 */ 

#include <avr/io.h>
#include "main.h"

int main(void)
{
	LCDinit();
	LCDGotoXY(0,0);
	unsigned char d1, d2;
    /* Replace with your application code */
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
    while (1);
}

