/*
 * TP4.c
 *
 * Created: 07/07/2025 14:24:50
 * Author : González Villagra, Santiago
 */ 

#include "main.h"
char BufferRX[TamBuffers];
//Flags ADC y UART0
uint8_t FlagADC=0;
uint8_t FlagUART=0;

//Medida del ADC
uint8_t result=0;

//Variables para los colores y color de software
uint8_t R=255;
uint8_t G=255;
uint8_t B=255;
uint8_t colorSoft=0;

//Funcion que retorna el brillo del codigo del color, en base al valor del ADC
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
		default:
			uart_sendString("Comando erroneo\r\n");
		break;
	}
}

//Inicializo todos los perifericos a utilizar
void initALL(){
	uart_init();
	uart_TXEnable();
	uart_sendString("Ingrese el color\r\n1=RED\r\n2=GREEN\r\n3=BLUE\r\n4=CIAN\r\n5=YELLOW\r\n6=MAGENTA\r\n7=WHITE\r\n8=BLACK\r\n");
	uart_RXEnable();
	uart_RXIEnable();
	PWM_init();
	adc_init();
	adc_start();
	sei();
	DDRB=0xff; //Todo PORTB como salida
}

int main(void)
{
	initALL();
    while (1) 
    {
		//Si se levanta el flag de la uart, actualizo los colores del LED
		if(FlagUART){
			FlagUART=0;
			colores();
		}
		//Se recibio una lectura nueva del ADC, entonces modifico el brillo del LED
		if(FlagADC){
			FlagADC=0;
			colorSoft=brillo(R, result);
			PWM_T1_update(brillo(G, result), brillo(B, result));
			adc_start();
		}
    }
	return 0;
}

