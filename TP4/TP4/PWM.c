/*
 * PWM.c
 *
 * Created: 07/07/2025 14:35:33
 *  Author: santi
 */ 
#include "PWM_LIB.h"
#define PWM_ON PORTB|=(1<<PORTB5)
#define PWM_OFF PORTB&=~(1<<PORTB5)

uint8_t PWM_PERIOD=255;

//OC1A CONTROLA EL AZUL (OSCURO)
//OC1B CONTROLA EL VERDE (OSCURO)
void PWM_T1(){
	//TCCR1A=(1<<WGM10)|(1<<COM1A1)|(1<<COM1A0)|(1<<COM1B0)|(1<<COM1B1);//Modo 5 invertido ya que los leds se activan en bajo
	TCCR1A=(1<<WGM10)|(1<<COM1A1)|(1<<COM1B1); //Modo 5 no invertido ya que los leds se activan en bajo
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);
	OCR1A=0;
	OCR1B=0;
}

void PWM_T1_update(uint8_t o1b, uint8_t o1a){
	OCR1B=o1b;//Actualizo el verde
	OCR1A=o1a;//Actualizo el azul
}

//CONTROLA EL ROJO
void PWM_soft(uint8_t PWM_DELTA){
	static uint16_t PWM_position=0;
	if(++PWM_position>=PWM_PERIOD)
		PWM_position=0;
	if(PWM_position>PWM_DELTA)
		PWM_OFF;
	else
		PWM_ON;
}
void PWM_init(){
	cargaRegsTimer();
	PWM_T1();
}