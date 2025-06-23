/*
 * timer1.c
 *
 * Created: 6/11/2025 10:36:12 PM
 *  Author: santi
 */ 
#include "timer1.h"
#include <avr/interrupt.h>

void timer1_Init(){
	TCCR1A=(1<<COM1A0);
	TCCR1B=(1<<WGM12)|(1<<CS12);//MODO CTC prescaler=256
	OCR1A=31249;
	TIMSK1=(1<<OCIE1A);
	sei();
}
ISR(TIMER1_COMPA_vect){
	//Utilizamos el contador para que el flag se active cada 100ms
	timer1Flag=1;
}