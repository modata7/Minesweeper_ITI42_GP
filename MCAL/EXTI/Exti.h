/*
 * Exti.h
 *
 *  Created on: Jun 28, 2022
 *      Author: modata7
 */

#ifndef EXTI_H_
#define EXTI_H_

typedef struct
{
	u32 Line;
	u32 Trigger;
}EXTI_tstrCfg;

/*LINE*/
#define EXTI_00	0x0001
#define EXTI_01	0x0002
#define EXTI_02	0x0004
#define EXTI_03	0x0008
#define EXTI_04	0x0010
#define EXTI_05	0x0020
#define EXTI_06	0x0040
#define EXTI_07	0x0080
#define EXTI_08	0x0100
#define EXTI_09	0x0200
#define EXTI_10	0x0400
#define EXTI_11	0x0800
#define EXTI_12	0x1000
#define EXTI_13	0x2000
#define EXTI_14	0x4000
#define EXTI_15	0x8000

/*TRIGGER*/
#define RISING_TRIGGER		0
#define FALLING_TRIGGER		1
#define ON_CHANGE_TRIGGER	2

/*FUNCTIONS PROTOTYPES*/
void EXTI_vidInit(EXTI_tstrCfg* ExtiCfg);

void EXTI_vidSelectTrigger(EXTI_tstrCfg* ExtiCfg);

#endif /* EXTI_H_ */
