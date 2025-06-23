/*
 * UART_LIB.c
 *
 * Created: 6/8/2025 12:35:50 AM
 *  Author: santi
 */ 
#include "UART_LIB.h"
extern volatile uint8_t FlagNewLine;

void uart_init(){
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);//tamanio del caracter
	UBRR0L = 103; //baud rate = 9600bps
}
void uart_TXEnable(){
	UCSR0B = (1<<TXEN0);
}
void uart_RXEnable(){
	UCSR0B = (1<<RXEN0);
}
void uart_RXEnI(void)
{
	UCSR0B |= (1 << RXCIE0);
}
void uart_sendCar(uint8_t dato){
	while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
	UDR0 = dato; //transmite dato
}

uint8_t uart_receiveCar(void){
	unsigned char dato;
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

ISR(USART_RX_vect){
	volatile uint8_t rx_data;
	static uint8_t index=0;
	rx_data=UDR0;
	if(rx_data!='\r'){
		BufferRX[index++]=rx_data;
	}
	else{
		BufferRX[index]='\0';
		index=0;
		FlagNewLine=1;
	}
}
