/*
 * IOExp.h
 *
 * Created: 11 Apr 2023 13:07:21
 *  Author: vladi
 */ 


#ifndef IOEXP_H_
#define IOEXP_H_


//set to 1 if the TWI code is used
#define TWI 0
//set to 1 if the I2C code is used
#define I2C !TWI
//device address and ID (determined by A0:2)
#define IOE16_ADDR 0x20
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x10
//IO pins
#define GPIO0 0x09
#define GPIO1 0x19


#if TWI
#include "TWI.h"


//initialize for writing
uint8_t IOInit_TWI(){
	twi_init();
	uint8_t state = twi_write(IOE16_ADDR, IODIR0, 0x00, sizeof(0x00));
	return state;
}

uint8_t IOEWrite8_TWI(uint8_t data){
	uint8_t state = twi_write(IOE16_ADDR, GPIO0, data, sizeof(data));
	return state;
}
#endif //TWI

#if I2C
#include "I2C.h"

uint8_t IOInit_I2C(){
	i2c_init();
	i2c_start(IOE16_ID,IOE16_ADDR,TW_WRITE);
	if (i2c_write(IODIR0) != 0) return 1;
	if (i2c_write(0x00) != 0) return 1;
	if (i2c_write(IODIR1) != 0) return 1;
	if (i2c_write(0x00) != 0) return 1;
	return 0;
}

uint8_t IOEWrite8_I2C(uint8_t addr, uint8_t data){
	i2c_start(IOE16_ID,IOE16_ADDR,TW_WRITE);
	if (i2c_write(addr) != 0) return 1;
	if (i2c_write(data) != 0) return 1;
	i2c_stop();
	return 0;
}

uint8_t IOEWrite16_I2C(uint8_t addr1, uint8_t addr2, uint8_t data1, uint8_t data2){
	if (IOEWrite8_I2C(addr1, data1) != 0) return 1;
	if (IOEWrite8_I2C(addr2, data2) != 0) return 1;
	return 0;
}

#endif //I2C




#endif /* IOEXP_H_ */