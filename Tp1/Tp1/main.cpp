/*
 * Tp1.cpp
 *
 * Created: 28/03/2025 18:59:25
 * Author : Villagra Santiago y Troitiño Arian
 */

/* Inclusi�n de bibliotecas de c�digo */
#include <avr/io.h>		 // Registros del microcontrolador
#define F_CPU 16000000UL // Defino la frecuencia de oscilador en 16MHz
#include <util/delay.h>	 // Retardos por software

/*Funciones de secuencias de leds*/
// En todas pongo el registro DDRD como salida ya que seran los LEDs
void Sec1(void)
{
	DDRD = 0xFF;
	PORTD = 0b10101010; // Encendido de LEDs de las posiciones pares.
	_delay_ms(100);		// Delay de 100 ms
	PORTD = 0x00;		// Hago esto para apagar los leds y luego se muestren encedidos unicamente los de las posiciones impares.
	PORTD = 0b01010101;
	_delay_ms(100); // Delay de 100 ms
	PORTD = 0x00;
}
void Sec2(void)
{
	DDRD = 0xff;
	PORTD = 0x01; // Inicializo el registro PORTD con un 1 en el bit menos significativo y el resto queda con 0s.
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		_delay_ms(100); // Delay de 100 ms
		PORTD <<= 1;	// Corrimiento de bit hacia izquierda para que se prendan desde el menos significativo al mas significativo
	}
}

void Sec3(void)
{
	DDRD = 0xff;
	int i = 0;
	PORTD = 0x80; // Inicializo el registro PORTD con un 1 en el bit mas significativo y el resto queda con 0s.
	for (i = 0; i < 8; i++)
	{
		_delay_ms(100); // Delay de 100 ms
		PORTD >>= 1;	// Corrimiento de bit hacia derecha para que se prendan desde el mas significativo al menos significativo
	}
	// Una vez recorri de izquierda a derecha, recorro de derecha a izquierda con la secuencia 2
	Sec2();
}
/* Funcion main */
int main(void)
{
	/* Setup */
	int cont = 0;
	DDRC = 0x00;
	DDRB = 0xff;
	PORTC |= (1 << PORTC0) | (1 << PORTC1); // Pongo en 1 los bits 0 y 1 del registro PORTC, sin alterar lo que hay en el resto de bits.
	/* Loop */
	while (1)
	{
		// Detecto en PINC0 la pulsacion de un pulsador para aumentar el contador y cambiar de secuencia.
		if (((PINC & (1 << PINC0)) == 0) && (cont < 3))
		{
			cont++;
		}
		else if (cont >= 3)
		{
			cont = 0;
		}
		// Detecto en que secuencia estoy y en base a eso cambio los LEDs que se prenden cuando se pulsa el pulsador conectado al PORTC1.
		if ((PINC & (1 << PINC1)) == 0)
		{
			switch (cont)
			{
			case 0:
				PORTB = 0b00001000;
				break;
			case 1:
				PORTB = 0b00010000;
				break;
			case 2:
				PORTB = 0b00011000;
				break;
			}
		}
		else // Si no se esta pulsando el pulsador, se apagan los LEDs.
			PORTB = 0x00;
		// En base al valor que contenga el contador, se ejecuta una secuencia u otra.
		switch (cont)
		{
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
	/* Punto de finalizacion del programa (NO se debe llegar a este lugar) */
	return 0;
}