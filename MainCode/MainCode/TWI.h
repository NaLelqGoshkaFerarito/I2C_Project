/*
 * TWI.h
 *
 * Created: 6 Apr 2023 09:23:11
 *  Author: vladi
 */ 


#ifndef TWI_H_
#define TWI_H_

#define F_CPU 16000000L
#define TWI_SPEED 100000


#define TWI_START 0x08
#define TWI_RESTRT 0x10
#define TWI_ERR 0x38
#define TWI_NONE 0xF8
 
#define TWI_T_ADDR_ACK 0x18
#define TWI_T_ADDR_NACK 0x20
#define TWI_T_DATA_ACK 0x28
#define TWI_T_DATA_NACK 0x30

#define TWI_R_ADDR_ACK 0x40
#define TWI_R_ADDR_NACK 0x48
#define TWI_R_DATA_ACK 0x50
#define TWI_R_DATA_NACK 0x58

enum{
	TWI_OK,
	TWI_ERR_START,
	TWI_ERR_RESTRT,
	TWI_NACK
	};

#define TWI_TIMEOUT 1600

volatile uint8_t status = TWI_NONE;

void twi_init(){
	//set bitrate register
	TWBR = (((F_CPU/TWI_SPEED) - 16)/2) & 0xFF;
	//enable TWI and interrupts
	TWCR = (1<<TWEN) | (1<<TWIE);
}

static uint8_t twi_start(){
	uint16_t timer = 0;
	//start
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
	//wait until the status register registers it
	while(status != TWI_START){
		++timer;
		//cancel if start times out
		if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
	}
	return TWI_OK;
}

static void twi_stop(){
	//stop
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) | (1<<TWIE);
}

static uint8_t twi_restart(){
	uint16_t timer = 0;
	//start
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
	//wait for ack
	while(status != TWI_RESTRT){
		++timer;
		//cancel if it times out
		if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
	}
	return TWI_OK;
}

static uint8_t twi_t_addr_ack(){
	uint16_t timer = 0;
	//start
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	//wait for ack
	while(status != TWI_T_ADDR_ACK){
		++timer;
		//cancel if it times out
		if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
	}
	return TWI_OK;
}

static uint8_t twi_t_data_ack(){
	uint16_t timer = 0;
	//start
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	//wait for ack
	while(status != TWI_T_DATA_ACK){
		++timer;
		//cancel if it times out
		if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
	}
	return TWI_OK;
}

static uint8_t twi_r_addr_ack(){
	uint16_t timer = 0;
	//start
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	//wait for ack
	while(status != TWI_R_ADDR_ACK){
		++timer;
		//cancel if it times out
		if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
	}
	return TWI_OK;
}

static uint8_t twi_r_data_ack(uint8_t ack){
	uint16_t timer = 0;
	//if nack
	if (ack != 0){
		//start
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
		//wait for ack
		while(status != TWI_R_DATA_ACK){
			++timer;
			//cancel if start times out
			if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
		}
		return TWI_OK;
	}
	else{
		//start
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
		//wait for nack
		while(status != TWI_R_DATA_NACK){
			++timer;
			//cancel if it times out
			if(timer >= TWI_TIMEOUT) return TWI_ERR_START;
		}
		return TWI_OK;
	}
}

uint8_t twi_read(uint8_t addr, uint8_t reg, uint8_t* data, uint16_t len){
	uint8_t err = TWI_OK;
	
	//begin
	err = twi_start();
	if(err != TWI_OK){
		twi_stop();
		return TWI_OK;
	}
	
	TWDR = (addr << 1) | 0;
	
	err = twi_t_addr_ack();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	TWDR = reg;
	
	err = twi_t_addr_ack();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	err = twi_restart();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	TWDR = (addr << 1) | 1;
	
	err = twi_r_addr_ack();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	
	//read
	uint16_t counter = 0;
	for (counter = 0; counter < len - 1; ++counter)
	{
		err = twi_r_data_ack(1);
		if (err != TWI_OK){
			twi_stop;
			return err;
		}
		data[counter] = TWDR;
	}
	
	//end
	err = twi_r_data_ack(0);
	if (err != TWI_OK){
		twi_stop;
		return err;
	}
	data[counter] = TWDR;
	
	twi_stop();
	return err;
}

uint8_t twi_write(uint8_t addr, uint8_t reg, uint8_t* data, uint16_t len){
	uint8_t err = TWI_OK;
	
	//begin
	err = twi_start();
	if(err != TWI_OK){
		twi_stop();
		return TWI_OK;
	}
	
	TWDR = (addr << 1) | 0;
	
	err = twi_t_addr_ack();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	TWDR = reg;
	
	err = twi_t_addr_ack();
	if(err != TWI_OK){
		twi_stop();
		return err;
	}
	
	uint16_t counter = 0;
	for (counter = 0; counter < len; ++counter)
	{
		TWDR = data[counter];
		err = twi_t_data_ack(1);
		if (err != TWI_OK){
			twi_stop;
			return err;
		}
	}
	
	//end
	twi_stop();
	return err;
}

ISR(TWI_vect){
	//get current status from status register
	status = (TWSR & TWI_NONE);
}

#endif /* TWI_H_ */