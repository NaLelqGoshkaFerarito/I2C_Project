/*
 * TS.h
 *
 * Created: 1 May 2023 16:27:55
 *  Author: vladi
 */ 


#ifndef TS_H_
#define TS_H_

//set with AO:2 = GND
#define TS_ADDR 0b1001000
#define TS_TEMP_REG 0x00
#define TS_CONFIG_REG 0x01

//select temperature register
void TSInitRead(){
		i2c_tx_start(MASTER_TRANSMITTER);
		i2c_tx_address(TS_ADDR);
		i2c_tx_byte(TS_TEMP_REG);
		i2c_tx_byte(0x00);
		i2c_tx_stop();
}

uint16_t TSReadTemp16(){
	TSInitRead();
	i2c_tx_start(MASTER_RECEIVER);
	i2c_tx_address(TS_ADDR);
	uint8_t msb = i2c_rx_byte(ACK);
	uint8_t lsb = i2c_rx_byte(ACK);
	i2c_tx_stop();
	uint16_t response = msb << 8;
	response |= lsb;
	return response;
}

uint8_t TSReadTemp8(){
	TSInitRead();
	i2c_tx_start(MASTER_RECEIVER);
	i2c_tx_address(TS_ADDR);
	uint8_t msb = i2c_rx_byte(ACK);
	uint8_t lsb = i2c_rx_byte(ACK);
	i2c_tx_stop();
	return msb;
}


#endif /* TS_H_ */