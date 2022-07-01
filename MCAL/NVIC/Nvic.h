/*
 * Nvic.h
 *
 *  Created on: Mar 28, 2022
 *      Author: modata7
 */

#ifndef NVIC_H_
#define NVIC_H_

/* Error Status */
typedef enum
{
	NVIC_enuOK,

	NVIC_enuNOK,

	NVIC_enuInvalidInput

}NVIC_tenuErrorStatus;

/* ACTIVE STATUS */
typedef enum
{
	NVIC_enuActive,

	NVIC_enuNotActive,

	NVIC_enuError

}NVIC_tenuActiveStatus;

/* ON OFF MODES */
#define	NVIC_u8ENABLE	1
#define	NVIC_u8DISABLE	0

/* Set Interrupt Groups & Sub-Groups Priority */
#define NVIC_GROUP_4_SUB_0		0x05FA0000
#define NVIC_GROUP_3_SUB_1		0x05FA0400
#define NVIC_GROUP_2_SUB_2		0x05FA0500
#define NVIC_GROUP_1_SUB_3		0x05FA0600
#define NVIC_GROUP_0_SUB_4		0x05FA0700

/* Peripherals */
#define	 NVIC_WWDG					0
#define	 NVIC_EXTI16_PVD				1
#define  NVIC_EXTI21               	2
#define  NVIC_EXTI22               	3
#define  NVIC_FLASH                	4
#define  NVIC_RCC                  	5
#define  NVIC_EXTI0                	6
#define  NVIC_EXTI1                	7
#define  NVIC_EXTI2                	8
#define  NVIC_EXTI3                	9
#define  NVIC_EXTI4               	10
#define  NVIC_DMA1_STREAM0           11
#define  NVIC_DMA1_STREAM1           12
#define  NVIC_DMA1_STREAM2           13
#define  NVIC_DMA1_STREAM3           14
#define  NVIC_DMA1_STREAM4           15
#define  NVIC_DMA1_STREAM5           16
#define  NVIC_DMA1_STREAM6           17
#define  NVIC_ADC                    18
#define  NVIC_EXTI9_5                23
#define  NVIC_TIM1_BRK_TIM9          24
#define  NVIC_TIM1_UP_TIM10          25
#define  NVIC_TIM1_TRG_COM_TIM11     26
#define  NVIC_TIM1_CC           		27
#define  NVIC_TIM2               	28
#define  NVIC_TIM3               	29
#define  NVIC_TIM4               	30
#define  NVIC_I2C1_EV                31
#define  NVIC_I2C1_ER           		32
#define  NVIC_I2C2_EV           		33
#define  NVIC_I2C2_ER           		34
#define  NVIC_SPI1                   35
#define  NVIC_SPI2                   36
#define  NVIC_USART1                 37
#define  NVIC_USART2                 38
#define  NVIC_EXTI15_10              40
#define  NVIC_EXTI17                 41
#define  NVIC_EXTI18                 42
#define  NVIC_DMA1_STREAM7           47
#define  NVIC_SDIO                	49
#define  NVIC_TIM5                	50
#define  NVIC_SPI3                	51
#define  NVIC_DMA2_STREAM0           56
#define  NVIC_DMA2_STREAM1           57
#define  NVIC_DMA2_STREAM2           58
#define  NVIC_DMA2_STREAM3           59
#define  NVIC_DMA2_STREAM4           60
#define  NVIC_OTG_FS                 67
#define  NVIC_DMA2_STREAM5           68
#define  NVIC_DMA2_STREAM6           69
#define  NVIC_DMA2_STREAM7           70
#define  NVIC_USART6                 71
#define  NVIC_I2C3_EV                72
#define  NVIC_I2C3_ER                73
#define  NVIC_FPU                    81
#define  NVIC_SPI4                   84

/* Function Prototypes */
NVIC_tenuErrorStatus NVIC_enuControlInterupt(u32 Copy_u32Peripheral , u8 Copy_u8OnOff);

NVIC_tenuErrorStatus NVIC_enuSetPriority(u32 Copy_u32Peripheral , u8 Copy_u8Priority);

NVIC_tenuErrorStatus NVIC_enuSetSubGroupPriority(u32 Copy_u32SubGroupPriority);

NVIC_tenuErrorStatus NVIC_enuControlPending(u32 Copy_u32Peripheral , u8 Copy_u8OnOff);

NVIC_tenuActiveStatus NVIC_enuGetActiveStatus(u32 Copy_u32Peripheral);

u8 NVIC_u8GetEncodingPriority(u8 Copy_u8NumberOfSubGroups, u8 Copy_u8SubGroupPrioprity, u8 Copy_u8PreemptivePriority);

#endif /* NVIC_H_ */
