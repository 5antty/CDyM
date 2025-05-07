/*
 * MEF.c
 *
 * Created: 5/6/2025 5:38:31 PM
 *  Author: santi
 */ 
#include "MEF.h"
//Estados MEF

/*
S0 = INICIO
S1 = ESCRIBIENDO
S2 = GANASTE
S3 = PERDISTE
*/
	
int ENTRADA=0;
char * contra;
void inicio(void){
	srand(TCNT0);
	uint8_t car=0;
	int ingreso=1;
	contra=getContra();
	while(ingreso){
		if((KEYPAD_Scan(&car)==1)&&(car==42)){
			LCDstring((uint8_t *)contra, 5);
			_delay_ms(2000);
			LCDclr();
			ingreso=0;
		}
	}
	ENTRADA=0;
}

void escribiendo(void){
	int cant=0;
	static int errores=0;
	static int pulsadas=0;
	uint8_t teclas[4];
	char car;
	if(errores>2){
		ENTRADA=1;
		return;
	}
	if(pulsadas==5){
		ENTRADA=2;
		return;
	}
	LCDGotoXY(0,1);
	while(cant<4)
	{
		if(KEYPAD_Scan(&(teclas[cant]))==1){
			LCDsendChar(teclas[cant]);
			cant++;
		}
	}
	if(teclas[3]==64){
		car=(teclas[0]-48)*100+(teclas[1]-48)*10+teclas[2]-48;
		if(car==contra[pulsadas]){
			LCDGotoXY(pulsadas,0);
			LCDsendChar(car);
			pulsadas++;
		}
		else{
			errores++;
		}
		//borrar linea inf
		LCDGotoXY(0,1);
		LCDstring((uint8_t *)"                ", 16);
	}
}

void derrota(void){
	LCDclr();
	LCDstring((uint8_t *)"DERROTA", 7);
	_delay_ms(3000);
}

void victoria(void){
	LCDclr();
	LCDstring((uint8_t *)"DERROTA", 7);
	_delay_ms(3000);
}

void (*Funciones[])(void)={inicio,escribiendo};

void ActualizarMEF(state* estado) {
	(*Funciones[*estado])();
	switch(*estado){
		case S0:
			*estado=S1;
		break;
		case S1:
		if(ENTRADA==1){
			*estado=S3;
		}
		else if(ENTRADA==2){
			*estado=S2;
		}
		break;
		case S2:
			*estado=S0;
		break;
		case S3:
			*estado=S0;
		break;
		
	}
}