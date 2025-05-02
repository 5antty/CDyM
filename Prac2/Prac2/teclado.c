/*
 * Prac2.cpp
 *
 * Created: 21/04/2025 14:23:22
 * Author : santi
 */

#include <avr/io.h>
#include "teclado.h"

uint8_t KepadUpdate(void)
{
	uint8_t r, c;
	PORT_KP(0x0F);
	for (c = 0; c < 4; c++)
	{
		//DDR_KP(0x00);
		//DDR_KP &= ~(0xff);
		
		DDR_KP(0x80 >> c);
		//PORT_KP(~(0x80 >> c));
		for (r = 0; r < 4; r++)
		{
			if (!(PIN_KP & (0x08 >> r)))
			{
				return (r * 4 + c);
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