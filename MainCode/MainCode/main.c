/*
 * main.c
 *
 * Created: 3/28/2023 11:25:53 AM
 *  Author: vladi
 */ 

#include <xc.h>
#include "USART.h"
int main(void)
{
	USARTinit();
    while(1)
    {
		USARTtransmitInt(23);
		_delay_ms(100);
		USARTtransmitLineInt(23);
		_delay_ms(100);
	}
}