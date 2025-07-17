/*
 * ADC.c
 *
 * Created: 17/07/2025 14:12:53
 *  Author: santi
 */ 
#include "ADC_LIB.h"
extern volatile uint8_t result;
extern volatile uint8_t FlagADC;
void adc_init(){
	DIDR0= 0x01; //Digital Input Disable (opcional)
	ADCSRA= 0x8F;//make ADC enable and select ck/128
	ADMUX= 0b01100011;// Vref=AVCC, right-justified, ADC3 pin
}
void adc_start(){
	ADCSRA|=(1<<ADSC);
}

ISR(ADC_vect){
	result=ADCH;//Como es de 10 bits da valores entre 0 y 1023
	FlagADC=1;
}