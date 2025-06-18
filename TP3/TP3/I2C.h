/*
 * I2C.h
 *
 * Created: 02/06/2025 14:53:14
 *  Author: santi
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

typedef struct{
	uint8_t segs;
	uint8_t min;
	uint8_t hr;
	uint8_t dia;
	uint8_t mes;
	uint8_t anio;
}fecha;

void i2c_init(void);
void i2c_start(void);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t isLast);
void i2c_stop(void);
fecha i2c_getTime(void);
void i2c_setTime(fecha f);

#endif /* I2C_H_ */