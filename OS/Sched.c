/*
 * Sched.c
 *
 *  Created on: Apr 6, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "STK.h"

#include "Sched.h"

#include "Sched_cfg.h"

extern const Runnabl_t RunnableList[MAX_TASKS_NUM];

static u8 StartSched;

static void TickCbf(void)
{
	StartSched = 1;
}

static void Sched(void)
{
	static u32 Loc_u32TimeMs = 0;

	u32 Loc_u32Index = 0;

	for(Loc_u32Index = 0 ; Loc_u32Index < MAX_TASKS_NUM ; Loc_u32Index++)
	{
		if(Loc_u32TimeMs % RunnableList[Loc_u32Index].CyclicTimeMs == 0)
		{
			RunnableList[Loc_u32Index].Cbf();
		}
	}

	Loc_u32Index += TICK_TIME_MS;
}

void Sched_vidInit(void)
{
	SysTick_enuInit();

	SysTick_enuSetTickTimems(TICK_TIME);

	Systick_vidRegisterCbf(TickCbf);
}

void Sched_vidStart(void)
{
	Systick_vidStart();

	while(1)
	{
		if(StartSched == 1)
		{
			StartSched = 0;

			Sched();
		}
	}
}

