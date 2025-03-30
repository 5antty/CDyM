/*
 * Tp1.cpp
 *
 * Created: 28/03/2025 18:59:25
 * Author : santi
 */ 

/* Inclusi�n de bibliotecas de c�digo */
#include <avr/io.h> // Registros del microcontrolador
#define F_CPU 16000000UL // Defino la frecuencia de oscilador en 8MHz
#include <util/delay.h> // Retardos por software

/*Funciones de secuencias de leds*/
void Sec1(void)
{
	DDRD = 0xFF;
	PORTD = 0b10101010;
	_delay_ms(100); // Delay de 100 ms
	PORTD = 0x00;
	PORTD = 0b01010101;
	_delay_ms(100); // Delay de 100 ms
	PORTD = 0x00;
}
void Sec2(void)
{
	char aux = 0x01;
	DDRD = aux;
	int i=0;
	PORTD = 0x01;
	for (i=0;i<8;i++){
		_delay_ms(100); // Delay de 100 ms
		DDRD = 0x00;
		PORTD <<= 1;
		aux <<= 1;
		DDRD = aux;
	}
}

/* Funci�n main */
int main (void)
{
	/* Setup */
	/* Loop */
	while(1)
	{
		Sec1();
		_delay_ms(100);
		Sec2();
	}
	/* Punto de finalizaci�n del programa (NO se debe llegar a este lugar) */
	return 0;
}
