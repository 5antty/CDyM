/*
 * Tp2.c
 *
 * Created: 5/4/2025 4:31:05 PM
 * Author : santi
 */ 

#include <avr/io.h>
#include "main.h"

//Estados MEF
typedef enum{S0,S1,S2, S3}state;
state estado;
void inicio(void);
void escribiendo(void);
void (*MEF[])(void)={inicio,escribiendo};

int X;
void Iniciar_MEF(){
	estado=S0; X=0;
}

void ActualizarMEF(void) {
	//X=leerEntradas();
	(*MEF[estado])();
	switch(estado){
		case S0:
			if(X==1){
				estado=S1;
			}
			break;
		case S1:
			if(X==1)
				estado=S3;
			break;
		case S2:
			estado=S0;
			break;
		case S3:
			estado=S0;
			break;
		
	}
}
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
}

void escribiendo(void){
	int cant=0;
	static int errores=0;
	static int pulsadas=0;
	uint8_t teclas[3];
	char car;
	while(cant<3)
	{
		if(KEYPAD_Scan(&teclas[cant])==1)
			cant++;
	}
	if(teclas[2]==64){
		car=teclas[0]*10+teclas[1];
		if(car!=contra[pulsadas]){
			errores++;
		}
		else
			LCDGotoXY(0,pulsadas);
			LCDsendChar(car);
		pulsadas++;
	}
}


int main(void)
{
	LCD_Init();
	inicio();
	char* prueba="YA TERMINO EL INICIO";
	LCDstring((uint8_t *)prueba, 21);
    while (1) 
    {
		//inicio(contra);
		//escribiendo();
		/*if (INTERERUPCION)
		{
			ActualizarMEF();
		}
		*/
		
    }
	return 0;
}

