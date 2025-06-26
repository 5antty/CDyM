/*
 * UART_LIB.c
 *
 * Created: 6/8/2025 12:35:50 AM
 *  Author: santi
 */ 
#include "UART_LIB.h"
#include <avr/interrupt.h>
extern volatile uint8_t FlagNewLine;
extern volatile uint8_t FlagOcupado;

void uart_init(){
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);//tamanio del caracter
	UBRR0L = 103; //baud rate = 9600bps
}
void uart_TXEnable(){
	UCSR0B |= (1 << TXEN0);
}
void uart_RXEnable(){
	UCSR0B |= (1 << RXEN0);
}
void uart_RXEnI(void)
{
	UCSR0B |= (1 << RXCIE0);
}

void uart_sendString(char *str)
{
	strncpy((char *)BufferTX, str, TamBuffers-1);
	UDR0=BufferTX[0];
	UCSR0B |= (1 << TXCIE0);
}

ISR(USART_TX_vect)
{
	static uint8_t TXindex_lec=1;
	UDR0=BufferTX[TXindex_lec++];
	if(BufferTX[TXindex_lec]=='\0'){
		TXindex_lec=1;
		UCSR0B &=~(1<<TXCIE0);
	}
}

ISR(USART_RX_vect)
{
	volatile uint8_t rx_data;
	static uint8_t RXindex=0;
	rx_data=UDR0;
	if(rx_data != '\r'){
		BufferRX[RXindex++]=rx_data;
	}
	else{
		BufferRX[RXindex]='\0';
		RXindex=0;
		FlagNewLine=1;
	}
}

