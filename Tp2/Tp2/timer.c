/*
 * timer.c
 *
 * Created: 07/05/2025 15:11:22
 *  Author: González Villagra, Santiago y Troitiño, Arian
 */ 

#include "timer.h"

static volatile uint8_t cont_MEF=0;

void cargaRegsTimer(void){
	//Utilizamos prescaler de 64
	//MODO CTC WGM02=0 WGM01=1 WGM00=0
	//Prescaler 64 y OCR0A=249 nos da una interrupcion periodica cada 1ms.
	TCCR0A|=0b00000010;
	TCCR0B|=0x03;
	OCR0A=249;
	TIMSK0=(1<<OCIE0A);
	sei();
}

ISR(TIMER0_COMPA_vect){
	//Utilizamos el contador para que el flag se active cada 100ms
	if (++cont_MEF==100) {
		MEF_flag=1;
		cont_MEF=0;
	}
}