/*
 * GPIO.c
 *
 *  Created on: Mar 21, 2022
 *      Author: modata7
 */


#include "STD_TYPES.h"

#include "GPIO.h"

typedef struct
{
	u32	MODER;
	u32	OTYPER;
	u32	OSPEEDR;
	u32	PUPDR;
	u32	IDR;
	u32	ODR;
	u32	BSRR;
	u32	LCKR;
	u32	AFRL;
	u32	AFRH;
}GPIO_t;

/* MASK EL MASK */
#define	IN_OUT_MASK			0x00000003
#define	MODE_MASK			0x0000000C
#define	SPEED_MASK			0x00000030

/* MASK EL MASK EL MASK*/
#define	INPUT_MASK			0x00000000
#define	OUTPUT_MASK			0x00000001
#define	ANALOG_MASK			0x00000003

/* CLEAR MASKS */
#define	DIR_CLEAR_MASK		0x00000003
#define	PP_OD_CLEAR_MASK	0x00000001
#define	PU_PD_CLEAR_MASK	0x00000003
#define	SPEED_CLEAR_MASK	0x00000003

/* PRIVATE DEFINES */
#define	TWO_BIT_SHFT		2
#define	FOUR_BIT_SHFT		4
#define ONE					1

#define NULL 				((void*)0x00)

GPIO_tenumErrorStatus GPIO_enuSetPinMode(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8Mode)
{
	GPIO_tenumErrorStatus Loc_enuErrorStatus = GPIO_enuOK;

	u8 Loc_u8InOut;

	u8 Loc_u8Mode;

	u8 Loc_u8Speed;

	u32 Loc_u32RegTemp;

	u8 Loc_u8PinIndex = 0;

	if(Add_pvidPort != PORTA && Add_pvidPort != PORTB && Add_pvidPort != PORTC)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Copy_u16Pin > GPIO_u8PIN_15)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else
	{
		//Getting the Direction
		Loc_u8InOut = Copy_u8Mode & IN_OUT_MASK;

		//Getting the Mode
		Loc_u8Mode = (Copy_u8Mode & MODE_MASK) >> TWO_BIT_SHFT;

		if(Loc_u8InOut == ANALOG_MASK)
		{
			for(Loc_u8PinIndex = 0 ; Loc_u8PinIndex < 32 ; Loc_u8PinIndex++)
			{
				if( (Copy_u16Pin >> Loc_u8PinIndex) & 1)
				{
					//Setting the MODE
					((volatile GPIO_t*) Add_pvidPort) -> MODER &= ~(DIR_CLEAR_MASK << (Loc_u8PinIndex * TWO_BIT_SHFT));
				}
			}
		}
		else if(Loc_u8InOut == INPUT_MASK)
		{

			for(Loc_u8PinIndex = 0 ; Loc_u8PinIndex < 32 ; Loc_u8PinIndex++)
			{
				if( (Copy_u16Pin >> Loc_u8PinIndex) & 1)
				{
					//Setting the MODE
					((volatile GPIO_t*) Add_pvidPort) -> MODER &= ~(DIR_CLEAR_MASK << (Loc_u8PinIndex * TWO_BIT_SHFT));

					//Setting Pull UP / Pull Down
					Loc_u32RegTemp = ((volatile GPIO_t*) Add_pvidPort) -> PUPDR;

					Loc_u32RegTemp &= ~(PU_PD_CLEAR_MASK << (Loc_u8PinIndex * TWO_BIT_SHFT));

					Loc_u32RegTemp |= (Loc_u8Mode << (Loc_u8PinIndex * TWO_BIT_SHFT));

					((volatile GPIO_t*) Add_pvidPort) -> PUPDR = Loc_u32RegTemp;
				}
			}
		}
		else
		{
			for(Loc_u8PinIndex = 0 ; Loc_u8PinIndex < 32 ; Loc_u8PinIndex++)
			{
				if( (Copy_u16Pin >> Loc_u8PinIndex) & 1)
				{
					//Setting the MODE
					Loc_u32RegTemp = ((volatile GPIO_t*) Add_pvidPort) -> MODER;

					Loc_u32RegTemp &= ~(DIR_CLEAR_MASK << (Loc_u8PinIndex * TWO_BIT_SHFT));

					Loc_u32RegTemp |= (Loc_u8InOut << (Loc_u8PinIndex * TWO_BIT_SHFT));

					((volatile GPIO_t*) Add_pvidPort) -> MODER = Loc_u32RegTemp;

					//Setting Push_PUll / Open Drain
					Loc_u32RegTemp = ((volatile GPIO_t*) Add_pvidPort) -> OTYPER;

					Loc_u32RegTemp &= ~(PP_OD_CLEAR_MASK << Loc_u8PinIndex);

					Loc_u32RegTemp |= (Loc_u8Mode << Loc_u8PinIndex);

					((volatile GPIO_t*) Add_pvidPort) -> OTYPER = Loc_u32RegTemp;

					//Getting the Speed
					Loc_u8Speed = ((Copy_u8Mode & SPEED_MASK) >> FOUR_BIT_SHFT);

					//Setting the Speed
					Loc_u32RegTemp = ((volatile GPIO_t*) Add_pvidPort) -> OSPEEDR;

					Loc_u32RegTemp &= ~(SPEED_CLEAR_MASK << (Loc_u8PinIndex * TWO_BIT_SHFT));

					Loc_u32RegTemp |= (Loc_u8Speed << (Loc_u8PinIndex * TWO_BIT_SHFT));

					((volatile GPIO_t*) Add_pvidPort) -> OSPEEDR = Loc_u32RegTemp;

				}
			}

		}
	}

	return Loc_enuErrorStatus;
}


GPIO_tenumErrorStatus GPIO_enuSetPinValue(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8Value)
{
	GPIO_tenumErrorStatus Loc_enuErrorStatus = GPIO_enuOK;

	if(Add_pvidPort != PORTA && Add_pvidPort != PORTB && Add_pvidPort != PORTC)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Copy_u16Pin > GPIO_u8PIN_15)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Copy_u8Value != GPIO_HIGH && Copy_u8Value != GPIO_LOW)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else
	{

		if(Copy_u8Value == GPIO_HIGH)
		{
			((volatile GPIO_t*) Add_pvidPort) -> ODR |= Copy_u16Pin;
		}
		else
		{
			((volatile GPIO_t*) Add_pvidPort) -> ODR &= ~(Copy_u16Pin);
		}
	}

	return Loc_enuErrorStatus;
}

GPIO_tenumErrorStatus GPIO_enuGetPinValue(void* Add_pvidPort, u16 Copy_u16Pin, pu8 Add_pu8Value)
{
	GPIO_tenumErrorStatus Loc_enuErrorStatus = GPIO_enuOK;

	if(Add_pvidPort != PORTA && Add_pvidPort != PORTB && Add_pvidPort != PORTC)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Copy_u16Pin > GPIO_u8PIN_15)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Add_pu8Value == NULL)
	{
		Loc_enuErrorStatus = GPIO_enuNullPointer;
	}
	else
	{
		if(((volatile GPIO_t*) Add_pvidPort) -> IDR & Copy_u16Pin)
		{
			*Add_pu8Value = GPIO_HIGH;
		}
		else
		{
			*Add_pu8Value = GPIO_LOW;
		}

	}

	return Loc_enuErrorStatus;
}

GPIO_tenumErrorStatus GPIO_enuSetPinAlternateFunction(void* Add_pvidPort, u16 Copy_u16Pin, u8 Copy_u8AFMode)
{
	GPIO_tenumErrorStatus Loc_enuErrorStatus = GPIO_enuOK;

	u8 Loc_u8PinIndex = 0 ;

	if(Add_pvidPort != PORTA && Add_pvidPort != PORTB && Add_pvidPort != PORTC)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else if(Copy_u16Pin > GPIO_u8PIN_15)
	{
		Loc_enuErrorStatus = GPIO_enuInvalideInput;
	}
	else
	{
		if(Copy_u16Pin > GPIO_u8PIN_07)
		{
			for(Loc_u8PinIndex = 0 ; Loc_u8PinIndex < 32 ; Loc_u8PinIndex++)
			{
				if( (Copy_u16Pin >> Loc_u8PinIndex) & 1)
				{
					(((volatile GPIO_t*) Add_pvidPort) -> AFRH) |= (Copy_u8AFMode << ((Loc_u8PinIndex -8) * FOUR_BIT_SHFT));
				}
			}
		}
		else
		{
			for(Loc_u8PinIndex = 0 ; Loc_u8PinIndex < 32 ; Loc_u8PinIndex++)
			{
				if( (Copy_u16Pin >> Loc_u8PinIndex) & 1)
				{
					(((volatile GPIO_t*) Add_pvidPort) -> AFRL) |= (Copy_u8AFMode << (Loc_u8PinIndex * FOUR_BIT_SHFT));
				}
			}
		}
	}

	return Loc_enuErrorStatus;
}
