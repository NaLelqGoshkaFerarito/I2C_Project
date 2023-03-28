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

 #define BUFF_SZ 8
 #define F_CPU 16000000L
 #define BAUD 9600
 #define VAL ((F_CPU/16/BAUD) - 1)



void USARTtransmitInt(uint8_t value){
	char str[BUFF_SZ];
	sprintf(str, "%d", value);
	for (int i = 0; i < BUFF_SZ && str[i] != '\0'; ++i){
		//sprintf(&UDR0, "%c", str[i]);
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = str[i];
	}
}


void USARTtransmit(char* value){
	for (int i = 0; i < BUFF_SZ && value[i] != '\0'; ++i){
		//sprintf(&UDR0, "%c", str[i]);
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = value[i];
	}
}


void USARTtransmitLineInt(uint8_t value){
	char str[BUFF_SZ + 1];
	//convert to string
	sprintf(str, "%d", value);
	for (int i = 0; i < BUFF_SZ && str[i] != '\0'; ++i){
		//sprintf(&UDR0, "%c", str[i]);
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = str[i];
	}
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = '\n';
}


void USARTtransmitLine(char* value){
	for (int i = 0; i < BUFF_SZ && value[i] != '\0'; ++i){
		//sprintf(&UDR0, "%c", str[i]);
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = value[i];
	}
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = '\n';
}


 void USARTinit(){
	//Set baud rate
	UBRR0H = (unsigned char)(VAL>>8);
	UBRR0L = (unsigned char)VAL;
	//Enable transmitter
	UCSR0B = 1<<TXEN0;
	// Data format: 8 bit 
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
 }
 



#endif /* USART_H_ */