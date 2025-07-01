/*
 * TP3.c
 *
 * Created: 02/06/2025 15:21:40
 * Author : santi
 */ 
#include "main.h"
//Flags de interrupciones
volatile uint8_t timer1Flag=0;
volatile uint8_t FlagNewLine=0;
//Flags para la arquitectura Background-foreground
uint8_t FlagON=0;
uint8_t FlagAlarma=0;
//Refistro para fecha actual
fecha act;
//Registro para alarma y contador de la misma
fecha alarma;
uint8_t contAlarm=0;

void initAll(){
	i2c_init();
	timer1_Init();
	uart_init();
	uart_TXEnable();
	uart_sendString("Ingrese la opcion a realizar\r\nON\r\nOFF\r\nSET TIME\r\nSET ALARM\r\n");
	uart_RXEnable();
	uart_RXIEnable();
	sei();
}
void fechaUART(){
	char ok[TXLong];
	uart_TXEnable();
	sprintf(ok, "FECHA: %u/%u/%u HORA: %u:%u:%u\r\n", act.dia, act.mes, act.anio, act.hr, act.min, act.segs);
	uart_sendString(ok);
}

void modoSetTime(void){
	fecha f;
	int i;
	for (i=0;i<6;i++){
		while(!FlagNewLine){
			//Guardar cada caracter de la cadena
		}
		FlagNewLine=0;
		switch(i){
			case 0:
				f.dia=atoi(BufferRX);
			break;
			case 1:
				f.mes=atoi(BufferRX);
			break;
			case 2:
				f.anio=atoi(BufferRX)%100;
			break;
			case 3:
				f.hr=atoi(BufferRX);
			break;
			case 4:
				f.min=atoi(BufferRX);
			break;
			case 5:
				f.segs=atoi(BufferRX);
			break;
		}
	}
	i2c_setTime(f);
}
void modoAlarma(){
	int i;
	for (i=0;i<3;i++){
		while(!FlagNewLine){
			//Guardar cada caracter de la cadena
		}
		FlagNewLine=0;
		switch(i){
			case 0:
				alarma.hr=atoi(BufferRX);
				break;
			case 1:
				alarma.min=atoi(BufferRX);
				break;
			case 2:
				alarma.segs=atoi(BufferRX);
				break;
		}
	}
}

void gestion(){
	if((strcmp(BufferRX, "on")==0)||(strcmp(BufferRX, "ON")==0)){
		uart_sendString("Reloj encendido\r\n");
		FlagON=1;
	}
	else if((strcmp(BufferRX, "off")==0)||(strcmp(BufferRX, "OFF")==0)){
		FlagON=0;
		uart_sendString("Reloj apagado\r\n");
	}
	else if((strcmp(BufferRX, "set time")==0)||(strcmp(BufferRX, "SET TIME")==0)){
		uart_sendString("Ingrese\r\ndia\r\nmes\r\nanio\r\nhora\r\nminuto\r\nsegundo\r\n");
		modoSetTime();
	}
	else if((strcmp(BufferRX, "set alarm")==0)||(strcmp(BufferRX, "SET ALARM")==0)){
		uart_sendString("Ingrese\r\nhora\r\nminuto\r\nsegundo\r\n");
		modoAlarma();
	}
	else
		uart_sendString("Error de comando\r\n");
}

int compAlarma(){
	return ((act.hr==alarma.hr) && (act.min==alarma.min) && (act.segs==alarma.segs));
}

void alarmT(){
	uart_sendString("ALARMA\r\n");
	if(++contAlarm>4){
		FlagAlarma=0;
		contAlarm=0;
	}
}

int main(void)
{
	initAll();
	while(1){
		if(FlagNewLine){
			FlagNewLine=0;
			gestion();
		}
		if(timer1Flag){
			timer1Flag=0;
			act=i2c_getTime();
			if(FlagAlarma)
				alarmT();
			else if(FlagON)
				fechaUART();//Tarea en background productora
			if(!FlagAlarma && compAlarma()){
				FlagAlarma=1;
			}
		}
		
	}
}

