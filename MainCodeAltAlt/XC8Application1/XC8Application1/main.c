/*
 * main.c
 *
 * Created: 5/12/2023 11:33:55 AM
 *  Author: vladi
 */ 

//#include <xc.h>
// #include "USART.c"
// #include "IOE8.c"
// #include "IOE16.c"
// #include "SPI.c"
#include "I2C.h"

#define F_CPU 16000000UL

int main(void)
{
	

	// Initial Master I2C
	USARTinit();
	SPIinit();
	i2c_init();
	IOEInit();
	// Initial the MCP23008 GP0 to GP7 as Output
	Write_MCP23008(IODIR,0b00000000);
	Write_MCP23008(GPIO,0b00000000);    // Reset all the Output Port
	_delay_ms(20);
	Write_MCP23008(GPIO,0xFF);
	IOEWrite(0xFFFF);
	_delay_ms(10000);
	Write_MCP23008(GPIO,0x00);
	IOEWrite(0x0000);
	_delay_ms(10000);
	
	// Loop Forever
	while(1) {
		uint16_t temp = ADCread();
// 		uint8_t msb = (temp << 1) >> 9;
// 		uint8_t lsb = (temp << 8) >> 8;
		USARTtransmitLineInt(temp);
// 		Write_MCP23008(GPIO,0x00);
// 		Write_MCP23008(GPIO,(lsb));
//		IOEWrite(0xFFFF);
		IOEWrite(0x00);
		IOEWrite(temp);
		Write_MCP23008(GPIO,0xFF);
		_delay_ms(1000);
		Write_MCP23008(GPIO,0x00);
//		IOEWrite(0x0000);
		_delay_ms(1000);
	}
	return 0;	
}
