/*
 * Uart.c
 *
 *  Created on: Apr 10, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "Uart_cfg.h"

#include "Uart.h"

#include "Dma.h"

#include "Dma_cfg.h"

typedef struct
{
	volatile u32 SR;

	volatile u32 DR;

	volatile u32 BRR;

	volatile u32 CR1;

	volatile u32 CR2;

	volatile u32 CR3;

	volatile u32 GTPR;

}UART_t;

//IRQHandlers Prototypes
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);

static cbf App_Cbf[NumofUartChannels];

static UART_tenuBusyStatus UART_enuBusyFlag[NumofUartChannels] = {NotBusy,NotBusy,NotBusy};

pu8 UART_pu8DataBuffer;
u32 UART_u32BufferSize;
u8 	UART_u8BufferIndex = 0;

#define	RECEIVER_ENABLE 			0x4
#define	TRANSMITTER_ENABLE	 		0x8
#define	TC							0x40
#define RXNE						0x20
#define LIN_BREAK_DETECTION_FLAG	0x0100

#define TXE_INT_ENABLE				0x80	//TXE interrupt enable
#define TCIE_INT_ENABLE				0x40	//Transmission complete interrupt enable
#define RXNEIE_INT_ENABLE			0x20	//RXNE interrupt enable
#define IDLEIE_INT_ENABLE			0x20	//IDLE interrupt enable

void UART_vidInit(const UART_tenuCFG* Uart_cfg)
{
	//Baud Rate
	((UART_t*) Uart_cfg -> BusNumber) -> BRR = Uart_cfg -> BaudRate;

	//Parity control
	((UART_t*) Uart_cfg -> BusNumber) -> CR1 |= Uart_cfg -> Parity;

	//stop bits
	((UART_t*) Uart_cfg -> BusNumber) -> CR2 |= Uart_cfg -> StopBits;

	//Enable Transmitter
	((UART_t*) Uart_cfg -> BusNumber) -> CR1 |= TRANSMITTER_ENABLE;

	//Enable Receiver
	((UART_t*) Uart_cfg -> BusNumber) -> CR1 |= RECEIVER_ENABLE;
}

void UART_vidSendByteSynchronous(u8 Copy_u8Data, void* Add_enuChannelNum)
{
	//Send Data
	((UART_t*) Add_enuChannelNum) -> DR = Copy_u8Data;

	//Wait for Transmit Complete flag to be raised
	while( !((((UART_t*) Add_enuChannelNum) -> SR) & TC) );
}

UART_tenuBusyStatus UART_enuSendByteASynchronous(u8 Copy_u8Data, void* Add_enuChannelNum)
{
	UART_tenuBusyStatus Loc_enuBusyStatus = NotBusy;

	Uart_tenuUartCbfChannels Loc_enuUartChannel = NumofUartChannels;

	switch( (u32)Add_enuChannelNum)
	{
	case (u32)USART1:
			Loc_enuUartChannel = Uart_enuUart1;
	break;
	case (u32)USART2:
			Loc_enuUartChannel = Uart_enuUart2;
	break;
	case (u32)USART6:
			Loc_enuUartChannel = Uart_enuUart6;
	break;
	}

	if(UART_enuBusyFlag[Loc_enuUartChannel] == NotBusy)
	{
		//Raise the Busy Flag
		UART_enuBusyFlag[Loc_enuUartChannel] = Busy;

		//Send Data
		((UART_t*) Add_enuChannelNum) -> DR = Copy_u8Data;
	}
	else
	{
		Loc_enuBusyStatus = Busy;
	}

	return Loc_enuBusyStatus;
}

UART_tenuBusyStatus UART_enuSendBuffer(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum)
{
	UART_tenuBusyStatus Loc_enuBusyStatus = NotBusy;

	Uart_tenuUartCbfChannels Loc_enuUartChannel = NumofUartChannels;

	switch( (u32)Add_enuChannelNum)
	{
	case (u32)USART1:
			Loc_enuUartChannel = Uart_enuUart1;
	break;
	case (u32)USART2:
			Loc_enuUartChannel = Uart_enuUart2;
	break;
	case (u32)USART6:
			Loc_enuUartChannel = Uart_enuUart6;
	break;
	}

	if(UART_enuBusyFlag[Loc_enuUartChannel] == NotBusy)
	{
		UART_enuBusyFlag[Loc_enuUartChannel] = Busy;

		UART_pu8DataBuffer = Add_pu8Data;

		UART_u32BufferSize = Copy_u32Size;

		((UART_t*)Add_enuChannelNum) -> DR = UART_pu8DataBuffer[UART_u8BufferIndex];

		//Transmission complete interrupt enable
		((UART_t*)Add_enuChannelNum) -> CR1 |= TCIE_INT_ENABLE;
	}
	else
	{
		Loc_enuBusyStatus = Busy;
	}

	return Loc_enuBusyStatus;
}

UART_tenuBusyStatus UART_enuReceiveBuffer(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum)
{
	UART_tenuBusyStatus Loc_enuBusyStatus = NotBusy;

	Uart_tenuUartCbfChannels Loc_enuUartChannel = NumofUartChannels;

	switch( (u32)Add_enuChannelNum)
	{
	case (u32)USART1:
			Loc_enuUartChannel = Uart_enuUart1;
	break;
	case (u32)USART2:
			Loc_enuUartChannel = Uart_enuUart2;
	break;
	case (u32)USART6:
			Loc_enuUartChannel = Uart_enuUart6;
	break;
	}

	if(UART_enuBusyFlag[Loc_enuUartChannel] == NotBusy)
	{
		UART_enuBusyFlag[Loc_enuUartChannel] = Busy;

		 UART_pu8DataBuffer = Add_pu8Data;

		UART_u32BufferSize = Copy_u32Size;

		//RXNE interrupt enable
		((UART_t*)Add_enuChannelNum) -> CR1 |= RXNEIE_INT_ENABLE;

	}
	else
	{
		Loc_enuBusyStatus = Busy;
	}

	return Loc_enuBusyStatus;
}

UART_tenuBusyStatus UART_enuSendBufferDMA(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum)
{
	UART_tenuBusyStatus Loc_enuBusyStatus = NotBusy;

	Uart_tenuUartCbfChannels Loc_enuUartChannel = NumofUartChannels;

	DMA_tstrCfgStream* DMA_CFG;

	switch( (u32)Add_enuChannelNum)
	{
	case (u32)USART1:
			Loc_enuUartChannel = Uart_enuUart1;
	break;
	case (u32)USART2:
			Loc_enuUartChannel = Uart_enuUart2;
	break;
	case (u32)USART6:
			Loc_enuUartChannel = Uart_enuUart6;
	break;
	}

	if(UART_enuBusyFlag[Loc_enuUartChannel] == NotBusy)
	{
		UART_enuBusyFlag[Loc_enuUartChannel] = Busy;

		//Destination
		DMA_CFG -> DMA_u32PeripheralAddress = (u32)&((UART_t*) Add_enuChannelNum) -> DR;

		//Source
		DMA_CFG -> DMA_u32MemoryAddress = (u32)Add_pu8Data;

		DMA_CFG -> DMA_u16NumberOfData = Copy_u32Size;

		DMA_CFG -> DMA_u8ChannelDirection = DMA_u8MEMORY_TO_PERIPHERAL;

		DMA_CFG -> DMA_u16MemoryDataSize = DMA_u16MEMORY_BYTE;

		DMA_CFG -> DMA_u16PeripheralDataSize = DMA_u16PERIPHERAL_BYTE;

		DMA_CFG -> DMA_u16MemoryIncrementMode = DMA_u16MEMORY_INC_POINTER;

		DMA_CFG -> DMA_u16PeripheralIncrementMode = DMA_u16PERIPHERAL_FIXED_POINTER;

		DMA_CFG -> DMA_u32Mode = DMA_u32NORMAL_MODE;

		DMA_CFG -> DMA_u32Priority = DMA_u32HIGH;

		switch((u32)Add_enuChannelNum)
		{
		case (u32)USART1:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA2;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_4;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_7;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_7 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA2 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_7 , Add_enuChannelNum);

		break;
		case (u32)USART2:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA1;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_4;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_6;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_6 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA1 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_6 , Add_enuChannelNum);

		break;

		case (u32)USART6:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA2;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_5;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_6;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_6 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA2 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_6 , Add_enuChannelNum);

		break;
		}

	}
	else
	{
		Loc_enuBusyStatus = Busy;
	}

	return Loc_enuBusyStatus;
}

UART_tenuBusyStatus UART_enuReceiveBufferDMA(pu8 Add_pu8Data, u32 Copy_u32Size , void* Add_enuChannelNum)
{
	UART_tenuBusyStatus Loc_enuBusyStatus = NotBusy;

	Uart_tenuUartCbfChannels Loc_enuUartChannel = NumofUartChannels;

	DMA_tstrCfgStream* DMA_CFG;

	switch( (u32)Add_enuChannelNum)
	{
	case (u32)USART1:
			Loc_enuUartChannel = Uart_enuUart1;
	break;
	case (u32)USART2:
			Loc_enuUartChannel = Uart_enuUart2;
	break;
	case (u32)USART6:
			Loc_enuUartChannel = Uart_enuUart6;
	break;
	}

	if(UART_enuBusyFlag[Loc_enuUartChannel] == NotBusy)
	{
		UART_enuBusyFlag[Loc_enuUartChannel] = Busy;

		//Destination
		DMA_CFG -> DMA_u32PeripheralAddress = (u32)&((UART_t*) Add_enuChannelNum) -> DR;

		//Source
		DMA_CFG -> DMA_u32MemoryAddress = (u32)Add_pu8Data;

		DMA_CFG -> DMA_u16NumberOfData = Copy_u32Size;

		DMA_CFG -> DMA_u8ChannelDirection = DMA_u8PERIPHERAL_TO_MEMORY;

		DMA_CFG -> DMA_u16MemoryDataSize = DMA_u16MEMORY_BYTE;

		DMA_CFG -> DMA_u16PeripheralDataSize = DMA_u16PERIPHERAL_BYTE;

		DMA_CFG -> DMA_u16MemoryIncrementMode = DMA_u16MEMORY_FIXED_POINTER;

		DMA_CFG -> DMA_u16PeripheralIncrementMode = DMA_u16PERIPHERAL_INC_POINTER;

		DMA_CFG -> DMA_u32Mode = DMA_u32NORMAL_MODE;

		DMA_CFG -> DMA_u32Priority = DMA_u32HIGH;

		switch((u32)Add_enuChannelNum)
		{
		case (u32)USART1:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA2;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_4;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_7;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_7 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA2 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_7 , Add_enuChannelNum);

		break;
		case (u32)USART2:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA1;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_4;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_6;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_6 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA1 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_6 , Add_enuChannelNum);

		break;

		case (u32)USART6:

		//DMA Controller
		DMA_CFG -> DMA_pvidDMAController = DMA2;

		//Channel Selection
		DMA_CFG -> DMA_u32ChannelSelection = DMA_u32Channel_5;

		//Stream Number
		DMA_CFG -> DMA_u8StreamNumber = DMA_u8STREAM_6;

		//DMA Init
		DMA_vidStreamInit(DMA_CFG);

		DMA_vidControlInterrupt(DMA_u8STREAM_6 , DMA_u8TRANSFERE_COMPLETE_INTERRUPT , DMA2 , DMA_u8INTERRUPT_ENABLE);

		DMA_vidTransfereStart(DMA_u8STREAM_6 , Add_enuChannelNum);

		break;
		}

	}
	else
	{
		Loc_enuBusyStatus = Busy;
	}

	return Loc_enuBusyStatus;
}
void UART_vidRegisterCallBackFunction(cbf Add_Cbf, void* Add_enuChannelNum)
{
	if(Add_Cbf)
	{
		switch( (u32) Add_enuChannelNum)
		{
		case (u32)USART1:

				App_Cbf[Uart_enuUart1] = Add_Cbf;

		break;

		case (u32)USART2:

				App_Cbf[Uart_enuUart2] = Add_Cbf;

		break;

		case (u32)USART6:

				App_Cbf[Uart_enuUart6] = Add_Cbf;

		break;
		}
	}
}

void USART1_IRQHandler(void)
{
	//Check the Transition Complete Flag
	if( ( ((UART_t*) USART1) -> SR  & TC) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Transition is ready
			UART_enuBusyFlag[Uart_enuUart1] = NotBusy;

			UART_u8BufferIndex = 0;

			//Notify the user that the buffer is Transmitted
			if(App_Cbf[Uart_enuUart1])
			{
				App_Cbf[Uart_enuUart1]();
			}
		}
		else
		{
			//  Transmit the rest of the buffer
			((UART_t*)USART1) -> DR = UART_pu8DataBuffer[UART_u8BufferIndex++];
		}
	}
	else
	{
		UART_enuBusyFlag[Uart_enuUart1] = Busy;
	}

	// Check the Read data register not empty Flag
	if(( ((UART_t*) USART1) -> SR  & RXNE) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Receiving is Ready
			UART_enuBusyFlag[Uart_enuUart1] = NotBusy;

			UART_u8BufferIndex = 0;
		}

		//Notify the user that the buffer is Received
		if(App_Cbf[Uart_enuUart1])
		{
			App_Cbf[Uart_enuUart1]();
		}
		else
		{
			//  Receive the rest of the buffer
			UART_pu8DataBuffer[UART_u8BufferIndex++] = ((UART_t*)USART1) -> DR;
		}
	}

	//Check the LIN break Detection Flag
	if(( ((UART_t*) USART1) -> SR  & LIN_BREAK_DETECTION_FLAG))
	{
		//LIN_enuGlobalSlaveState = HeaderReceive;
	}
}

void USART2_IRQHandler(void)
{
	//Check the Transition Complete Flag
	if( ( ((UART_t*) USART2) -> SR  & TC) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Transition is ready
			UART_enuBusyFlag[Uart_enuUart2] = NotBusy;

			UART_u8BufferIndex = 0;

			//Notify the user that the buffer is Transmitted
			if(App_Cbf[Uart_enuUart2])
			{
				App_Cbf[Uart_enuUart2]();
			}
		}
		else
		{
			//  Transmit the rest of the buffer
			((UART_t*)USART2) -> DR = UART_pu8DataBuffer[UART_u8BufferIndex++];
		}
	}
	else
	{
		UART_enuBusyFlag[Uart_enuUart2] = Busy;
	}

	// Check the Read data register not empty Flag
	if(( ((UART_t*) USART2) -> SR  & RXNE) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Receiving is Ready
			UART_enuBusyFlag[Uart_enuUart2] = NotBusy;

			UART_u8BufferIndex = 0;
		}

		//Notify the user that the buffer is Received
		if(App_Cbf[Uart_enuUart2])
		{
			App_Cbf[Uart_enuUart2]();
		}
		else
		{
			//  Receive the rest of the buffer
			UART_pu8DataBuffer[UART_u8BufferIndex++] = ((UART_t*)USART2) -> DR;
		}
	}

	//Check the LIN break Detection Flag
	if(( ((UART_t*) USART2) -> SR  & LIN_BREAK_DETECTION_FLAG))
	{
		//LIN_enuGlobalSlaveState = HeaderReceive;
	}
}
void USART6_IRQHandler(void)
{
	//Check the Transition Complete Flag
	if( ( ((UART_t*) USART6) -> SR  & TC) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Transition is ready
			UART_enuBusyFlag[Uart_enuUart6] = NotBusy;

			UART_u8BufferIndex = 0;

			//Notify the user that the buffer is Transmitted
			if(App_Cbf[Uart_enuUart6])
			{
				App_Cbf[Uart_enuUart6]();
			}
		}
		else
		{
			//  Transmit the rest of the buffer
			((UART_t*)USART6) -> DR = UART_pu8DataBuffer[UART_u8BufferIndex++];
		}
	}
	else
	{
		UART_enuBusyFlag[Uart_enuUart6] = Busy;
	}

	// Check the Read data register not empty Flag
	if(( ((UART_t*) USART6) -> SR  & RXNE) )
	{
		//Check if the Buffer is completed
		if(UART_u8BufferIndex == UART_u32BufferSize)
		{
			// Receiving is Ready
			UART_enuBusyFlag[Uart_enuUart6] = NotBusy;

			UART_u8BufferIndex = 0;
		}

		//Notify the user that the buffer is Received
		if(App_Cbf[Uart_enuUart6])
		{
			App_Cbf[Uart_enuUart6]();
		}
		else
		{
			//  Receive the rest of the buffer
			UART_pu8DataBuffer[UART_u8BufferIndex++] = ((UART_t*)USART6) -> DR;
		}
	}

	//Check the LIN break Detection Flag
	if(( ((UART_t*) USART6) -> SR  & LIN_BREAK_DETECTION_FLAG))
	{
		//LIN_enuGlobalSlaveState = HeaderReceive;
	}
}
