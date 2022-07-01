/*
 * Adc.h
 *
 *  Created on: May 18, 2022
 *      Author: modata7
 */

#ifndef ADC_H_
#define ADC_H_

typedef struct
{
	u32 PreScaler;
	u16 DataAlign;
	u8 SamplingTime;
	u32 Resolution;
}ADC_tstrInit;

typedef struct
{
	u8 channel;
	pu16 ReadingValue;
}ADC_tstrAdcChainConversoin;

/*ADC prescaler*/
#define PCLK2	0x00000000
#define PCLK4	0x00010000
#define PCLK6	0x00020000
#define PCLK8	0x00040000

/*Data Alignment*/
#define RIGHT_ALIGN	0x0000
#define LEFT_ALIGN	0x0800

/*Sampling Time*/
#define _3_CYCLES	0x00
#define _15_CYCLES	0x01
#define _28_CYCLES	0x02
#define _56_CYCLES	0x03
#define _84_CYCLES	0x04
#define _112_CYCLES	0x05
#define _144_CYCLES	0x06
#define _480_CYCLES	0x07

/*Resolution*/
#define	_12_BIT	0x00000000
#define	_10_BIT	0x01000000
#define	_8_BIT	0x02000000
#define	_6_BIT	0x04000000

/*ADC Channels*/
#define ADC_CHANNEL_00	0
#define ADC_CHANNEL_01 	1
#define ADC_CHANNEL_02 	2
#define ADC_CHANNEL_03 	3
#define ADC_CHANNEL_04 	4
#define ADC_CHANNEL_05 	5
#define ADC_CHANNEL_06 	6
#define ADC_CHANNEL_07 	7
#define ADC_CHANNEL_08 	8
#define ADC_CHANNEL_09 	9
#define ADC_CHANNEL_10	10
#define ADC_CHANNEL_11	11
#define ADC_CHANNEL_12	12
#define ADC_CHANNEL_13	13
#define ADC_CHANNEL_14	14
#define ADC_CHANNEL_15	15
#define ADC_CHANNEL_16	16
#define ADC_CHANNEL_17	17
#define ADC_CHANNEL_18	18

/*Function Prototypes*/
void ADC_vidInit(ADC_tstrInit* hadc);

u16 ADC_u16SingleConversion(u8 Copy_u8Channel);

void ADC_vidContinuousConversion(u8 Copy_u8Channel , pu16 Add_pu16AdcChannelReading);

void ADC_vidContinuousChainConversion(ADC_tstrAdcChainConversoin* ADC_ChainConArr);

#endif /* ADC_H_ */
