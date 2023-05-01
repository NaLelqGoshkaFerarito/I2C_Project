/*
 * main.c
 *
 * Created: 4/28/2023 12:40:32 PM
 *  Author: vladi
 */ 

#include <xc.h>
#include "../../../lib/i2c/i2c.h"
#include "../../../lib/i2c/i2c.c"
//#include "IOE.h"

//device address and ID (determined by A0:2)
#define IOE16_ADDR (0x20)
#define IOE16_ID 0
//IO direction register
#define IODIR0 0x00
#define IODIR1 0x01
//IO pins
#define GPIO0 0x12
#define GPIO1 0x13

int main(void)
{
	i2c_init();
	IOEInit();
    while(1)
    {
		

		i2c_tx_start(MASTER_TRANSMITTER);
		i2c_tx_address(IOE16_ADDR);
		i2c_tx_byte(GPIO0);
		i2c_tx_byte(0XFF);
		i2c_tx_stop();

		i2c_tx_start(MASTER_TRANSMITTER);
		i2c_tx_address(IOE16_ADDR);
		i2c_tx_byte(GPIO1);
		i2c_tx_byte(0XFF);
		i2c_tx_stop();
	}
}