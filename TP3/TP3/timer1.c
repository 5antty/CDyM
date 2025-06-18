/*
 * timer1.c
 *
 * Created: 6/11/2025 10:36:12 PM
 *  Author: santi
 */ 
#include "timer1.h"
#include <avr/interrupt.h>

void timer1_Init(){
	DDRB=(1<<PORTB1);//salida por PORTB1
	TCCR1A=(1<<COM1A0);
	TCCR1B=(1<<WGM12)|(1<<CS10);//MODO CTC no prescaler
	TIMSK1=(1<<OCIE1A);
	sei();
}
ISR(TIMER1_COMPA_vect){
	//Utilizamos el contador para que el flag se active cada 100ms
	timer1Flag=1;
}