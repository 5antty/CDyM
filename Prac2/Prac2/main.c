/*
 * Prac2.c
 *
 * Created: 02/05/2025 15:04:36
 * Author : santi
 */ 

#include "main.h"

int main (void){
	uint8_t car, ok;
	LCDinit();
	LCDGotoXY(0,0);
	LCDstring((uint8_t *)"FUNCIONO", 8);
	_delay_ms(1000);
	LCDclr();
	while(1){
		ok=KEYPAD_Scan(&car);
		if(ok==1){
			LCDsendChar(car);
		}
		//_delay_ms(100);
	}
	return 0;
}


