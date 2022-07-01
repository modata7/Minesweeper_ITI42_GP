/*
 * STK.c
 *
 *  Created on: Mar 25, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "STK.h"

#include "STK_cfg.h"

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}SysTick_t;

#define	SysTick ((SysTick_t*)0xE000E010)

/* Clock Sources */
#define	AHB_CLK					0x4
#define	AHB_DIV_8_CLK			0x0

#define	SYS_TICK_INT			0x2

#define	SYS_TICK_COUNT_FLAG		0x10000

#define SYS_TICK_START			0x1

static SystickCbf_t APPcbf;

SysTick_tenuErrorStatus SysTick_enuInit(void)
{
	SysTick_tenuErrorStatus Loc_enuErrorStatus = SysTick_enuOK;

	SysTick -> VAL = 0;

	SysTick -> CTRL |= SYSTICK_CLK_SRC;

	SysTick -> CTRL |= SYS_TICK_INT;

	return Loc_enuErrorStatus;
}

void Systick_vidStart()
{
	SysTick -> CTRL |= SYS_TICK_START;
}

SysTick_tenuErrorStatus SysTick_enuSetTickTimems(u32 Copy_u32Ticks)
{
	SysTick_tenuErrorStatus Loc_enuErrorStatus = SysTick_enuOK;

	SysTick -> LOAD = Copy_u32Ticks;

	return Loc_enuErrorStatus;
}

void Systick_vidRegisterCbf(SystickCbf_t Cbf)
{
	if(Cbf)
	{
		APPcbf = Cbf;
	}
}

void SysTick_Handler()
{
	if(APPcbf)
	{
		APPcbf();
	}
}

SysTick_tenuErrorStatus SysTick_enuDelay(u32 Copy_u32Ticks)
{
	SysTick_tenuErrorStatus Loc_enuErrorStatus = SysTick_enuOK;

	SysTick -> LOAD = Copy_u32Ticks;

	SysTick -> CTRL |= SYS_TICK_INT;

	SysTick -> CTRL |= SYS_TICK_START;

	while((SysTick -> CTRL & SYS_TICK_COUNT_FLAG) == 0);

	SysTick -> CTRL &= ~(SYS_TICK_START);

	SysTick -> LOAD = 0;

	SysTick -> VAL = 0;

	return Loc_enuErrorStatus;
}

u32 Systick_u32GetTicksMs(u32 Copy_u32AHB_Clock , u32 Copy_u32TimeMs)
{
	u32 Loc_u32Ticks = ((Copy_u32TimeMs / 1000) * Copy_u32AHB_Clock);

	return Loc_u32Ticks;
}
