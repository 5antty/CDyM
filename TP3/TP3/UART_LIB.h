/*
 * UART_LIB.h
 *
 * Created: 6/8/2025 12:36:06 AM
 *  Author: santi
 */ 


#ifndef UART_LIB_H_
#define UART_LIB_H_
#include <avr/io.h>

void uart_sendCar(unsigned char dato);
unsigned char uart_receiveCar(void);
void uart_sendString(char* cadena);

#endif /* UART_LIB_H_ */