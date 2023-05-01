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
#include "../../lib/i2c/i2c.h"
#include "../../lib/i2c/i2c.c"


#if I2C
int main(void)
{
	USARTinit();
	mcp_init();
	while(1)
    {
		uint16_t val = 0xFFFF;
		//if (IOEWrite8_I2C(GPIO0, val) != 0) USARTtransmitInt(6);
		visualize(val);
	}
}
#endif //I2C

#if TWI
int main(void)
{
	USARTinit();
	IOInit_TWI();
	while(1)
	{
		uint16_t val = 0xFFFF;
		//if (IOEWrite8_I2C(GPIO0, val) != 0) USARTtransmitInt(6);
		IOEWrite16_TWI(val);
	}
}
#endif //TWI