/*
 * USART.h
 *
 * Created: 28 Mar 2023 11:31:21
 *  Author: vladi
 */ 


#ifndef USART_H_
#define USART_H_


 #include <xc.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include <avr/io.h>

 #define BUFF_SZ 3
 #define F_CPU 16000000L
 #define BAUD 9600
 #define VAL ((F_CPU/16/BAUD) - 1)



void transmitUSART(uint8_t value){
	while ( !(UCSR0A & (1<<RXC0)));
	UDR0 = value;
}


 void initUSART(){
 //Set baud rate
 UBRR0H = (unsigned char)(VAL>>8);
 UBRR0L = (unsigned char)VAL;
 //Enable transmitter
 UCSR0B = 1<<TXEN0;
 // Data format: 8 bit 
 UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
 }
 



#endif /* USART_H_ */