/*
 * STK.h
 *
 *  Created on: Mar 25, 2022
 *      Author: modata7
 */

#ifndef STK_H_
#define STK_H_

typedef	void(*SystickCbf_t)(void);

/* Error Status */
typedef enum
{

	SysTick_enuOK,

	SysTick_enuNOK,

	SysTick_enuInvalidInput

}SysTick_tenuErrorStatus;


/* Function Prototypes */

SysTick_tenuErrorStatus SysTick_enuInit(void);

SysTick_tenuErrorStatus SysTick_enuSetTickTimems(u32 Copy_u32Ticks);

void Systick_vidStart();

void Systick_vidRegisterCbf(SystickCbf_t Cbf);

u32 Systick_u32GetTicksMs(u32 Copy_u32AHB_Clock , u32 Copy_u32TimeMs);

SysTick_tenuErrorStatus SysTick_enuDelay(u32 Copy_u32Ticks);


#endif /* STK_H_ */
