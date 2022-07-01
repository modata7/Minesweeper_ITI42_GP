/*
 * Adc.c
 *
 *  Created on: May 18, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"
#include "Adc_cfg.h"
#include "Adc.h"
#include "RCC.h"
#include "GPIO.h"

typedef struct
{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR1;
	volatile u32 JOFR2;
	volatile u32 JOFR3;
	volatile u32 JOFR4;
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR1;
	volatile u32 SQR2;
	volatile u32 SQR3;
	volatile u32 JSQR;
	volatile u32 JDR1;
	volatile u32 JDR2;
	volatile u32 JDR3;
	volatile u32 JDR4;
	volatile u32 DR;
	volatile u32 CCR;
}ADC_t;

typedef enum
{
	NoConversion,
	SingleConversion,
	ConChainConversion
}ADC_tenuConversionFlags;

/*ADC Handler Prototypes*/
void ADC_IRQHandler(void);

/*Private Definitions*/
#define ADC1	((ADC_t*)0x40012000)

#define SCAN_MODE_ENABLE	0x0100
#define ADC_ON				0x01

#define	CONTINUOUS_CONVERSION	0x02
#define	SINGLE_CONVERSION		0xFD

#define END_OF_CONVERSION_INT_ENABLE	0x20
#define START_CONVERSION				0x40000000
#define ONE_CONVERSION					0x00000000
#define FIRST_CONVERSION				0x01

#define START_FLAG						0x02	/*Regular channel start flag*/
#define END_OF_CONVERSION				0x10	/*Regular channel end of conversion*/

#define REG_CHANNEL_SEQ_LEN				20		/*Regular channel sequence length*/

/*Global Variables*/
static u8 ADC_u8SamplingTime;
pu16 ADC_pu16ChannelReading;
static u8 ADC_u8ChainConIndex = 0;
ADC_tenuConversionFlags ADC_enuConvFlag = NoConversion;
u8 ADC_u8BusyFlag = 0;

/*Function Implementations*/
void ADC_vidInit(ADC_tstrInit* hadc)
{
	/*Enable ADC Clock*/
	RCC_enuEnablePrephiralClock(RCC_APB2_ADC1);

	/*ADC prescaler*/
	ADC1 -> CCR |= hadc -> PreScaler;

	/*Data Alignment*/
	ADC1 -> CR2 |= hadc -> DataAlign;

	/*Resolution*/
	ADC1 -> CR1 |= hadc -> Resolution;

	/*Buffer the Sampling Time*/
	ADC_u8SamplingTime = hadc -> SamplingTime;

	/*Scan Mode Enable*/
	ADC1 -> CR1 |= SCAN_MODE_ENABLE;

	//GPIO PINS ANALOG
	//AF ADC
}

u16 ADC_u16SingleConversion(u8 Copy_u8Channel)
{
	/*ADC ON*/
	ADC1 -> CR2 |= ADC_ON;

	/*Single Conversion*/
	ADC1 -> CR2 &= SINGLE_CONVERSION;

	/*Sampling Time*/
	if(Copy_u8Channel > ADC_CHANNEL_09)
	{
		ADC1 -> SMPR1 |= ADC_u8SamplingTime << ((Copy_u8Channel - 10) * 3);
	}
	else
	{
		ADC1 -> SMPR2 |= ADC_u8SamplingTime << (Copy_u8Channel * 3);
	}

	/*One Conversion*/
	ADC1 -> SQR1 = ONE_CONVERSION;

	/*1st conversion in regular sequence*/
	ADC1 -> SQR3 = FIRST_CONVERSION;

	/*Clear The Status Register*/
	ADC1->SR = 0;

	/*Start Conversion*/
	ADC1 -> CR2 |= START_CONVERSION;

	/*Wait for EOC*/
	while( !(ADC1 -> SR & END_OF_CONVERSION) );

	/*Disable ADC*/
	ADC1 -> CR2 &= ~ADC_ON;

	return (ADC1 -> DR);
}

void ADC_vidContinuousConversion(u8 Copy_u8Channel , pu16 Add_pu16AdcChannelReading)
{
	if(ADC_u8BusyFlag == 0)
	{
		ADC_u8BusyFlag = 1;

		/*Raise the Single Conversion Flag*/
		ADC_enuConvFlag = SingleConversion;

		/*ADC ON*/
		ADC1 -> CR2 |= ADC_ON;

		/*Continuous Conversion*/
		ADC1 -> CR2 |= CONTINUOUS_CONVERSION;

		/*Interrupt enable for EOC*/
		ADC1 -> CR1 |= END_OF_CONVERSION_INT_ENABLE;

		ADC_pu16ChannelReading = Add_pu16AdcChannelReading;

		/*Sampling Time*/
		if(Copy_u8Channel > ADC_CHANNEL_09)
		{
			ADC1 -> SMPR1 |= ADC_u8SamplingTime << ((Copy_u8Channel - 10) * 3);
		}
		else
		{
			ADC1 -> SMPR2 |= ADC_u8SamplingTime << (Copy_u8Channel * 3);
		}

		/*One Conversion*/
		ADC1 -> SQR1 = ONE_CONVERSION;

		/*1st conversion in regular sequence*/
		ADC1 -> SQR3 = FIRST_CONVERSION;

		/*Clear The Status Register*/
		ADC1->SR = 0;

		/*Start Conversion*/
		ADC1 -> CR2 |= START_CONVERSION;

	}
	else
	{
		// BUSY
	}
}

void ADC_vidContinuousChainConversion(ADC_tstrAdcChainConversoin* ADC_ChainConArr)
{
	if(ADC_u8BusyFlag == 0)
	{
		ADC_u8BusyFlag = 1;

		u8 Loc_u8ChannelIndex = 0;

		/*Raise the Chain Conversion Flag*/
		ADC_enuConvFlag = ConChainConversion;

		/*ADC ON*/
		ADC1 -> CR2 |= ADC_ON;

		/*Continuous Conversion*/
		ADC1 -> CR2 |= CONTINUOUS_CONVERSION;

		/*Interrupt enable for EOC*/
		ADC1 -> CR1 |= END_OF_CONVERSION_INT_ENABLE;

		/*Number of Conversions*/
		ADC1 -> SQR1 |= MAX_NUM_OF_CHANNELS << REG_CHANNEL_SEQ_LEN;

		for(Loc_u8ChannelIndex = 0 ; Loc_u8ChannelIndex < MAX_NUM_OF_CHANNELS ; Loc_u8ChannelIndex++)
		{
			ADC_pu16ChannelReading[Loc_u8ChannelIndex] = ADC_ChainConArr[Loc_u8ChannelIndex].ReadingValue;

			if(ADC_ChainConArr[Loc_u8ChannelIndex].channel > ADC_CHANNEL_13)
			{
				ADC1 -> SQR1 |= Loc_u8ChannelIndex << ((ADC_ChainConArr[Loc_u8ChannelIndex].channel - 13) * 5);
			}
			else if(ADC_ChainConArr[Loc_u8ChannelIndex].channel > ADC_CHANNEL_06 && ADC_ChainConArr[Loc_u8ChannelIndex].channel < ADC_CHANNEL_13)
			{
				ADC1 -> SQR1 |= Loc_u8ChannelIndex << ((ADC_ChainConArr[Loc_u8ChannelIndex].channel - 7) * 5);
			}
			else if(ADC_ChainConArr[Loc_u8ChannelIndex].channel < ADC_CHANNEL_06)
			{
				ADC1 -> SQR1 |= Loc_u8ChannelIndex << ((ADC_ChainConArr[Loc_u8ChannelIndex].channel - 1) * 5);
			}

			/*Sampling Time*/
			if(ADC_ChainConArr[Loc_u8ChannelIndex].channel > ADC_CHANNEL_09)
			{
				ADC1 -> SMPR1 |= ADC_u8SamplingTime << ((ADC_ChainConArr[Loc_u8ChannelIndex].channel - 10) * 3);
			}
			else
			{
				ADC1 -> SMPR2 |= ADC_u8SamplingTime << (ADC_ChainConArr[Loc_u8ChannelIndex].channel * 3);
			}
		}

		/*Clear The Status Register*/
		ADC1->SR = 0;

		/*Start Conversion*/
		ADC1 -> CR2 |= START_CONVERSION;

	}
	else
	{
		// BUSY
	}
}

void ADC_IRQHandler(void)
{
	if(ADC1 -> SR & END_OF_CONVERSION)
	{
		if(ADC_enuConvFlag == SingleConversion)
		{
			*ADC_pu16ChannelReading = ADC1 -> DR;

			ADC_u8BusyFlag = 0;
		}
		else if(ADC_enuConvFlag == ConChainConversion)
		{
			ADC_pu16ChannelReading[ADC_u8ChainConIndex] = ADC1 -> DR;

			ADC_u8ChainConIndex++;

			if(ADC_u8ChainConIndex == MAX_NUM_OF_CHANNELS)
			{
				ADC_u8ChainConIndex = 0;

				ADC_u8BusyFlag = 0;
			}
		}
	}
}
