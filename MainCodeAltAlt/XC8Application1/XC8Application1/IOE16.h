/*
 * IOE16.h
 *
 * Created: 12 May 2023 12:50:06
 *  Author: vladi
 */ 


#ifndef IOE16_H_
#define IOE16_H_

//device address and ID (determined by A0:2)
#define IOE16_ADDR 0x20 << 1
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x01
//IO pins
#define GPIO0 0x12
#define GPIO1 0x13


void IOEInit(){
	i2c_start(IOE16_ADDR, IOE16_ID, TW_WRITE);
	i2c_write(IODIR0);
	i2c_write(0x00);
	i2c_stop();

	i2c_start(IOE16_ADDR, IOE16_ID, TW_WRITE);
	i2c_write(IODIR1);
	i2c_write(0x00);
	i2c_stop();
}

void IOEWrite(uint16_t data){
	uint8_t msb = (data >> 8) & 0xFF;
	uint8_t lsb = data & 0xFF;
	i2c_start(IOE16_ADDR, IOE16_ID, TW_WRITE);
	i2c_write(GPIO0);
	i2c_write(lsb);
	i2c_stop();

	i2c_start(IOE16_ADDR, IOE16_ID, TW_WRITE);
	i2c_write(GPIO1);
	i2c_write(msb);
	i2c_stop();
}


#endif /* IOE16_H_ */