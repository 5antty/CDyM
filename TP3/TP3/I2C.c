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

void getTime(){
	unsigned char aux, seg_10, seg, min, min_10, hr_10, hr;
	unsigned char dia_10, dia, mes_10, mes, anio_10, anio;
	char * fecha;
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_stop();
	//leo byte 00h donde estan los segs
	aux=i2c_read(0);
	seg_10=(aux<<6)|(aux<<5)|(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	seg=seg_10*10+aux;
	//Lectura de mins 01h
	aux=i2c_read(0);
	min_10=(aux<<6)|(aux<<5)|(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	min=min_10*10+aux;
	//Lectura de hora 02h
	aux=i2c_read(0);
	hr_10=(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	hr=hr_10*10+aux;
	//Lectura dia de semana 03h
	aux=i2c_read(0);
	//Lectura dia del mes 04h
	aux=i2c_read(0);
	dia_10=(aux<<5)|(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	dia=dia_10*10+aux;
	//Lectura del mes 05h
	aux=i2c_read(0);
	mes_10=(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	mes=mes_10*10+aux;
	//Lectura del anio 06h
	aux=i2c_read(1);
	anio_10=(aux<<7)|(aux<<6)|(aux<<5)|(aux<<4);
	aux=(aux<<3)|(aux<<2)|(aux<<1)|(aux<<0);
	mes=mes_10*10+aux;
	
	//Capaz conviene hacer un struct para tener toda esta info y devolverla en la funcion
}