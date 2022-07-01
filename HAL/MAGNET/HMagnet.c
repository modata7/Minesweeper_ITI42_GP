/*
 * HMagnet.c
 *
 *  Created on: Mar 25, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "GPIO.h"

#include "HMagnet.h"

#include "HMagnet_cfg.h"


extern Magnet_tenuCfg Magnets[NUM_OF_MAGS];

HMagnet_tenuErrorStatus HMagnet_enuMagnetInit(void)
{
	HMagnet_tenuErrorStatus Loc_enuErrorStatus = HMagnet_enuOK;

	u8 Loc_u8Iterator = 0;

	for(Loc_u8Iterator = 0 ; Loc_u8Iterator < NUM_OF_MAGS ; Loc_u8Iterator++)
	{
		GPIO_enuSetPinMode( Magnets[Loc_u8Iterator].Port , Magnets[Loc_u8Iterator].Pin , Magnets[Loc_u8Iterator].Mode );
	}

	return Loc_enuErrorStatus;
}

HMagnet_tenuErrorStatus HMagnet_enuMagnetSetState(u8 Copy_u8MagnetNum , u8 Copy_u8MagnetState)
{
	HMagnet_tenuErrorStatus Loc_enuErrorStatus = HMagnet_enuOK;

	GPIO_enuSetPinValue( Magnets[Copy_u8MagnetNum].Port , Magnets[Copy_u8MagnetNum].Pin , (Magnets[Copy_u8MagnetNum].Active_Status ^ Copy_u8MagnetState));

	return Loc_enuErrorStatus;
}

