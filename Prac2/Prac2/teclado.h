#ifndef teclado
#define teclado
#include "main.h"

#define PORT_KP(Data)  PORTB = (PORTB & 0b11100110) | ((Data & (1 << 7)) >> 3) | ((Data & (1 << 6)) >> 3) | ((Data & (1 << 5)) >> 5);\
		PORTD = (PORTD & 0b01000011) |((Data & (1 << 4)) << 3) | ((Data & (1 << 3))) | ((Data & (1 << 2)) << 3) | ((Data & (1 << 1)) << 3) | ((Data & (1 << 0)) << 2);
#define DDR_KP(Data)  PORTB = (PORTB & 0b11100110) | ((Data & (1 << 7)) >> 3) | ((Data & (1 << 6)) >> 3) | ((Data & (1 << 5)) >> 5);\
		PORTD = (PORTD & 0b01000011) |((Data & (1 << 4)) << 3) | ((Data & (1 << 3))) | ((Data & (1 << 2)) << 3) | ((Data & (1 << 1)) << 3) | ((Data & (1 << 0)) << 2);
#define PIN_KP ((PINB & (1 << 4)) << 3) | ((PINB & (1 << 3)) << 3) | ((PINB & (1 << 0)) << 5) | ((PIND & (1 << 7)) >> 3) | ((PIND & (1 << 3)) << 0) | ((PIND & (1 << 5)) >> 3) | ((PIND & (1 << 4)) >> 3) | ((PIND & (1 << 2)) >> 1)

uint8_t KepadUpdate(void);
uint8_t KEYPAD_Scan(uint8_t *pkey);

#endif