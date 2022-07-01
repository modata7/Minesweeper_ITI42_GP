/*
 * Pwm.c
 *
 *  Created on: Jun 22, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "Pwm.h"
#include "Pwm_cfg.h"

/*Register Definitions*/
typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RCR;
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 BDTR;
	volatile u32 DCR;
	volatile u32 DMAR;
}PWM_t;

#define NULL ((void*)0x00)

#define TIM_CR1_ARPE	0x80
#define TIM_BDTR_MOE	0x8000
#define TIM_CR1_CEN		0x01
#define TIM_CR1_DIR_UPCOUNTER	0xFFEF
#define TIM_CR1_CMS_EDGE_ALIGNED	0xFF9F

#define TIM_CCMR1_CC1S_OUTPUT 0xFFFC
#define TIM_CCMR1_OC1PE		0x08
#define TIM_CCMR1_OC1M_PWM_MODE_1 0x60

#define TIM_CCER_CC1P	0xFD
#define TIM_CCER_CC1E	0x01
#define TIM_EGR_UG		0x01

#define TIM_CCMR1_CC2S_OUTPUT	0xFCFF
#define TIM_CCMR1_OC2PE			0x0800
#define TIM_CCMR1_OC2M_PWM_MODE_1	0x6000
#define TIM_CCER_CC2P			0xFFDF
#define TIM_CCER_CC2E			0x0010

void Pwm_vidInit(Pwm_tstrCfg* Add_PstrPwmCfg)
{
	if(Add_PstrPwmCfg != NULL)
	{
		switch((u32)Add_PstrPwmCfg -> TimerNumber)
		{
		case (u32)TIM1:
				/*Enable Clock*/
				RCC_enuEnablePrephiralClock(RCC_APB2_TIMER1);

		switch(Add_PstrPwmCfg -> ChannelNumber)
		{
		RCC_enuEnablePrephiralClock(RCC_AHB_GPIOA);
		case Channel_1:
			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_08, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin8 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_08, AF01_TIM1_2);

			break;
		case Channel_2:
			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_09, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin9 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_09, AF01_TIM1_2);

			break;

		case Channel_3:
			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_10, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin10 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_10, AF01_TIM1_2);

			break;

		case Channel_4:
			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_11, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin11 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_11, AF01_TIM1_2);

			break;
		}
		break;
		case (u32)TIM2:
				/*Enable Clock*/
				RCC_enuEnablePrephiralClock(RCC_APB1_TIMER2);

		switch(Add_PstrPwmCfg -> ChannelNumber)
		{
		case Channel_1:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOA);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_15, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin15 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_15, AF01_TIM1_2);

			break;
		case Channel_2:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_03, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin3 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_03, AF01_TIM1_2);

			break;

		case Channel_3:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_10, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin10 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_10, AF01_TIM1_2);

			break;

		case Channel_4:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_01, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTA, GPIO_u8PIN_01, AF01_TIM1_2);

			break;
		}
		break;
		case (u32)TIM3:
				/*Enable Clock*/
				RCC_enuEnablePrephiralClock(RCC_APB1_TIMER3);

		switch(Add_PstrPwmCfg -> ChannelNumber)
		{
		case Channel_1:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_04, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin4 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_04, AF02_TIM3_5);

			break;
		case Channel_2:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_05, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin5 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_05, AF02_TIM3_5);

			break;

		case Channel_3:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_00, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin0 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_00, AF02_TIM3_5);

			break;

		case Channel_4:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_01, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin1 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_01, AF02_TIM3_5);

			break;
		}


		break;
		case (u32)TIM4:
				/*Enable Clock*/
				RCC_enuEnablePrephiralClock(RCC_APB1_TIMER4);

		switch(Add_PstrPwmCfg -> ChannelNumber)
		{
		case Channel_1:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTB, GPIO_u8PIN_06, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin6 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_06, AF02_TIM3_5);

			break;
		case Channel_2:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_07, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin7 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_07, AF02_TIM3_5);

			break;

		case Channel_3:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_08, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin8 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_08, AF02_TIM3_5);

			break;

		case Channel_4:
			RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);

			/*Set Mode to Alternate Function*/
			GPIO_enuSetPinMode(PORTA, GPIO_u8PIN_09, OUTPUT_VERY_HIGH_SPEED_AF_PP);

			/*Set Pin9 to Timer AF*/
			GPIO_enuSetPinAlternateFunction(PORTB, GPIO_u8PIN_09, AF02_TIM3_5);

			break;
		}
		break;
		case (u32)TIM5:
				/*Enable Clock*/
				RCC_enuEnablePrephiralClock(RCC_APB1_TIMER5);

		/*Will Developed If Needed*/
		break;
		}
	}
	else
	{
		//error
	}
}

void Pwm_vidGeneratePwmSignal(Pwm_tstrCfg* Add_PstrPwmCfg)
{
	if(Add_PstrPwmCfg != NULL)
	{
		/* Enable Auto-reload preload */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CR1 |= TIM_CR1_ARPE;

		/* Set counter direction as up-counter */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) ->CR1 &= TIM_CR1_DIR_UPCOUNTER | TIM_CR1_CMS_EDGE_ALIGNED;

		/* Set timer Prescaler */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> PSC = PRE_SCALER_VALUE - 1;

		/* Set timer auto reload value */
		//((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> ARR = 999;
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> ARR = ((TIMER_FREQUENCY / Add_PstrPwmCfg -> Copy_u32Frequency) / PRE_SCALER_VALUE) - 1;

		/* Set Duty Cycle */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCR1 = Add_PstrPwmCfg -> Copy_f32Dutycyle * Add_PstrPwmCfg -> Copy_u32Frequency;

		switch(Add_PstrPwmCfg -> ChannelNumber)
		{
		case Channel_1:
			/* Set Capture/Compare 1 as output */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 &= TIM_CCMR1_CC1S_OUTPUT;

			/* Output Compare 1 preload enable */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 |= TIM_CCMR1_OC1PE;

			/* Select Output Compare 1 PWM mode 1
			 * TIMx_CNT < TIMx_CCR1 -> Output Active
			 * TIMx_CNT >= TIMx_CCR1 -> Output Inactive */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 |= TIM_CCMR1_OC1M_PWM_MODE_1;

			/* Select Capture/Compare 1 output polarity active high */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCER &= TIM_CCER_CC1P;

			/* Initialize all the registers */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> EGR |= TIM_EGR_UG;

			/* Enable Capture/Compare 1 output */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCER |= TIM_CCER_CC1E;

			break;

		case Channel_2:
			/* Set Capture/Compare 2 as output */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 &= TIM_CCMR1_CC2S_OUTPUT;

			/* Output Compare 2 preload enable */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 |= TIM_CCMR1_OC2PE;

			/* Select Output Compare 2 PWM mode 1
			 * TIMx_CNT < TIMx_CCR1 -> Output Active
			 * TIMx_CNT >= TIMx_CCR1 -> Output Inactive */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCMR1 |= TIM_CCMR1_OC2M_PWM_MODE_1;

			/* Select Capture/Compare 2 output polarity active high */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCER &= TIM_CCER_CC2P;

			/* Initialize all the registers */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> EGR |= TIM_EGR_UG;

			/* Enable Capture/Compare 2 output */
			((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CCER |= TIM_CCER_CC2E;

			break;

		case Channel_3:

			/*Will Developed If Needed*/

			break;

		case Channel_4:

			/*Will Developed If Needed*/

			break;
		}


		/* Enable timer main output */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> BDTR |= TIM_BDTR_MOE;

		/* Enable TIMER */
		((volatile PWM_t*)(Add_PstrPwmCfg) -> TimerNumber) -> CR1 |= TIM_CR1_CEN;
	}
	else
	{
		//Error
	}
}
