/*
 * IOExp.h
 *
 * Created: 11 Apr 2023 13:07:21
 *  Author: vladi
 */ 


#ifndef IOEXP_H_
#define IOEXP_H_


//set to 1 if the TWI code is used
#define TWI 1
//set to 1 if the I2C code is used
#define I2C 1
//set to the opposite of I2C due to conflicting names
#define I2C_LIB !I2C
//device address and ID (determined by A0:2)
#define IOE16_ADDR (0x20)
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x01
//IO pins
#define GPIO0 0x12
#define GPIO1 0x13


#if TWI
#include "TWI.h"


//initialize for writing
uint8_t IOInit_TWI(){
	twi_init();
	uint8_t state1 = twi_write(IOE16_ADDR, IODIR0, 0x00, sizeof(0x00));
	uint8_t state2 = twi_write(IOE16_ADDR, IODIR1, 0x00, sizeof(0x00));
	return state1 & state2;
}

uint8_t IOEWrite8_TWI(uint8_t data){
	uint8_t state = twi_write(IOE16_ADDR, GPIO0, data, sizeof(data));
	return state;
}

uint8_t IOEWrite16_TWI(uint16_t data){
	uint8_t msb = (data >> 8) & 0xFF;
	uint8_t lsb = data & 0xFF;
	uint8_t state1 = twi_write(IOE16_ADDR, GPIO0, msb, sizeof(msb));
	uint8_t state2 = twi_write(IOE16_ADDR, GPIO0, msb, sizeof(msb));
	return state1 & state2;
}
#endif //TWI

#if I2C
#include "I2C.h"

uint8_t IOInit_I2C(){
	i2c_init();
	i2c_start(IOE16_ADDR);
	if (i2c_write(IODIR0) != 0) return 1;
	if (i2c_write(0x00) != 0) return 1;
	if (i2c_write(IODIR1) != 0) return 1;
	if (i2c_write(0x00) != 0) return 1;
	return 0;
}

uint8_t IOEWrite8_I2C(uint8_t addr, uint8_t data){
	i2c_start(IOE16_ADDR);
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

void mcp_init(void) {
	// Set IO direction register A as output
	i2c_start(IOE16_ADDR | 0);
	i2c_write(IODIR0);
	i2c_write(0x00);
	i2c_stop();

	// Set IO direction register B as output
	i2c_start(IOE16_ADDR | 0);
	i2c_write(IODIR1);
	i2c_write(0x00);
	i2c_stop();
}

void visualize(uint16_t value) {
	// Divide the value into two bytes so it can be sent to both GPIO ports
	uint8_t high = (value >> 8) & 0xFF;
	uint8_t low = value & 0xFF;

	// Show the high byte to the first 8 leds
	i2c_start(IOE16_ADDR | 0);
	i2c_write(IODIR0);
	i2c_write(high);
	i2c_stop();

	// Show the low byte to the second 8 leds
	i2c_start(IOE16_ADDR | 0);
	i2c_write(IODIR1);
	i2c_write(low);
	i2c_stop();
}


#endif //I2C

#if I2C_LIB
#include "../../lib/i2c/i2c.h"

uint8_t IOInit_I2C(){
	i2c_init();
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IOE16_ADDR);
	i2c_tx_byte(0x00);
	i2c_tx_stop();
	
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IODIR0);
	i2c_tx_byte(0x00);
	i2c_tx_stop();
	
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IODIR1);
	i2c_tx_byte(0x00);
	i2c_tx_stop();
	
}


uint8_t IOEWrite8_I2C(uint8_t addr, uint8_t data){
	i2c_tx_start(MASTER_TRANSMITTER);
	if (i2c_tx_address(addr) != 0) return 1;
	if (i2c_tx_byte(data) != 0) return 1;
	i2c_tx_stop();
	return 0;
}

uint8_t IOEWrite16_I2C(uint8_t addr1, uint8_t addr2, uint8_t data1, uint8_t data2){
	if (IOEWrite8_I2C(addr1, data1) != 0) return 1;
	if (IOEWrite8_I2C(addr2, data2) != 0) return 1;
	return 0;
}

#endif //I2C_LIB



#endif /* IOEXP_H_ */