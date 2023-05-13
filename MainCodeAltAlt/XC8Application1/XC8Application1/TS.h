/*
 * TS.h
 *
 * Created: 12 May 2023 11:58:03
 *  Author: vladi
 */ 


#ifndef TS_H_
#define TS_H_
#include "I2C.h"

#define TS_ADDR 0b1001000
#define TS_TEMP_REG 0x00
#define TS_CONFIG_REG 0x01

void TSInitRead(){
	i2c_start(TS_ADDR, 0x00, TW_WRITE);
	i2c_write(TS_TEMP_REG);
	i2c_write(0x00);
	i2c_stop();
}

uint16_t TSReadTemp16(){
	TSInitRead();
	i2c_start(TS_ADDR, 0x00, TW_READ);
	uint8_t msb;
	uint8_t lsb;
	i2c_read(&msb, ACK);
	i2c_read(&lsb, NACK);
	i2c_stop();
	uint16_t response = msb << 8;
	response |= lsb;
	return response;
}

uint8_t TSReadTemp8(){
	TSInitRead();
	i2c_start(TS_ADDR, 0x00, TW_READ);
	uint8_t msb;
	uint8_t lsb;
	i2c_read(&msb, ACK);
	i2c_read(&lsb, NACK);
	i2c_stop();
	return msb;
}



#endif /* TS_H_ */