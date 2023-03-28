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
	initUSART();
    while(1)
    {
		//char str[3];
		char str[BUFF_SZ] = "13\n";
		for (int i = 0; i < BUFF_SZ; ++i){
			sprintf(&UDR0, "%c", str[i]);
		}
	}
}