/*
 * PWM.h
 *
 * Created: 07/07/2025 14:35:48
 *  Author: González Villagra, Santiago
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "main.h"

void PWM_T1();
void PWM_soft(uint8_t);
void PWM_T1_update(uint8_t, uint8_t);
void PWM_init();


#endif /* PWM_H_ */