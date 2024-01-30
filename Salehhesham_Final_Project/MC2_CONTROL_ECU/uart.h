/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Saleh
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*****************************************************************************************************/
/* Types Definitions  */
/*****************************************************************************************************/

/* Select the mode of USART */
typedef enum
{
	ASYNCH,SYNCH
}UART_Mode;

/* Select the Mode of Parity bit */
typedef enum
{
	DISABLE,RESERVED,En_EvenParity,En_OddParity
}UART_parity;

/* Select the number of stop Bits */
typedef enum
{
	ONEBIT,TWOBITS
}UART_StopBit;

/* Select the Size */
typedef enum
{
	BITS_5,BITS_6,BITS_7,BITS_8,BITS_9=0X07
}UART_BitData;

/* Select the Baud Rate of the UART-Driver */
typedef enum
{
	BAUD_10=10,BAUD_300=300,BAUD_600=600,BAUD_12H=1200,BAUD_24H=2400,BAUD_48H=4800,BAUD_96H=9600,
	BAUD_144H=14400,BAUD_192H=19200,BAUD_384H=38400,BAUD_576=57600,BAUD_115K=115200,
	BAUD_128K=128000,BAUD_256K=256000
}UART_BaudRate;

typedef struct
{
	UART_Mode                 Mode;
	UART_parity             parity;
	UART_StopBit          stop_bit;
	UART_BitData          bit_data;
	UART_BaudRate        baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
