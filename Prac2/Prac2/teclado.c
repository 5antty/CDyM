/*
 * Prac2.c
 *
 * Created: 21/04/2025 14:23:22
 * Author : González Villagra, Santiago y Troitiño, Arian
 */

#include "teclado.h"

uint8_t KepadUpdate(void)
{
	int col, filas;
	PORT_KP(0x0F);
	for (filas = 0; filas < 4; filas++)
	{
		DDR_KP(0x00);
		DDR_KP(0x80 >> filas);
		for (col = 0; col < 4; col++)
		{
			if (!((PIN_KP) & (0x08 >> col)))
			{
				int tecla = filas * 4 + col;
				switch(tecla){
					case 0:
						return 55;
						break;
					case 1:
						return 56;
						break;
					case 2:
						return 57;
						break;
					case 3:
						return 47;
						break;
					case 4:
						return 52;
						break;
					case 5:
						return 53;
						break;
					case 6:
						return 54;
						break;
					case 7:
						return 42;
						break;
					case 8:
						return 49;
						break;
					case 9:
						return 50;
						break;
					case 10:
						return 51;
						break;
					case 11:
						return 45;
						break;
					case 12:
						return 64;
						break;
					case 13:
						return 48;
						break;
					case 14:
						return 61;
						break;
					case 15:
						return 43;
						break;
				}
			}
		}
	}

	return 0xff; // Tecla no presionada
}

uint8_t KEYPAD_Scan(uint8_t *pkey)
{
	static uint8_t Old_key, Last_valid_key = 0xFF; // no hay tecla presionada;
	uint8_t Key = KepadUpdate();
	if (Key == 0xFF)
	{
		Old_key = 0xFF; // no hay tecla presionada
		Last_valid_key = 0xFF;
		return 0;
	}
	if (Key == Old_key)
	{ // 2da verificación
		if (Key != Last_valid_key)
		{ // evita múltiple detección
			*pkey = Key;
			Last_valid_key = Key;
			return 1;
		}
	}
	Old_key = Key; // 1era verificación
	return 0;
}