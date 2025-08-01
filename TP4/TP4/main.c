/*
 * TP4.c
 *
 * Created: 07/07/2025 14:24:50
 * Author : santi
 */ 

#include "main.h"
#define  F_CPU 16000000UL 
#include <util/delay.h>

uint8_t FlagADC=0;
uint8_t FlagUART=0;
uint8_t R=255;
uint8_t G=255;
uint8_t B=255;

char BufferRX[TamBuffers];
uint8_t result=0;
uint8_t colorSoft=0;

uint8_t brillo(uint8_t ccolor, uint8_t adcv)
{
	return 255 - ((255 - ccolor) * adcv) / 255;
}

void colores(){
	//actualizo el ciclo de trabajo fuera de la uart
	//la uart solo me cambia los flags de los colores a actualizar
	switch(BufferRX[0]){
		case '1'://ROJO
			R=0;
			G=255;
			B=255;
		break;
		case '2'://VERDE
			R=255;
			G=0;
			B=255;
		break;
		case '3'://AZUL
			R=255;
			G=255;
			B=0;
		break;
		case '4'://CIAN
			R=255;
			G=0;
			B=0;
		break;
		case '5'://AMARILLO
			R=0;
			G=0;
			B=255;
		break;
		case '6'://MAGENTA
			R=0;
			G=255;
			B=0;
		break;
		case '7'://BLANCO
			R=0;
			G=0;
			B=0;
		break;
		case '8'://NEGRO
			R=255;
			G=255;
			B=255;
		break;
	}
}

void initALL(){
	uart_init();
	uart_TXEnable();
	uart_sendString("Ingrese el color\r\n1=RED\r\n2=GREEN\r\n3=BLUE\r\n4=CIAN\r\n5=YELLOW\r\n6=MAGENTA\r\n7=WHITE\r\n8=BLACK\r\n");
	uart_RXEnable();
	uart_RXIEnable();
	PWM_init();
	adc_init();
	sei();
	DDRB=0xff;
}

int main(void)
{
	
	initALL();
    /* Replace with your application code */
    while (1) 
    {
		if(FlagUART){
			FlagUART=0;
			colores();
		}
		adc_start();
		while(!FlagADC);
		FlagADC=0;
		colorSoft=brillo(R, result);
		PWM_T1_update(brillo(G, result), brillo(B, result));
    }
	return 0;
}

