/*
 * UART_LIB.c
 *
 * Created: 6/8/2025 12:35:50 AM
 *  Author: santi
 */ 
#include "UART_LIB.h"
extern volatile uint8_t FlagNewLine;
char BufferTX[TamBuffers];

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
void uart_RXIEnable(void)
{
	UCSR0B |= (1 << RXCIE0);
}

void uart_sendString(char *str)
{
	strncpy((char *)BufferTX, str, TamBuffers-1);
	UCSR0B |= (1 << UDRIE0);
}

ISR(USART_UDRE_vect)
{
	static uint8_t TXindex_lec=0;
	UDR0=BufferTX[TXindex_lec];
	TXindex_lec++;
	if(BufferTX[TXindex_lec]=='\0'){
		TXindex_lec=0;
		UCSR0B &=~(1<<UDRIE0);
	}
}

ISR(USART_RX_vect)
{
	volatile uint8_t RXData;
	static uint8_t RXindex=0;
	RXData=UDR0;
	if((RXData != '\r') && (RXData != '\n')){
		BufferRX[RXindex++]=RXData;
	}
	else if(RXData == '\r'){
		BufferRX[RXindex]='\0';
		RXindex=0;
		FlagNewLine=1;
	}
}

