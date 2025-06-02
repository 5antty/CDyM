/*
 * Practica3.c
 *
 * Created: 19/05/2025 14:37:10
 * Author : santi
 */ 

#include <avr/io.h>
#define  F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	uint16_t note[12] = {
		262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494
	};
	
	/*
		1hz = 16mhz/2*prescaler*(1+ocr1a)
		16*10^6=2*prescaler(1+ocr1a)
		
		prescaler = 256
		ocr1a=31250-1=31249
	*/
	/*Configuarcion ej a)
	DDRB=(1<<PORTB1);
	TCCR1A=(1<<COM1A0);
	TCCR1B=(1<<WGM12)|(1<<CS10);//MODO CTC no prescaler
	while (1)
	{
		int i;
		for (i=0; i<12; i++)
		{
			OCR1A=(16000000/(2*note[i]))-1;
			_delay_ms(2000);
			if(i==11){
				i=0;
			}
		}
	}
	
	*/
	//Configuracion ej b)
	TCCR1A=(1<<COM1A0)|(1<<COM1B0);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(1<<CS10);
	//OCR1A=31249;
	DDRB=(1<<PORTB1)|(1<<PORTB2);
	float T, T2;
    while (1) 
    {
		int i;
		for (i=0; i<12; i++)
		{
			ICR1=(16000000/(2*(note[i])))-1;
			OCR1A=ICR1*0.5;
			T=2*(OCR1A+1)/16000000;
			OCR1B=ICR1;
			_delay_ms(2000);
			if(i==11){
				i=0;
			}
		}
    }
	return 0;
}
