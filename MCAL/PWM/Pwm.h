/*
 * Pwm.h
 *
 *  Created on: Jun 22, 2022
 *      Author: modata7
 */

#ifndef PWM_H_
#define PWM_H_

typedef struct
{
	void* TimerNumber;
	u8 ChannelNumber;
	u32 Copy_u32Frequency;
	f32 Copy_f32Dutycyle;
}Pwm_tstrCfg;

/*Timers*/
#define TIM1		((void*)0x40010000)
#define TIM2		((void*)0x40000000)
#define TIM3		((void*)0x40000400)
#define TIM4		((void*)0x40000800)
#define TIM5		((void*)0x40000C00)
#define TIM9		((void*)0x40014000)
#define TIM10		((void*)0x40014400)
#define TIM11		((void*)0x40014800)

/*Channels*/
typedef enum
{
	Channel_1,
	Channel_2,
	Channel_3,
	Channel_4
}Pwm_tenuChannels;

/*Functions Prototypes*/
extern void Pwm_vidInit(Pwm_tstrCfg* Add_PstrPwmCfg);

extern void Pwm_vidGeneratePwmSignal(Pwm_tstrCfg* Add_PstrPwmCfg);

#endif /* PWM_H_ */
