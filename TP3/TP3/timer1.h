/*
 * timer1.h
 *
 * Created: 6/11/2025 10:36:21 PM
 *  Author: santi
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
#include <avr/io.h>
#include <avr/interrupt.h>
extern volatile uint8_t timer1Flag;
void timer1_Init();

#endif /* TIMER1_H_ */