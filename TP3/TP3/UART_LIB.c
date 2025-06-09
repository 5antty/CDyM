/*
 * UART_LIB.c
 *
 * Created: 6/8/2025 12:35:50 AM
 *  Author: santi
 */ 
#include "UART_LIB.h"

void uart_sendCar(unsigned char dato){
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = 103; //baud rate = 9600bps
	while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
	UDR0 = dato; //transmit ‘G’ letter
}

unsigned char uart_receiveCar(void){
	unsigned char dato;
	UCSR0B = (1<<RXEN0); //initialize USART0
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = 103;//baud rate = 9600bps
	while (! (UCSR0A & (1<<RXC0))); //wait until new data
	dato = UDR0;
	return dato;
}

void uart_sendString(char* cadena){
	//int tam = sizeof(cadena)/sizeof(cadena[0]);
	int i;
	int tam = 0;
	while(cadena[tam]!='\0'){
		tam++;
	}
	for (i=0;i<tam;i++){
		uart_sendCar(cadena[i]);
	}
}