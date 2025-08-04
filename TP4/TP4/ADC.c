/*
 * ADC.c
 *
 * Created: 17/07/2025 14:12:53
 *  Author: González Villagra, Santiago
 */ 
#include "ADC_LIB.h"
extern volatile uint8_t result;
extern volatile uint8_t FlagADC;
void adc_init(){
	DIDR0= 0x01; //Deshabilito la entrada digital
	ADCSRA= 0x8F;//ADC enable y prescaler clk/128
	ADMUX= 0b01100011;// Vref=AVCC, justificado a derecha, ADC3 pin e interrupcion activada
}
void adc_start(){
	ADCSRA|=(1<<ADSC);
}

ISR(ADC_vect){
	result=ADCH;//Me quedo con la parte alta, ya que los bits menos significativos probablemente sean ruido
	FlagADC=1;
}