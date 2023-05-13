/*
 * main.c
 *
 * Created: 5/12/2023 11:33:55 AM
 *  Author: vladi
 */ 

#include <xc.h>
#include "USART.h"
#include "IOE8.h"
#include "IOE16.h"
#include "TS.h"
#include "SPI.h"

int main(void)
{
	

	// Initial Master I2C
	i2c_init();
	IOEInit();
	USARTinit();
	SPIinit();
	// Initial the MCP23008 GP0 to GP7 as Output
	Write_MCP23008(IODIR,0b00000000);
	Write_MCP23008(GPIO,0b00000000);    // Reset all the Output Port

	Write_MCP23008(GPIO,0xFF);
	IOEWrite(0xFFFF);
	_delay_ms(10000);
	Write_MCP23008(GPIO,0x00);
	IOEWrite(0x0000);
	_delay_ms(10000);
	
	// Loop Forever
	while(1) {
		uint16_t temp = ADCread();
		uint8_t msb = (temp << 1) >> 9;
		uint8_t lsb = (temp << 8) >> 8;
		USARTtransmitLineInt(lsb);
		Write_MCP23008(GPIO,msb);
		IOEWrite(0xFFFF);
		_delay_ms(10000);
		Write_MCP23008(GPIO,0x00);
		IOEWrite(0x0000);
		_delay_ms(10000);

	}


	return 0;
}
