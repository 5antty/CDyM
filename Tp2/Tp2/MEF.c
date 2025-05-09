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

char * contra;
static uint8_t clk;
static uint8_t clkS0;
static uint8_t clkVic;
static uint8_t clkDer;
static state estado;

static int listo;
static int errores;
static int correctas;

void IniciarMEF(void){
	clk=0;
	clkS0=0;
	clkVic=0;
	clkDer=0;
	
	estado=ini;
	errores=0;
	correctas=0;
	listo=0;
	
	cargaRegsTimer();
}

int inicio(void){
	uint8_t car=0;
	srand(clk);
	errores=0;
	clkDer=0;
	correctas=0;
	clkVic=0;
	if((KEYPAD_Scan(&car)==1)&&(car==42)){
		contra=getContra();
		LCDstring((uint8_t *)contra, 5);
		clkS0=0;
		return 1;
	}
	return 0;
}

int caracter(uint8_t * car){
	if((KEYPAD_Scan(car))==1){
		if((*car>=48)&&(*car<=57)){
			LCDsendChar(*car);
			return 1;
		}
	}
	return 0;
}

void compCAR(char num1,  char num2, char num3){
	char car;
	car=(num1-48)*100+(num2-48)*10+num3-48;
	if(car==contra[correctas]){
		LCDGotoXY(correctas,0);
		LCDsendChar(car);
		correctas++;
	}
	else{
		errores++;
	}
	//borrar linea inf
	LCDGotoXY(0,1);
	LCDstring((uint8_t *)"                ", 16);
}

void derrota(void){
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t *)"DERROTA", 7);
}

void victoria(void){
	char * msj="";
	int min=0, seg=10*clk;
	LCDclr();
	LCDGotoXY(0,0);
	if(seg>60){
		min=seg/60;
		seg=seg%60;
	}
	sprintf(msj, "VICTORIA %d:%d", min, seg);
	LCDstring((uint8_t *)msj, 14);
}

void ActualizarMEF(void) {
	static uint8_t num1;
	static uint8_t num2;
	static uint8_t num3;
	static uint8_t finCAR;
	switch(estado){
		case ini:
			if(inicio()){
				listo=1;
			}
			if((listo)&&(++clkS0==20)){
				LCDclr();
				estado=number1;
				clkS0=0;
			}
			clk++;
		break;
		
		case number1:
			listo=0;
			LCDGotoXY(0, 1);
			//caracter(&num1); Devuelve si se pulso un caracter numerico
			if(caracter(&num1)){
				estado=number2;
			}
			clk++;
		break;
		case number2:
			//caracter(&num2); Devuelve si se pulso un caracter numerico
			if(caracter(&num2)){
				estado=number3;
			}
			clk++;
		break;
		case number3:
			//caracter(&num3); Devuelve si se pulso un caracter numerico
			if(caracter(&num3)){
				estado=numeral;
			}
			clk++;
		break;
		
		case numeral:
			if((KEYPAD_Scan(&finCAR)==1)&&(finCAR==64)){
				compCAR(num1, num2, num3);
				if(correctas>4){
					estado=vic;
				}
				else if(errores>2){
					estado=der;
				}
				else
				{
					estado=number1;
				}
			}
			listo=0;
			clk++;
		break;
		case der:
			if(!listo){
				listo=1;
				derrota();
			}
			if((listo)&&(++clkDer==30)){
				LCDclr();
				estado=ini;
				listo=0;
			}
			clk++;
		break;
		
		case vic:
			if(!listo){
				listo=1;
				victoria();
			}
			if((listo)&&(++clkVic==50)){
				LCDclr();
				estado=ini;
				listo=0;
				clk=0;
			}
			else
				clk++;
		break;
		
	}
}