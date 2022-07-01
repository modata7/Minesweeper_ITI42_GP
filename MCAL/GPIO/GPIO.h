/*
 * GPIO.h
 *
 *  Created on: Mar 21, 2022
 *      Author: modata7
 */

#ifndef GPIO_H_
#define GPIO_H_


/* PINS */
#define	GPIO_u8PIN_00		((u16) 0x0001)
#define	GPIO_u8PIN_01		((u16) 0x0002)
#define	GPIO_u8PIN_02		((u16) 0x0004)
#define	GPIO_u8PIN_03		((u16) 0x0008)
#define	GPIO_u8PIN_04		((u16) 0x0010)
#define	GPIO_u8PIN_05		((u16) 0x0020)
#define	GPIO_u8PIN_06		((u16) 0x0040)
#define	GPIO_u8PIN_07		((u16) 0x0080)
#define	GPIO_u8PIN_08		((u16) 0x0100)
#define	GPIO_u8PIN_09		((u16) 0x0200)
#define	GPIO_u8PIN_10		((u16) 0x0400)
#define	GPIO_u8PIN_11		((u16) 0x0800)
#define	GPIO_u8PIN_12		((u16) 0x1000)
#define	GPIO_u8PIN_13		((u16) 0x2000)
#define	GPIO_u8PIN_14		((u16) 0x4000)
#define	GPIO_u8PIN_15		((u16) 0x8000)

/*************************************************/

/* PORTS */
#define	PORTA		((void*)0x40020000)
#define	PORTB		((void*)0x40020400)
#define	PORTC		((void*)0x40020800)

/*************************************************/

/* MODES */
#define	INPUT_FLOATING					((u8)0x00)
#define	INPUT_PULL_UP					((u8)0x04)
#define	INPUT_PULL_DOWN					((u8)0x08)

#define	OUTPUT_LOW_SPEED_PP				((u8)0x01)
#define	OUTPUT_LOW_SPEED_OD				((u8)0x05)
#define	OUTPUT_LOW_SPEED_AF_PP			((u8)0x02)
#define	OUTPUT_LOW_SPEED_AF_OD			((u8)0x06)

#define	OUTPUT_MED_SPEED_PP				((u8)0x11)
#define	OUTPUT_MED_SPEED_OD				((u8)0x15)
#define	OUTPUT_MED_SPEED_AF_PP			((u8)0x12)
#define	OUTPUT_MED_SPEED_AF_OD			((u8)0x16)

#define	OUTPUT_HIGH_SPEED_PP			((u8)0x21)
#define	OUTPUT_HIGH_SPEED_OD			((u8)0x25)
#define	OUTPUT_HIGH_SPEED_AF_PP			((u8)0x22)
#define	OUTPUT_HIGH_SPEED_AF_OD			((u8)0x26)

#define	OUTPUT_VERY_HIGH_SPEED_PP		((u8)0x31)
#define	OUTPUT_VERY_HIGH_SPEED_OD		((u8)0x35)
#define	OUTPUT_VERY_HIGH_SPEED_AF_PP	((u8)0x32)
#define	OUTPUT_VERY_HIGH_SPEED_AF_OD	((u8)0x36)

#define	INPUT_OUTPUT_ANALOG				((u8)0x03)

/*************************************************/
/* ALTERNATE FUNCTION MODES */
#define	AF00_SYSTEM		0
#define	AF01_TIM1_2		1
#define	AF02_TIM3_5		2
#define	AF03_TIM9_11	3
#define	AF04_I2C1_3		4
#define	AF05_SPI1_4		5
#define	AF06_SPI3		6
#define	AF07_USART1_2	7
#define	AF08_USART6		8
#define	AF09_I2C2_3		9
#define	AF10_OTG_FS		10
#define	AF11			11
#define	AF12_SDIO		12
#define	AF13			13
#define	AF14			14
#define	AF15_EVENTOUT	15

/*************************************************/


/* OUTPUT VALUES */
#define	GPIO_LOW	0
#define	GPIO_HIGH	1

/* ERROR STATUS */
typedef enum
{
	GPIO_enuOK,

	GPIO_enuNOK,

	GPIO_enuInvalideInput,

	GPIO_enuNullPointer

}GPIO_tenumErrorStatus;

/*************************************************/

/* FUNCTION PROTOTYPES */

//GPIO_tenumErrorStatus GPIO_enuInit();

GPIO_tenumErrorStatus GPIO_enuSetPinMode(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8Mode);

GPIO_tenumErrorStatus GPIO_enuSetPinValue(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8Value);

GPIO_tenumErrorStatus GPIO_enuGetPinValue(void* Add_pvidPort, u16 Copy_u16Pin, pu8 Add_pu8Value);

GPIO_tenumErrorStatus GPIO_enuSetPinAlternateFunction(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8AFMode);



#endif /* GPIO_H_ */
