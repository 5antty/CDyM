/*
 * main.h
 *
 * Created: 02/06/2025 15:22:56
 *  Author: santi
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "UART_LIB.h"
#include "I2C.h"
#include "timer1.h"

#define  TamBuffers 128
#define TXLong 34
char BufferRX[TamBuffers];


#endif /* MAIN_H_ */