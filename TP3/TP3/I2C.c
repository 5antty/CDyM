/*
 * I2C.c
 *
 * Created: 02/06/2025 14:53:39
 *  Author: santi
 */ 
#include "I2C.h"
#include "UART_LIB.h"

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

void i2c_write(uint8_t data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
}

uint8_t i2c_read(uint8_t isLast){
	if(isLast==0)
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

uint8_t BCDtoInt(uint8_t value)
{
	return ((value >> 4) * 10) + (value & 0x0F);
}

uint8_t InttoBCD(uint8_t value)
{
	return ((value / 10) << 4) | (value % 10);
}

fecha i2c_getTime(){
	fecha f;
	uint8_t aux;
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_stop();
	
	i2c_start();
	i2c_write(0b11010001);
	
	//leo byte 00h donde estan los segs
	aux=i2c_read(0);
	f.segs=BCDtoInt(aux);
	
	//Lectura de mins 01h
	aux=i2c_read(0);
	f.min=BCDtoInt(aux);
	
	//Lectura de hora 02h
	aux=i2c_read(0);
	f.hr=BCDtoInt(aux);
	
	//Lectura dia de semana 03h
	aux=i2c_read(0);
	
	//Lectura dia del mes 04h
	aux=i2c_read(0);
	f.dia=BCDtoInt(aux);
	
	//Falta poder ver esto en la estructura fecha
	
	//Lectura del mes 05h
	aux=i2c_read(0);
	f.mes=BCDtoInt(aux);
	
	//Lectura del anio 06h
	aux=i2c_read(1);
	f.anio=BCDtoInt(aux);
	
	i2c_stop();
	return f;
	//Capaz conviene hacer un struct para tener toda esta info y devolverla en la funcion
}

void i2c_setTime(fecha f){
	unsigned char aux, aux2;
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	
	aux=f.segs%10;//unidades
	aux2=(f.segs*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	
	aux=f.min%10;
	aux2=(f.min*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	
	aux=f.hr%10;
	aux2=(f.hr*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	i2c_write(0x00);
	
	aux=f.dia%10;
	aux2=(f.dia*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	
	aux=f.mes%10;
	aux2=(f.mes*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	
	aux=f.anio%10;
	aux2=(f.anio*0.1);//decenas
	i2c_write((aux2<<4)|aux);
	
	i2c_stop();
}