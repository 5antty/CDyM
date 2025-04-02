/*
 * Tp1.cpp
 *
 * Created: 28/03/2025 18:59:25
 * Author : santi
 */

/* Inclusi�n de bibliotecas de c�digo */
#include <avr/io.h>		 // Registros del microcontrolador
#define F_CPU 16000000UL // Defino la frecuencia de oscilador en 8MHz
#include <util/delay.h>	 // Retardos por software

/*Funciones de secuencias de leds*/
void Sec1(void)
{
	DDRD = 0xFF;
	PORTD = 0b10101010;
	_delay_ms(200); // Delay de 100 ms
	PORTD = 0x00;
	PORTD = 0b01010101;
	_delay_ms(200); // Delay de 100 ms
	PORTD = 0x00;
}
void Sec2(void)
{
	DDRD=0xff;
	PORTD = 0x01;
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		_delay_ms(100); // Delay de 100 ms
		PORTD <<= 1;
	}
}

void Sec3(void)
{
	DDRD=0xff;
	int i = 0;
	PORTD = 0x80;
	for (i = 0; i < 8; i++)
	{
		_delay_ms(100); // Delay de 100 ms
		PORTD >>= 1;
	}
	Sec2();
}
/* Funci�n main */
int main(void)
{
	/* Setup */
	/* Loop */

	int cont=0;
	DDRC=0x00;
	PORTC |= (1<<PORTC0) | (1<<PORTC1);
	while (1)
	{
		if(((PINC & (1<<PINC0))==0)&& (cont<3)){
			cont++;
		}
		else if (cont>=3){
			cont=0;
		}
		//_delay_ms(100);
		switch(cont){
			case 0:
				Sec1();
				break;
			case 1:
				Sec2();
				break;
			case 2:
				Sec3();
				break;
		}
	}
	/* Punto de finalizaci�n del programa (NO se debe llegar a este lugar) */
	return 0;
}