/*
 * Sched_cfg.c
 *
 *  Created on: Apr 6, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "Sched.h"

#include "Sched_cfg.h"

#include "HSwitch.h"

#include "HSwitch_cfg.h"

#include "App_Task.h"

#include "HLcd.h"

#include "HLcd_cfg.h"

#include "HKeypad.h"

#include "HKeypad_cfg.h"

const Runnabl_t RunnableList[MAX_TASKS_NUM] = {

		[Task_1] = {
				.Cbf = App_Task,
				.CyclicTimeMs = 5
		},

		[Task_2] = {
				.Cbf = HKeypad_Task,
				.CyclicTimeMs = 10
		}/*,

		[Task_3] = {
				.Cbf = HSwitch_Task,
				.CyclicTimeMs = 2
		}*/
};
