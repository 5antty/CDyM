/*
 * I2C.h
 *
 * Created: 02/06/2025 14:53:14
 *  Author: santi
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char isLast);
void i2c_stop(void);

#endif /* I2C_H_ */