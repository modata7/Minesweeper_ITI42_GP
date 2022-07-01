/*
 * Servo_cfg.c
 *
 *  Created on: Jun 23, 2022
 *      Author: WINDOWS
 */

#include "STD_TYPES.h"
#include "Pwm.h"
#include "Pwm_cfg.h"
#include "Servo.h"
#include "Servo_cfg.h"

Servo_cfg Servos[2] ={
		[0]={
				.TimNum=TIM3,
				.Channel=Channel_1
		},
		[1]={
				.TimNum=TIM4,
				.Channel=Channel_1
			}
};
