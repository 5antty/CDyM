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

char BufferRX[TamBuffers];
uint8_t result=0;
uint8_t color=0;
uint8_t colorSoft=0;
float porc;
void colores(){
	adc_start();
	while(!FlagADC);
	color=result;
	//actualizo el ciclo de trabajo fuera de la uart
	//la uart solo me cambia los flags de los colores a actualizar
	switch(BufferRX[0]){
		case '1':
			colorSoft=0;
			PWM_T1_update(color, color);
		break;
		case '2':
			colorSoft=color;
			PWM_T1_update(0, color);
		break;
		case '3':
			colorSoft=color;
			PWM_T1_update(color, 0);
		break;
		case '4':
			colorSoft=color;
			PWM_T1_update(0, 0);
		break;
		case '5':
			colorSoft=0;
			PWM_T1_update(0, color);
		break;
		case '6':
			colorSoft=0;
			PWM_T1_update(color, 0);
		break;
		case '7':
			colorSoft=0;
			PWM_T1_update(0, 0);
		break;
		case '8':
			colorSoft=color;
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
			
		}
		colores();
		if(FlagADC){
			FlagADC=0;
			color=result;
		}
		
		_delay_ms(100);
    }
	return 0;
}

