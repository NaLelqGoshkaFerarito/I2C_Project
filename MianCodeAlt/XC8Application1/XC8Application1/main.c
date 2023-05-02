/*
 * main.c
 *
 * Created: 4/28/2023 12:40:32 PM
 *  Author: vladi
 */ 

#include <xc.h>
#include "IOE.h"
#include "USART.h"
#include "TS.h"

int main(void)
{
	i2c_init();
	USARTinit();
	IOEInit();
    while(1)
    {
		uint16_t temp = TSReadTemp16();
		//IOEWrite(temp);
		char sign = (temp >> 15) > 0 ? '+' : '-';
		temp = temp >> 4;
		uint8_t msb = (temp << 1) >> 8;
		uint8_t lsb = (temp << 8) >> 8;
		USARTtransmitChar(sign);
		USARTtransmitInt(msb);
		USARTtransmitChar('.');
		USARTtransmitLineInt(lsb);

	}
}