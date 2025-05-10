/*
 * Prac2.c
 *
 * Created: 21/04/2025 14:23:22
 * Author : González Villagra, Santiago y Troitiño, Arian
 */

#ifndef teclado
#define teclado

#include <avr/io.h>
#include <stdint.h>

#define PORT_KP(Data1)  PORTB = (PORTB & 0b11100110) | ((Data1 & (1 << 7)) >> 3) | ((Data1 & (1 << 6)) >> 3) | ((Data1 & (1 << 5)) >> 5);\
		PORTD = (PORTD & 0b01000011) |((Data1 & (1 << 4)) << 3) | ((Data1 & (1 << 3))) | ((Data1 & (1 << 2)) << 3) | ((Data1 & (1 << 1)) << 3) | ((Data1 & (1 << 0)) << 2);
#define DDR_KP(Data2)  DDRB = (DDRB & 0b11100110) | ((Data2 & (1 << 7)) >> 3) | ((Data2 & (1 << 6)) >> 3) | ((Data2 & (1 << 5)) >> 5);\
		DDRD = (DDRD & 0b01000011) |((Data2 & (1 << 4)) << 3) | ((Data2 & (1 << 3))) | ((Data2 & (1 << 2)) << 3) | ((Data2 & (1 << 1)) << 3) | ((Data2 & (1 << 0)) << 2);
#define PIN_KP ((PINB & (1 << 4)) << 3) | ((PINB & (1 << 3)) << 3) | ((PINB & (1 << 0)) << 5) | ((PIND & (1 << 7)) >> 3) | ((PIND & (1 << 3)) << 0) | ((PIND & (1 << 5)) >> 3) | ((PIND & (1 << 4)) >> 3) | ((PIND & (1 << 2)) >> 2)

uint8_t KepadUpdate(void);
uint8_t KEYPAD_Scan(uint8_t *pkey);

#endif