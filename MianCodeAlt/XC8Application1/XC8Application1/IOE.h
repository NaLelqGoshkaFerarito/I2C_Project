#ifndef IOE_H_
#define IOE_H_

//device address and ID (determined by A0:2)
#define IOE16_ADDR (0x20)
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x01
//IO pins
#define GPIO0 0x12
#define GPIO1 0x13

#define LIB 0


#if LIB
#include "../../../lib/i2c/i2c.h"
//#include "../../../lib/i2c/i2c.c"

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
#else

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#define MAX_TRIES 50
#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0
#define DATASIZE 32


/* START I2C Routine */
unsigned char i2c_transmit(unsigned char type) {
	switch(type) {
		case I2C_START:    // Send Start Condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		break;
		case I2C_DATA:     // Send Data with No-Acknowledge
		TWCR = (1 << TWINT) | (1 << TWEN);
		break;
		case I2C_DATA_ACK: // Send Data with Acknowledge
		TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
		break;
		case I2C_STOP:     // Send Stop Condition
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
		return 0;
	}
	// Wait for TWINT flag set on Register TWCR
	while (!(TWCR & (1 << TWINT)));
	// Return TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
	return (TWSR & 0xF8);
}
char i2c_start(unsigned int dev_id, unsigned int dev_addr, unsigned char rw_type)
{
	unsigned char n = 0;
	unsigned char twi_status;
	char r_val = -1;
	i2c_retry:
	if (n++ >= MAX_TRIES) return r_val;
	// Transmit Start Condition
	twi_status=i2c_transmit(I2C_START);

	// Check the TWI Status
	if (twi_status == TW_MT_ARB_LOST) goto i2c_retry;
	if ((twi_status != TW_START) && (twi_status != TW_REP_START)) goto i2c_quit;
	// Send slave address (SLA_W)
	TWDR = (dev_id & 0xF0) | (dev_addr & 0x0E) | rw_type;
	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_DATA);
	// Check the TWSR status
	if ((twi_status == TW_MT_SLA_NACK) || (twi_status == TW_MT_ARB_LOST)) goto i2c_retry;
	if (twi_status != TW_MT_SLA_ACK) goto i2c_quit;
	r_val=0;
	i2c_quit:
	return r_val;
}
void i2c_stop(void)
{
	unsigned char twi_status;
	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_STOP);
}
char i2c_write(char data)
{
	unsigned char twi_status;
	char r_val = -1;
	// Send the Data to I2C Bus
	TWDR = data;
	// Transmit I2C Data
	twi_status=i2c_transmit(I2C_DATA);
	// Check the TWSR status
	if (twi_status != TW_MT_DATA_ACK) goto i2c_quit;
	r_val=0;
	i2c_quit:
	return r_val;
}
char i2c_read(char *data,char ack_type)
{
	unsigned char twi_status;
	char r_val = -1;

	if (ack_type) {
		// Read I2C Data and Send Acknowledge
		twi_status=i2c_transmit(I2C_DATA_ACK);
		if (twi_status != TW_MR_DATA_ACK) goto i2c_quit;
		} else {
		// Read I2C Data and Send No Acknowledge
		twi_status=i2c_transmit(I2C_DATA);
		if (twi_status != TW_MR_DATA_NACK) goto i2c_quit;
	}
	// Get the Data
	*data=TWDR;
	r_val=0;
	i2c_quit:
	return r_val;
}


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
#endif //LIB

#endif /* IOE_H_ */