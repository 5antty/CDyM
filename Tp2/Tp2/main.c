/*
 * Tp2.c
 *
 * Created: 5/4/2025 4:31:05 PM
 * Author : santi
 */ 

#include <avr/io.h>
#include "main.h"

static volatile uint8_t MEF_flag=0;
static volatile uint8_t cont_MEF=0;

void cargaRegsTimer(void){
	//Utilizamos prescaler de 64
	//MODO CTC WGM02=0 WGM01=1 WGM00=0
	//Prescaler 64
	TCCR0A|=0b00000010;
	TCCR0B|=0x03;
	OCR0A=249;
	TIMSK0=(1<<OCIE0A);
	sei();
}

int main(void)
{
	state estado=S0;
	LCD_Init();
	cargaRegsTimer();
    while (1) 
    {
		if (MEF_flag)
		{
			ActualizarMEF(&estado);
		}
    }
	return 0;
}

ISR(TIMER0_COMPA_vect){
	if (++cont_MEF==100) {
		MEF_flag=1;
		cont_MEF=0;
	}
}

