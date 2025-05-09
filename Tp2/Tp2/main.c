/*
 * Tp2.c
 *
 * Created: 5/4/2025 4:31:05 PM
 * Author : santi
 */ 

#include <avr/io.h>
#include "main.h"

volatile uint8_t MEF_flag=0;

int main(void)
{
	
	LCD_Init();
	IniciarMEF();
    while (1) 
    {
		if (MEF_flag)
		{
			ActualizarMEF();
			MEF_flag=0;
		}
    }
	return 0;
}



