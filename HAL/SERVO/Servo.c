/*
 * Servo.c
 *
 *  Created on: Jun 23, 2022
 *      Author: WINDOWS
 */

#include "STD_TYPES.h"
#include "Pwm.h"
#include "Pwm_cfg.h"
#include "Servo.h"
#include "Servo_cfg.h"

extern Servo_cfg Servos[2];

void Servo_vidInit(u8 Copy_u8ServoNum)
{
	Pwm_tstrCfg Pwm_cfg ={
					.TimerNumber=Servos[Copy_u8ServoNum].TimNum,
					.ChannelNumber=Servos[Copy_u8ServoNum].Channel,
					.Copy_u32Frequency=50,
					.Copy_f32Dutycyle=0
			};
	Pwm_vidInit(&Pwm_cfg);
}


void Servo_vidSetAngle(u8 Copy_u8ServoNum,u8 Copy_u8Angle)
{
	Pwm_tstrCfg Pwm_cfg ={
				.TimerNumber=Servos[Copy_u8ServoNum].TimNum,
				.ChannelNumber=Servos[Copy_u8ServoNum].Channel,
				.Copy_u32Frequency=50,
		};

	Pwm_vidInit(&Pwm_cfg);

	if(Copy_u8Angle==0)
	{
		Pwm_cfg.Copy_f32Dutycyle=1;
	}
	else if(Copy_u8Angle==90)
	{
		Pwm_cfg.Copy_f32Dutycyle=2.5;
	}
	else if(Copy_u8Angle==180)
	{
		Pwm_cfg.Copy_f32Dutycyle=4;
	}
	Pwm_vidGeneratePwmSignal(&Pwm_cfg);
}

