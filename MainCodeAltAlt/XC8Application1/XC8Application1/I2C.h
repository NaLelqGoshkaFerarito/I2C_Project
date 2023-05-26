/*
 * I2C.h
 *
 * Created: 12 May 2023 11:37:22
 *  Author: vladi
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

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

#endif /* I2C_H_ */