/*
 * SPI.h
 *
 * Created: 12 May 2023 15:37:28
 *  Author: vladi
 */ 


#ifndef SPI_H_
#define SPI_H_


#define SS 2        // pin 10 arduino uno
#define MOSI 3      // pin 11 arduino uno
#define MISO 4      // pin 12 arduino uno
#define SCK 5       // pin 13 arduino uno
#define TXD 1

#define CH0 0x40

#define ENABLE_SS PORTB &= (0 << SS)
#define DISABLE_SS PORTB |= (1 << SS)
#define ENABLE_SS2 PORTB &= ~(1 << PORTB1)  //pin 9 arduino = pin portb1 for other spi chips
#define DISABLE_SS2 PORTB |= (1 << PORTB1)

#define  FOSC 16000000
#define  BAUD 9600
#define  MYUBBR FOSC/16/BAUD -1


#define A 0
#define B 1

#define READ 1
#define WRITE 0

#define IODIR 0
#define OUTP_LATCH 10

volatile uint8_t spi_rx = 0;
volatile uint8_t spi_status = 0;

void SPIinit(){
// 	/* Set SS, MOSI and SCK output, all others input */
// 	DDRB = (1<<SS)|(1<<MOSI)|(1<<SCK)|(1 << PORTB1);
// 	/* LED PIN */
// 	DDRB |= (1 << PORTB0);
// 	/* Set TXD as an output */
// 	DDRD = (1 << TXD);
// 	
// 	/* Set the slave select pin (Active low) */
// 	DISABLE_SS;
// 	DISABLE_SS2;
// 	
// 	/* Enable SPI, Master, set clock rate fosc/16 */
// 	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
// 	/* Set MOSI and SCK output, all others input */
// 	DDRB = (1<<MOSI)|(1<<SCK);
// 	/* Enable SPI, Master, set clock rate fck/16 */
// 	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
	DDRB |= (1 << SCK) | (1 << SS) | (1 << MOSI) | (0 << MISO);
	PORTB |= (1 << SS);
	SPCR |=  (1 << SPE) | (1 << MSTR) | (1 << SPIE) | (1 << CPOL) | (0 << CPHA) | (1 << SPR0) | (1 << SPR1);

}

uint8_t SPItxrx(uint8_t data){
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}

uint8_t SPIrx(){
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}

uint16_t ADCread(){
	DISABLE_SS;
	ENABLE_SS;
	_delay_ms(5);
	//using CH0 on the ADC
	uint8_t msb = SPItxrx(CH0);
	uint8_t lsb = SPIrx();
	DISABLE_SS;
	uint16_t data = (msb << 8) | lsb;
	return data;
}
#endif /* SPI_H_ */