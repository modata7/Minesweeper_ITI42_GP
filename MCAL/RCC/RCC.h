/*
 * RCC.h
 *
 *  Created on: Mar 21, 2022
 *      Author: modata7
 */

#ifndef RCC_H_
#define RCC_H_


/****************************************************************
=================================================================
				Reset and Clock Control Driver
=================================================================

	Developed by: Mohamed Abdelfatah

	Created on: The big bang

	Version: 1.0002.1.06

	MCU: STM32F104CC

	License: Mashy 7alak

	This Driver is used to Reset the MCU or to Control the system clock

	of the MCU and to control the clock on each peripheral.


*****************************************************************/


/*CLOCK TYPES*/
#define	RCC_HSE_CRYSTAL		0x00010000
#define	RCC_HSE_BYPASS		0x00050000
#define	RCC_HSI				0x00000001
#define	RCC_PLL				0x01000000

/*RCC_ON_OFF*/
#define	RCC_ON				1
#define	RCC_OFF				0

/***********  AHB1 ************/
#define RCC_AHB_GPIOA       0x00000001
#define RCC_AHB_GPIOB       0x00000002
#define RCC_AHB_GPIOC       0x00000004
#define RCC_AHB_GPIOD       0x00000008
#define RCC_AHB_GPIOE       0x00000010
#define RCC_AHB_GPIOH       0x00000080
#define RCC_AHB_CRC         0x00001000
#define RCC_AHB_DMA1        0x00200000
#define RCC_AHB_DMA2        0x00400000
/****************************/

/***********  AHB2 ************/
#define RCC_AHB_OTGFS		0x40000080
/****************************/

/**********  APB1 ************/
#define RCC_APB1_TIMER2     0x80000001
#define RCC_APB1_TIMER3     0x80000002
#define RCC_APB1_TIMER4     0x80000004
#define RCC_APB1_TIMER5     0x80000008
#define RCC_APB1_WWDG     	0x80000800
#define RCC_APB1_SPI2     	0x80004000
#define RCC_APB1_SPI3	    0x80008000
#define RCC_APB1_USART2    	0x80020000
#define RCC_APB1_I2C1	    0x80200000
#define RCC_APB1_I2C2       0x80400000
#define RCC_APB1_I2C3		0x80800000
#define RCC_APB1_PWR		0x90000000
/*****************************/

/**********  APB2 ************/
#define RCC_APB2_TIMER1     0xC0000001
#define RCC_APB2_USART1     0xC0000010
#define RCC_APB2_USART6     0xC0000020
#define RCC_APB2_ADC1  		0xC0000100
#define RCC_APB2_SDIO       0xC0000800
#define RCC_APB2_SPIQ       0xC0001000
#define RCC_APB2_SPI4       0xC0002000
#define RCC_APB2_SYSCFG		0xC0004000
#define RCC_APB2_TIMER9		0xC0010000
#define RCC_APB2_TIMER10	0xC0020000
#define RCC_APB2_TIMER11	0xC0040000
/*****************************/

/******PLL CONFIGIRATIONS******/

/*PLLM CONFIG*/
#define	PLLM_DIV_BY_2	0x00000002
#define	PLLM_DIV_BY_4	0x00000004
#define	PLLM_DIV_BY_8	0x00000008
#define	PLLM_DIV_BY_16	0x00000010
#define	PLLM_DIV_BY_32	0x00000020
#define	PLLM_DIV_BY_63	0x0000003F

/*PLLN CONFIG*/
#define	PLLN_MUL_BY_192		0x00000300
#define	PLLN_MUL_BY_432		0x00006C00

/*PLLP CONFIG*/
#define	PLLP_DIV_BY_2	0x00000000
#define	PLLP_DIV_BY_4	0x00010000
#define	PLLP_DIV_BY_6	0x00020000
#define	PLLP_DIV_BY_8	0x00030000

/*PLLQ CONFIG*/
#define	PLLQ_DIV_BY_2	0x02000000
#define	PLLQ_DIV_BY_3	0x03000000
#define	PLLQ_DIV_BY_4	0x04000000
#define	PLLQ_DIV_BY_5	0x05000000
#define	PLLQ_DIV_BY_6	0x06000000
#define	PLLQ_DIV_BY_7	0x07000000
#define	PLLQ_DIV_BY_8	0x08000000
#define	PLLQ_DIV_BY_9	0x09000000
#define	PLLQ_DIV_BY_10	0x0A000000
#define	PLLQ_DIV_BY_11	0x0B000000
#define	PLLQ_DIV_BY_12	0x0C000000
#define	PLLQ_DIV_BY_13	0x0D000000
#define	PLLQ_DIV_BY_14	0x0E000000
#define	PLLQ_DIV_BY_15	0x0F000000

/*PLL SRC*/
#define	PLL_HSI_SRC				0x00000000
#define	PLL_HSE_SRC				0x00400000

/*********************************/

/*AHB Prescaler*/
#define AHB_PRESCAL_NOT_DIV		0x00000000
#define AHB_PRESCAL_DIV_BY_2	0x00000080
#define AHB_PRESCAL_DIV_BY_4	0x00000090
#define AHB_PRESCAL_DIV_BY_8	0x000000A0
#define AHB_PRESCAL_DIV_BY_16	0x000000B0
#define AHB_PRESCAL_DIV_BY_128	0x000000C0
#define AHB_PRESCAL_DIV_BY_256	0x000000D0
#define AHB_PRESCAL_DIV_BY_512	0x000000F0

/*APB1 Low Speed Prescaler*/
#define	APB1_PRESCAL_NOT_DIV	0x00000000
#define	APB1_PRESCAL_DIV_BY_2	0x00001000
#define	APB1_PRESCAL_DIV_BY_4	0x00001400
#define	APB1_PRESCAL_DIV_BY_8	0x00001800
#define	APB1_PRESCAL_DIV_BY_16	0x00001C00

/*APB2 high Speed Prescaler*/
#define	APB2_PRESCAL_NOT_DIV	0x00000000
#define	APB2_PRESCAL_DIV_BY_2	0x00008000
#define	APB2_PRESCAL_DIV_BY_4	0x0000A000
#define	APB2_PRESCAL_DIV_BY_8	0x0000C000
#define	APB2_PRESCAL_DIV_BY_16	0x0000E000

/*SYSTEM CLOCK SWITCH*/
typedef enum{

	RCC_HSI_SW,

	RCC_HSE_SW,

	RCC_PLL_SW,

	RCC_SW_ERROR

}RCC_tenumSysClockSW;

/*ERROR STATUS*/
typedef enum{

	RCC_enuOK,

	RCC_enuInValidInput,

	RCC_enuClockError,

	RCC_enuPLL_CFG_Error

}RCC_tenumErrorStatus;


/*FUNCTIONS PROTOTYPES*/

/*********************************************************************************************************************************************************
 Function Desciption:
 					 This function Controls the HSI, HSE, PLL clocks by turning them ON or OFF

 Returns:
 					This function returns an error status if any or an ok status that it completed its fuctionality
 First Argument:
 				The Clock Type needed to be controlled:
 															RCC_HSE_CRYSTAL	-------> To Control the High Speed External Clock from a Crystal Oscillator
 					                                        RCC_HSE_BYPASS	-------> To Control the High Speed External Clock from a Bypass
 					                                        RCC_HSI			-------> To Control the High Speed Internal Clock from a RC circuit
 															RCC_PLL			-------> To Control the Phase Locked Loop Clock
 Second Argument:
 						The Clock to be turned ON or OFF:
 															RCC_ON			-------> To turn on the Clock
 															RCC_OFF			-------> To turn off the Clock

 Error Status:
 										The status of the returned error:
 															OK
 															InValidInput
 															ClockError
 															PLL_CFG_Error

*********************************************************************************************************************************************************/
RCC_tenumErrorStatus RCC_enuControlClock(u32 RCC_u32ClockType, u8 RCC_u8On_Off);

RCC_tenumErrorStatus RCC_enuSelectSystemClock(RCC_tenumSysClockSW RCC_enuSysClockType);

RCC_tenumSysClockSW RCC_enuGetSystemClockStatus(void);

/*
Caution for AHB Prescaler:
		The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
		HPRE write.

Caution for APB1 Prescaler:
		The software has to set these bits correctly not to exceed 42 MHz on this domain.
		The clocks are

Caution for APB2 Prescaler:
		The software has to set these bits correctly not to exceed 84 MHz on this domain.
		The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after PPRE2 write.
 */

RCC_tenumErrorStatus RCC_enuConfigBusPreScaler(u32 RCC_u32AHB_PRESCAL, u32 RCC_u32APB1_PRESCAL , u32 RCC_u32APB2_PRESCAL);

/*
Caution:
		The USB OTG FS requires a 48 MHz clock to work correctly. The SDIO and the random
		number generator need a frequency lower than or equal to 48 MHz to work correctly.
 */
RCC_tenumErrorStatus RCC_enuPllConfig(u32 Copy_u32PLLM , u32 Copy_u32PLLN , u32 Copy_u32PLLQ , u32 Copy_u32PLLP , u32 Copy_u32PLLSRC);

RCC_tenumErrorStatus RCC_enuEnablePrephiralClock(u32 Copy_u32PrephiralId);

RCC_tenumErrorStatus RCC_enuDisablePrephiralClock(u32 Copy_u32PrephiralId);


#endif /* RCC_H_ */
