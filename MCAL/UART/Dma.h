/*
 * Dma.h
 *
 *  Created on: Apr 22, 2022
 *      Author: modata7
 */

#ifndef DMA_H_
#define DMA_H_

typedef void(*Cbf)(void);

typedef struct
{
	void* 	DMA_pvidDMAController;
	u8		DMA_u8StreamNumber;
	u32 	DMA_u32ChannelSelection;
	u8		DMA_u8ChannelDirection;
	u32		DMA_u32PeripheralAddress;
	u32		DMA_u32MemoryAddress;
	u32		DMA_u32Memory_2_Address;
	u16		DMA_u16NumberOfData;
	u16		DMA_u16MemoryDataSize;
	u16		DMA_u16PeripheralDataSize;
	u16		DMA_u16MemoryIncrementMode;
	u16		DMA_u16PeripheralIncrementMode;
	u32		DMA_u32Mode;
	u32		DMA_u32Priority;
}DMA_tstrCfgStream;

/*DMA Controller*/
/*
DMA1
DMA2
*/

/*Stream Number*/
#define DMA_u8STREAM_0		0
#define DMA_u8STREAM_1		1
#define DMA_u8STREAM_2		2
#define DMA_u8STREAM_3		3
#define DMA_u8STREAM_4		4
#define DMA_u8STREAM_5		5
#define DMA_u8STREAM_6		6
#define DMA_u8STREAM_7		7

/*Interrupt Type*/
#define DMA_u8TRANSFERE_COMPLETE_INTERRUPT	0x10
#define DMA_u8HALF_TRANSFERE_INTERRUPT		0x08
#define DMA_u8TRANSFERE_ERROR_INTERRUPT		0x04
#define DMA_u8DIRECT_MODE_ERROR_INTERRUPT	0x02

/*Interrupt Control*/
#define DMA_u8INTERRUPT_DISABLE				0
#define DMA_u8INTERRUPT_ENABLE				1

/*FLAGS*/
#define	CFEIFx	0x01
#define	CDMEIFx	0x04
#define	CTEIFx	0x08
#define	CHTIFx	0x10
#define	CTCIFx	0x20

/*Function Prototypes*/
void DMA_vidStreamInit(DMA_tstrCfgStream* Add_strStreamCfg);

void DMA_vidTransfereStart(u8 Copy_u8StreamNumber , void* Add_pvidDMAController);

void DMA_vidControlInterrupt(u8 Copy_u8StreamNumber , u8 Copy_u8InterruptType , void* Add_pvidDMAController , u8 Copu_u8On_Off);

void DMA_vidClearFlag(u8 Copy_u8StreamNumber , u8 Copy_u8Flag , void* Add_pvidDMAController);

u8 DMA_vidGetFlag(u8 Copy_u8StreamNumber , u8 Copy_u8Flag , void* Add_pvidDMAController);

void DMA_vidRegisterCallBackFunction(Cbf App_Cbf , void* Add_pvidDMAController);

#endif /* DMA_H_ */
