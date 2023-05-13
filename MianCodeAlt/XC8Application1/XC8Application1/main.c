// /*
//  * main.c
//  *
//  * Created: 4/28/2023 12:40:32 PM
//  *  Author: vladi
//  */ 
// 
// #include <xc.h>
// #include "IOE.h"
// #include "USART.h"
// #include "TS.h"
// 
// int main(void)
// {
// 	i2c_init();
// 	//USARTinit();
// 	IOEInit();
//     while(1)
//     {
//  		IOEWrite(0xFFFF);
// 		_delay_ms(100);
// 		
// // 		uint16_t temp = TSReadTemp16();
// // 		//IOEWrite(temp);
// // 		char sign = (temp >> 15) > 0 ? '+' : '-';
// // 		temp = temp >> 4;
// // 		uint8_t msb = (temp << 1) >> 8;
// // 		uint8_t lsb = (temp << 8) >> 8;
// // 		USARTtransmitChar(sign);
// // 		USARTtransmitInt(msb);
// // 		USARTtransmitChar('.');
// // 		USARTtransmitLineInt(lsb);
//  		IOEWrite(0xFFFF);
// 		_delay_ms(100);
// 		
// 		
// 	}
// }

//***************************************************************************
//  File Name	 : I2Cvb1ioexp.c
//  Version	 : 1.0
//  Description  : AVR I2C Bus Master
//  IDE          : Atmel AVR Studio
//  Programmer   : Stokkink
//               :
//  Last Updated : April 2016
//***************************************************************************
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include "IOE.h"
#include "TS.h"
#include "USART.h"

#define MAX_TRIES 50
#define MCP23008_ID    0x40  // MCP23008 Device Identifier
#define MCP23008_ADDR  0x00  // MCP23008 Device Address
#define IODIR 0x00           // MCP23008 I/O Direction Register
#define GPIO  0x09           // MCP23008 General Purpose I/O Register
#define OLAT  0x0A           // MCP23008 Output Latch Register
#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0
#define DATASIZE 32

void Write_MCP23008(unsigned char reg_addr,unsigned char data)
{
	// Start the I2C Write Transmission
	i2c_start(MCP23008_ID,MCP23008_ADDR,TW_WRITE);
	// Sending the Register Address
	i2c_write(reg_addr);
	// Write data to MCP23008 Register
	i2c_write(data);
	// Stop I2C Transmission
	i2c_stop();
}
unsigned char Read_MCP23008(unsigned char reg_addr)
{
	char data;
	// Start the I2C Write Transmission
	i2c_start(MCP23008_ID,MCP23008_ADDR,TW_WRITE);
	// Read data from MCP23008 Register Address
	i2c_write(reg_addr);
	// Stop I2C Transmission
	i2c_stop();

	// Re-Start the I2C Read Transmission
	i2c_start(MCP23008_ID,MCP23008_ADDR,TW_READ);
	i2c_read(&data,NACK);

	// Stop I2C Transmission
	i2c_stop();

	return data;
}


int main(void)
{
	
	int x=0;
	// Initial Master I2C
	i2c_init();
	// Initial the MCP23008 GP0 to GP7 as Output
	Write_MCP23008(IODIR,0b00000000);
	Write_MCP23008(GPIO,0b00000000);    // Reset all the Output Port

	// Loop Forever
	while(1) {
		//uint16_t temp = TSReadTemp16();
		//IOEWrite(temp);
		Write_MCP23008(GPIO, 0xFF);
		_delay_ms(100);
// 	 	char sign = (temp >> 15) > 0 ? '+' : '-';
// 		temp = temp >> 4;
// 		uint8_t msb = (temp << 1) >> 8;
// 		uint8_t lsb = (temp << 8) >> 8;
// 		USARTtransmitChar(sign);
// 		USARTtransmitInt(msb);
// 		USARTtransmitChar('.');
// 		USARTtransmitLineInt(lsb);
// 		// Write to MCP23008 GPIO Register
		Write_MCP23008(GPIO, 0x00);
		_delay_ms(100);
	}


	return 0;
}
/* EOF: I2Cvb1ioexp.c */

