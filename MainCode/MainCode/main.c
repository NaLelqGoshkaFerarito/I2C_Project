/*
 * main.c
 *
 * Created: 3/28/2023 11:25:53 AM
 *  Author: vladi
 */ 

#include <xc.h>
#include "USART.h"
#include "TWI.h"
#include "IOExp.h"


int main(void)
{
	USARTinit();
	if(IOInit_I2C() != 0) USARTtransmitInt(4);
    while(1)
    {
		uint8_t val = 00;
		if (IOEWrite8(GPIO0, val) != 0) USARTtransmitInt(6);
	}
}