/*
 * Collection.c
 *
 *  Created on: Jun 23, 2022
 *      Author: WINDOWS
 */

#include "STD_TYPES.h"
#include "Servo.h"
#include "Servo_cfg.h"
#include "HMagnet.h"
#include "HMagnet_cfg.h"
#include "Collection.h"
#include "GPIO.h"



u8 Uart_u8Flag = 0;

void Servo_vidUp(u8 Copy_u8Servo1,u8 Copy_u8Servo2)
{
	Servo_vidSetAngle(Copy_u8Servo1,180);
	Servo_vidSetAngle(Copy_u8Servo2,0);
}
void Servo_vidDown(u8 Copy_u8Servo1,u8 Copy_u8Servo2)
{
	Servo_vidSetAngle(Copy_u8Servo2,180);
	Servo_vidSetAngle(Copy_u8Servo1,0);
}

u8 Servo_vidAuto(u8 Copy_u8Servo1,u8 Copy_u8Servo2)
{
	static u32 state=0;

	if(state < 16000)
	{
		if(state == 0)
		{
			Servo_vidDown(Copy_u8Servo1,Copy_u8Servo2);

			HMagnet_enuMagnetSetState( MAG_1 , HMAG_u8MAG_ON );
		}

		state++;
	}
	else if(state >= 16000 && state < 25000)
	{
		if(state == 16000)
		{
			Servo_vidUp(Copy_u8Servo1,Copy_u8Servo2);
		}
		state++;
	}
	else if(state >= 32000)
	{
		HMagnet_enuMagnetSetState( MAG_1 , HMAG_u8MAG_OFF );
		state = 0;
		return 0;
	}
	else
	{
		state++;
	}
	return 1;
}


void Collection()
{
	static u8 state=0,Gpio_u8Reading;
	if(state == 0)
	{
		GPIO_enuGetPinValue(PORTB, GPIO_u8PIN_01, &Gpio_u8Reading);
		state=Gpio_u8Reading;
		//state = 1;
	}
	else if(state == 1)
	{
		state = Servo_vidAuto(1,0);
		//Servo_vidAuto(0,1);
	}

}
