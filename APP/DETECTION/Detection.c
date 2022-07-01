/*
 * Detection.c
 *
 *  Created on: Jun 27, 2022
 *      Author: Ahmed Soliman
 */

#include "STD_TYPES.h"
#include "Detection.h"
#include "GPIO.h"
#include "RCC.h"




void initPins(void)
{
	/*Initialization Phase*/
	/*Enable the GPIOA Peripheral Clock*/
	RCC_enuEnablePrephiralClock(RCC_EN_PORT);

	/*Detection And Proximity Pins*/
	GPIO_enuSetPinMode(DETECT_PORT,detectionPIN,INPUT_PULL_DOWN);
	GPIO_enuSetPinMode(DETECT_PORT,proximityPIN,INPUT_PULL_DOWN);

	/*Buzzer Pin as an output*/
	GPIO_enuSetPinMode(DETECT_PORT,buzzerPIN,OUTPUT_HIGH_SPEED_PP);
	/*INIT State of the PIN*/
	GPIO_enuSetPinValue(DETECT_PORT,buzzerPIN,BUZZER_OFF);
}

void DetectionTask(void)
{

	/*Noise Flag*/
	static u16 Local_u8calibrationFlag;



	/*In case of the Two Sensor gives Digital Value -----> 0 , 1*/
	/*0 -------- > No Action*/
	/*1 -------- > Action*/
	/*Synchronous Functions*/
	GPIO_enuGetPinValue(DETECT_PORT,detectionPIN,&detectionVar);
	GPIO_enuGetPinValue(DETECT_PORT,proximityPIN,&proximityVar);


	if(detectionVar == DETECTED)
	{
		/*Increment of the Calibration Flag for Filtration of Noise*/
		Local_u8calibrationFlag++;
		//trace_printf("SURFACE MINE");
		if(proximityVar == SURFACE)
		{

		}
		else
		{
			/*Increment of the Calibration Flag for Filtration of Noise*/
			Local_u8calibrationFlag++;
			//trace_printf("UNDERGROUND MINE");
		}
	}
	else
	{
		/*reset of the Noise Flag back to zero because it was a noise detected not a real Mine*/
		Local_u8calibrationFlag = 0;
		//trace_printf("NOISE");
	}
	/**After 500 times of the Detection sensor signal, it will make sure that is the mine**/
	if(Local_u8calibrationFlag >= CALIBRATIONLIMIT)
	{
		/*Activate Buzzer*/
		GPIO_enuSetPinValue(DETECT_PORT,buzzerPIN,BUZZER_OFF);	//Relay : Active LOW
	}
	else
	{
		/*DeActivate Buzzer*/
		GPIO_enuSetPinValue(DETECT_PORT,buzzerPIN,BUZZER_ON);
	}

}//End of Function





