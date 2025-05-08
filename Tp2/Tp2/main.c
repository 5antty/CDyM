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
	state estado=S0;
	LCD_Init();
	//cargaRegsTimer();
    while (1) 
    {
		if (MEF_flag)
		{
			ActualizarMEF(&estado);
			MEF_flag=0;
		}
    }
	return 0;
}



