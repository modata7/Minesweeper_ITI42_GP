/*
 * Sched.h
 *
 *  Created on: Apr 6, 2022
 *      Author: modata7
 */

#ifndef SCHED_H_
#define SCHED_H_

typedef struct
{
	void (* Cbf)(void);

	u32 CyclicTimeMs;
}Runnabl_t;

void Sched_vidInit(void);

void Sched_vidStart(void);

#endif /* SCHED_H_ */
