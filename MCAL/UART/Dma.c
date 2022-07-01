/*
 * Dma.c
 *
 *  Created on: Apr 22, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"
#include "Dma_cfg.h"
#include "Dma.h"

typedef struct
{
	volatile u32 SCR;
	volatile u32 SNDTR;
	volatile u32 SPAR;
	volatile u32 SM0AR;
	volatile u32 SM1AR;
	volatile u32 SFCR;
}DMA_Channel_t;

typedef struct
{
	volatile u32 LISR;
	volatile u32 HISR;
	volatile u32 LIFCR;
	volatile u32 HIFCR;

	DMA_Channel_t Stream[8];
}DMA_t;

static Cbf DMA_Cbf[2];

#define DMA_CONTROL	0x1

/****************************************************************************************************************/

void DMA_vidStreamInit(DMA_tstrCfgStream* Add_strStreamCfg)
{
	//Disable DMA
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR &= ~(DMA_CONTROL);

	//Select Channel
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u32ChannelSelection;

	//Select Channel Direction
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u8ChannelDirection;

	//Config Data size
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u16MemoryDataSize | Add_strStreamCfg -> DMA_u16PeripheralDataSize;

	//Set Priority
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u32Priority;

	//Set Increment Mode
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u16MemoryIncrementMode | Add_strStreamCfg -> DMA_u16PeripheralIncrementMode;

	//Set Mode
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SCR |= Add_strStreamCfg -> DMA_u32Mode;

	//Set the second memomry address in case of Double Buffer Mode
	if(Add_strStreamCfg -> DMA_u32Mode == DMA_u32DOUBLE_BUFFER_MODE)
	{
		((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SM1AR = Add_strStreamCfg -> DMA_u32Memory_2_Address;
	}
	//Set Number of Data
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SNDTR = Add_strStreamCfg -> DMA_u16NumberOfData;

	//Set Peripheral Address
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SPAR = Add_strStreamCfg -> DMA_u32PeripheralAddress;

	//Set Memory Address
	((DMA_t*)(Add_strStreamCfg -> DMA_pvidDMAController)) -> Stream[Add_strStreamCfg -> DMA_u8StreamNumber].SM0AR = Add_strStreamCfg -> DMA_u32MemoryAddress;

}

void DMA_vidTransfereStart(u8 Copy_u8StreamNumber , void* Add_pvidDMAController)
{
	//Clear Flags
	DMA_vidClearFlag(Copy_u8StreamNumber , CFEIFx	 , Add_pvidDMAController);
	DMA_vidClearFlag(Copy_u8StreamNumber , CDMEIFx	 , Add_pvidDMAController);
	DMA_vidClearFlag(Copy_u8StreamNumber , CTEIFx	 , Add_pvidDMAController);
	DMA_vidClearFlag(Copy_u8StreamNumber , CHTIFx	 , Add_pvidDMAController);
	DMA_vidClearFlag(Copy_u8StreamNumber , CTCIFx	 , Add_pvidDMAController);

	//Enable DMA
	((DMA_t*)(Add_pvidDMAController)) -> Stream[Copy_u8StreamNumber].SCR |= DMA_CONTROL;

}

void DMA_vidControlInterrupt(u8 Copy_u8StreamNumber , u8 Copy_u8InterruptType , void* Add_pvidDMAController , u8 Copu_u8On_Off)
{
	switch (Copu_u8On_Off)
	{
	case DMA_u8INTERRUPT_ENABLE:
		((DMA_t*)(Add_pvidDMAController)) -> Stream[Copy_u8StreamNumber].SCR |= Copy_u8InterruptType;
		break;
	case DMA_u8INTERRUPT_DISABLE:
		((DMA_t*)(Add_pvidDMAController)) -> Stream[Copy_u8StreamNumber].SCR &= ~(Copy_u8InterruptType);
		break;
	}
}

void DMA_vidClearFlag(u8 Copy_u8StreamNumber , u8 Copy_u8Flag , void* Add_pvidDMAController)
{
	if(Copy_u8StreamNumber < DMA_u8STREAM_4)
	{
		//Stream 0 - 1
		if(Copy_u8StreamNumber < DMA_u8STREAM_2)
		{
			((DMA_t*)(Add_pvidDMAController)) -> LIFCR |= Copy_u8Flag << (Copy_u8StreamNumber * 5);
		}
		else	//Stream 2 - 3
		{
			((DMA_t*)(Add_pvidDMAController)) -> LIFCR |= Copy_u8Flag << ((Copy_u8StreamNumber - 2) * 5) + 16;
		}
	}
	else
	{
		//Stream 4 - 5
		if(Copy_u8StreamNumber < DMA_u8STREAM_6)
		{
			((DMA_t*)(Add_pvidDMAController)) -> HIFCR |= Copy_u8Flag << ((Copy_u8StreamNumber - 4) * 5);
		}
		else	//Stream 6 - 7
		{
			((DMA_t*)(Add_pvidDMAController)) -> HIFCR |= Copy_u8Flag << ((Copy_u8StreamNumber - 6) * 5) + 16;
		}
	}
}

u8 DMA_vidGetFlag(u8 Copy_u8StreamNumber , u8 Copy_u8Flag , void* Add_pvidDMAController)
{
	u8 Loc_u8Flag;

	if(Copy_u8StreamNumber < DMA_u8STREAM_4)
		{
			//Stream 0 - 1
			if(Copy_u8StreamNumber < DMA_u8STREAM_2)
			{
				Loc_u8Flag = (((DMA_t*)(Add_pvidDMAController)) -> LIFCR & Copy_u8Flag) >> (Copy_u8StreamNumber * 5);
			}
			else	//Stream 2 - 3
			{
				Loc_u8Flag = (((DMA_t*)(Add_pvidDMAController)) -> LIFCR & Copy_u8Flag) >> ((Copy_u8StreamNumber - 2) * 5) + 16;
			}
		}
		else
		{
			//Stream 4 - 5
			if(Copy_u8StreamNumber < DMA_u8STREAM_6)
			{
				Loc_u8Flag = (((DMA_t*)(Add_pvidDMAController)) -> HIFCR & Copy_u8Flag) >> ((Copy_u8StreamNumber - 4) * 5);
			}
			else	//Stream 6 - 7
			{
				Loc_u8Flag = (((DMA_t*)(Add_pvidDMAController)) -> HIFCR & Copy_u8Flag) >> ((Copy_u8StreamNumber - 6) * 5) + 16;
			}
		}

	return Loc_u8Flag;
}

void DMA_vidRegisterCallBackFunction(Cbf App_Cbf , void* Add_pvidDMAController)
{
	if(App_Cbf)
	{
		switch((u32)Add_pvidDMAController)
		{
		case (u32)DMA1:
				DMA_Cbf[0] = App_Cbf;
		break;
		case (u32)DMA2:
				DMA_Cbf[1] = App_Cbf;
		break;
		}
	}
}

void DMA1_Stream0_IRQHandler(void)
{

}

void DMA2_Stream0_IRQHandler(void)
{

}

