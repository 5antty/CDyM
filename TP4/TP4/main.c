/*
 * TP4.c
 *
 * Created: 07/07/2025 14:24:50
 * Author : santi
 */ 

#include "main.h"

void adc_init(){
	DIDR0= 0x01; //Digital Input Disable (opcional)
	ADCSRA= 0x87;//make ADC enable and select ck/128
	ADMUX= 0x00;// Vref=AVCC, right-justified, ADC0 pin
}

int main(void)
{
	DDRB=0xff;
	PWM_init();
	adc_init();
    /* Replace with your application code */
    while (1) 
    {
		/*
		OCR1A++;
		OCR1B++;
		if(OCR1A==256)
			OCR1A=0;
		if(OCR1B==256)
			OCR1B=0;
			*/
		
    }
	return 0;
}

ISR(ADC){
	
}
