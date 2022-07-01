/*
 * Uart_cfg.h
 *
 *  Created on: Apr 11, 2022
 *      Author: modata7
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

typedef struct
{
	void* BusNumber;

	u16 BaudRate;

	u16 StopBits;

	u16 Parity;

}UART_tenuCFG;


//Baud Rate
#define UART_BAUD_RATE_9600_16MHZ	0x683

//Stop Bits
#define	ONE_STOP_BIT	0x0000
#define	HALF_STOP_BIT	0x1000
#define	TWO_STOP_BIT	0x2000

//Parity
#define NO_PARITY		0x0000
#define EVEN_PARITY		0x0600
#define ODD_PARITY		0x0400


#endif /* UART_CFG_H_ */
