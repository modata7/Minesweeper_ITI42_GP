/*
 * Exti.h.c
 *
 *  Created on: Jun 28, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"
#include "Exti.h"

typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_t;


#define EXTI	((EXTI_t*)0x40013C00)


void EXTI_vidInit(EXTI_tstrCfg* ExtiCfg)
{
	EXTI -> IMR |= ExtiCfg -> Line;

	switch(ExtiCfg -> Trigger)
	{
	case RISING_TRIGGER:
		EXTI -> RTSR |= ExtiCfg -> Line;
		break;

	case FALLING_TRIGGER:
		EXTI -> FTSR |= ExtiCfg -> Line;
		break;

	case ON_CHANGE_TRIGGER:
		EXTI -> RTSR |= ExtiCfg -> Line;
		EXTI -> FTSR |= ExtiCfg -> Line;
		break;
	}
}

void EXTI_vidSelectTrigger(EXTI_tstrCfg* ExtiCfg)
{
	EXTI -> IMR |= ExtiCfg -> Line;

	switch(ExtiCfg -> Trigger)
	{
	case RISING_TRIGGER:
		EXTI -> RTSR |= ExtiCfg -> Line;
		break;

	case FALLING_TRIGGER:
		EXTI -> FTSR |= ExtiCfg -> Line;
		break;

	case ON_CHANGE_TRIGGER:
		EXTI -> RTSR |= ExtiCfg -> Line;
		EXTI -> FTSR |= ExtiCfg -> Line;
		break;
	}
}
