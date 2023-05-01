/*
 * IOE.h
 *
 * Created: 28 Apr 2023 12:50:24
 *  Author: vladi
 */ 


#ifndef IOE_H_
#define IOE_H_

#include "../../../lib/i2c/i2c.h"
//device address and ID (determined by A0:2)
#define IOE16_ADDR (0x23 << 1)
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x01
//IO pins
#define GPIO0 0x12
#define GPIO1 0x13

//initialize for writing
void IOEInit(){
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IOE16_ADDR);
	i2c_tx_byte(IODIR0);
	i2c_tx_byte(0x00);
	i2c_tx_stop();
	
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IOE16_ADDR);
	i2c_tx_byte(IODIR1);
	i2c_tx_byte(0x00);
	i2c_tx_stop();
}

void IOEWrite(uint16_t data){
	uint8_t msb = (data >> 8) & 0xFF;
	uint8_t lsb = data & 0xFF;
	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IOE16_ADDR);
	i2c_tx_byte(GPIO0);
	i2c_tx_byte(lsb);
	i2c_tx_stop();

	i2c_tx_start(MASTER_TRANSMITTER);
	i2c_tx_address(IOE16_ADDR);
	i2c_tx_byte(GPIO1);
	i2c_tx_byte(msb);
	i2c_tx_stop();
}

#endif /* IOE_H_ */