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

#define	TWI_W			0x00
#define	TWI_R			0x01
#define TWI_ACK			0x01
#define TWI_NACK		0x00

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



#define TWI_TIMEOUT 1600

volatile uint8_t status = TWI_NONE;
 
 void twi_init(){
	TWSR &=~ (1<<TWPS0);
	TWSR &=~ (1<<TWPS1);

	//set bit rate register
	TWBR = (((F_CPU/TWI_SPEED) - 16)/2) & 0xFF;

	//make sure power reduction isn't on
	PRR	 &=~ (1<<PRTWI);

 }

 uint8_t twi_start(){
	 //start condition
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));

	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) == TWI_START)
		return 0;

	return 1;
 }

 uint8_t twi_res(){
	
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));

    while(!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xF8) == TWI_RESTRT)
		return 0;

    return 1;
 }

 void twi_stop(){
	//stop condition 
	TWCR |= ((1<<TWINT) | (1<<TWSTO) | (1<<TWEN));
 }

 uint8_t twi_sendAdrr(uint8_t adrr, uint8_t action){
	uint8_t cmp = 0;
	adrr = (adrr << 1 );

	if (action == TWI_W){
		adrr &=~ 1;
		cmp = TWI_T_ADDR_ACK;
	}
	else{
		adrr |= 1;
		cmp = TWI_R_ADDR_ACK;
	}

	TWDR = adrr;
	TWCR = ((1<<TWINT) | (1<<TWEN));

	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) == cmp)
	return 0;
	
	return 1;
 }
 
  uint8_t twi_data(uint8_t data){
	  int ret = 1;
	  
	  TWDR = data;
	  TWCR = ((1<<TWINT) | (1<<TWEN));
	  while(!(TWCR & (1<<TWINT)));
	  
	  if ((TWSR & 0xF8) == TWI_T_DATA_ACK)
	  ret = false;
	  
	  return ret;
  }

  uint8_t twi_write(uint8_t device, uint8_t address, uint8_t action, uint8_t data){
	  uint8_t ret1 = twi_sendAdrr(device, uint8_t address,  uint8_t action)
	  return ;
  }

 uint8_t twi_read(uint8_t ACK_NACK){
	//set ASCK bit, wait and return the data register
	TWCR = ((1 << TWINT) | (1 << TWEN) | (ACK_NACK << TWEA));

	while(!(TWCR & (1<<TWINT)));
	return TWDR;
 }
#endif /* TWI_H_ */