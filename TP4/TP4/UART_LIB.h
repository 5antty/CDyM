/*
 * UART_LIB.h
 *
 * Created: 6/8/2025 12:36:06 AM
 *  Author: santi
 */ 


#ifndef UART_LIB_H_
#define UART_LIB_H_
#include "main.h"
#include <string.h>
void uart_init();
void uart_TXEnable();
void uart_RXEnable();
void uart_RXIEnable();
void uart_sendString(char *);


#endif /* UART_LIB_H_ */