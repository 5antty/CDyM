/*
 * timer.c
 *
 * Created: 07/05/2025 15:11:22
 *  Author: González Villagra, Santiago
 */ 

#include "timer.h"
static volatile uint8_t cont=0;
extern uint8_t colorSoft;
void cargaRegsTimer(void){
	//MODO CTC WGM02=0 WGM01=1 WGM00=0
	//Prescaler 8 y OCR0A=125 nos da una interrupcion periodica cada 63us.
	TCCR0A|=0b01000010;
	TCCR0B|=0x02;
	OCR0A=125;
	TIMSK0=(1<<OCIE0A);
	sei();
}

ISR(TIMER0_COMPA_vect){
	PWM_soft(colorSoft);
}