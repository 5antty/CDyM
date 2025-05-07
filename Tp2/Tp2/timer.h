/*
 * timer.h
 *
 * Created: 07/05/2025 15:11:58
 *  Author: santi
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <avr/interrupt.h>

extern volatile uint8_t MEF_flag;

void cargaRegsTimer(void);


#endif /* TIMER_H_ */