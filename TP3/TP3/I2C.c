/*
 * I2C.c
 *
 * Created: 02/06/2025 14:53:39
 *  Author: santi
 */ 
#include "I2C.h"

void i2c_init(void){
	TWSR=0x00;//Prescaler de bits en 0
	TWBR=72;//Frecuencia de SCL a 100khz
	//TWPS=0;
	TWCR=0x04;//Activo el modulo TWI
}

void i2c_start(void){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
}

void i2c_write(unsigned char data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
}

unsigned char i2c_read(unsigned char isLast){
	if(~isLast)
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//Envio de ACK
	else
		TWCR=(1<<TWINT)|(1<<TWEN);//Envio de NACK
	while((TWCR & (1<<TWINT))==0);
	return TWDR;
}

void i2c_stop(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	//No usar el flag de twint luego de enviar STOP
}