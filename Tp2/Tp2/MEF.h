/*
 * MEF.h
 *
 * Created: 5/6/2025 5:38:42 PM
 *  Author: santi
 */ 


#ifndef MEF_H_
#define MEF_H_

#include "main.h"
typedef enum{S0,S1,S2,S3}state;
void inicio(void);
void escribiendo(void);

void ActualizarMEF(state* estado);


#endif /* MEF_H_ */