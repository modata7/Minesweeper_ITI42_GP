/*
 * Uart.h
 *
 *  Created on: Apr 10, 2022
 *      Author: modata7
 */

#ifndef UART_H_
#define UART_H_

typedef enum
{
	NotBusy,

	Busy
}UART_tenuBusyStatus;

typedef enum
{
	Uart_enuUart1,

	Uart_enuUart2,

	Uart_enuUart6,

	NumofUartChannels

}Uart_tenuUartCbfChannels;

typedef void(*cbf)(void);

//Bus Number
#define USART1 ((void*) 0x40011000)
#define USART2 ((void*) 0x40004400)
#define USART6 ((void*) 0x40011400)

void UART_vidInit(const UART_tenuCFG* Uart_cfg);

void UART_vidSendByteSynchronous(u8 Copy_u8Data, void* Add_enuChannelNum);

UART_tenuBusyStatus UART_enuSendByteASynchronous(u8 Copy_u8Data, void* Add_enuChannelNum);

UART_tenuBusyStatus UART_enuSendBuffer(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum);

UART_tenuBusyStatus UART_enuReceiveBuffer(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum);

UART_tenuBusyStatus UART_enuSendBufferDMA(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum);

UART_tenuBusyStatus UART_enuReceiveBufferDMA(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum);

void UART_vidRegisterCallBackFunction(cbf Add_Cbf, void* Add_enuChannelNum);

#endif /* UART_H_ */
