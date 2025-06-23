/*
 * UART_LIB.h
 *
 * Created: 6/8/2025 12:36:06 AM
 *  Author: santi
 */ 


#ifndef UART_LIB_H_
#define UART_LIB_H_
#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init();
void uart_TXEnable();
void uart_RXEnable();
void uart_RXEnI(void);
void uart_sendCar(uint8_t dato);
uint8_t uart_receiveCar(void);
void uart_sendString(char* cadena);


#endif /* UART_LIB_H_ */