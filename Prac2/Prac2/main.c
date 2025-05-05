/*
 * Prac2.c
 *
 * Created: 02/05/2025 15:04:36
 * Author : santi
 */ 

#include "main.h"

int main (void){
	uint8_t car=0;
	LCDinit();
	LCDGotoXY(0,0);
	LCDstring((uint8_t *)"FUNCIONO", 8);
	_delay_ms(1000);
	LCDclr();
	while(1){
		if(KEYPAD_Scan(&car)==1){
			/*LCDGotoXY(0,0);
			LCDescribeDato(car, 3);
			LCDGotoXY(0, 1);
			LCDprogressBar(car, 15, 16);*/
			LCDsendChar(car);
			//LCDescribeDato(car, 1);
		}
		_delay_ms(100);
	}
	return 0;
}


