/*
 * HMagnet_cfg.c
 *
 *  Created on: Mar 25, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "GPIO.h"

#include "HMagnet.h"

#include "HMagnet_cfg.h"

const Magnet_tenuCfg Magnets[NUM_OF_MAGS] = {

				 [MAG_1] = {
						 .Port = PORTB,
						 .Pin = GPIO_u8PIN_05,
						 .Mode = OUTPUT_VERY_HIGH_SPEED_PP,
						 .Active_Status = ACTIVE_LOW
				 },

//				 [MAG_2] = {
//						 .Port = PORTA,
//						 .Pin = GPIO_u8PIN_01,
//						 .Mode = OUTPUT_VERY_HIGH_SPEED_PP,
//						 .Active_Status = ACTIVE_HIGH
//				 			}
};
