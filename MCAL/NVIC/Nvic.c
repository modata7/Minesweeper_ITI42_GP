/*
 * Nvic.c
 *
 *  Created on: Mar 28, 2022
 *      Author: modata7
 */

#include "STD_TYPES.h"

#include "Nvic.h"

typedef struct
{
	u32 ISER[8];

	u32 RES0[24];

	u32 ICER[8];

	u32 RES1[24];

	u32 ISPR[8];

	u32 RES2[24];

	u32 ICPR[8];

	u32 RES3[24];

	u32 IABR[8];

	u32 RES4[56];

	u8 IPR[240];

	u32 RES5[644];

	u32 STIR;

}NVIC_t;

#define NVIC ((NVIC_t*)0xE000E100)

#define SCB_AIRCR *((u32*)0xE000ED0C)

#define	REGISTER_SIZE	32

#define	REGISTER_IPR	4

#define	MAX_PRIPH_NUM	84

#define IPR_CLR_MASK	0xFF

NVIC_tenuErrorStatus NVIC_enuControlInterupt(u32 Copy_u32Peripheral , u8 Copy_u8OnOff)
{
	NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;

	u8 Loc_u8PeripheralRegIndex = Copy_u32Peripheral / REGISTER_SIZE;

	u8 Loc_u8PeripheralIndex = Copy_u32Peripheral % REGISTER_SIZE;

	if(Copy_u32Peripheral > MAX_PRIPH_NUM)
	{
		Loc_enuErrorStatus = NVIC_enuNOK;
	}
	else if(Copy_u8OnOff != NVIC_u8ENABLE && Copy_u8OnOff != NVIC_u8DISABLE)
	{
		Loc_enuErrorStatus = NVIC_enuNOK;
	}
	else
	{
		switch(Copy_u8OnOff)
		{
		case NVIC_u8ENABLE:

			NVIC -> ISER[Loc_u8PeripheralRegIndex] = 1 << Loc_u8PeripheralIndex;

			break;

		case NVIC_u8DISABLE:

			NVIC -> ICER[Loc_u8PeripheralRegIndex] = 1 << Loc_u8PeripheralIndex;

			break;
		}
	}

	return Loc_enuErrorStatus;
}

NVIC_tenuErrorStatus NVIC_enuSetPriority(u32 Copy_u32Peripheral , u8 Copy_u8Priority)
{
	NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;

	u32 Loc_u32IPR_Temp = 0;

	if(Copy_u32Peripheral > MAX_PRIPH_NUM)
	{
		Loc_enuErrorStatus = NVIC_enuNOK;
	}
	else
	{
		Loc_u32IPR_Temp = Copy_u8Priority;

		NVIC -> IPR[Copy_u32Peripheral] = Loc_u32IPR_Temp;
	}

	return Loc_enuErrorStatus;
}

NVIC_tenuErrorStatus NVIC_enuSetSubGroupPriority(u32 Copy_u32SubGroupPriority)
{
	NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;

	if(Copy_u32SubGroupPriority < NVIC_GROUP_4_SUB_0 || Copy_u32SubGroupPriority > NVIC_GROUP_0_SUB_4)
	{
		Loc_enuErrorStatus = NVIC_enuInvalidInput;
	}
	else
	{
		SCB_AIRCR |= Copy_u32SubGroupPriority;
	}

	return Loc_enuErrorStatus;
}

NVIC_tenuErrorStatus NVIC_enuControlPending(u32 Copy_u32Peripheral , u8 Copy_u8OnOff)
{
	NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;

	u8 Loc_u8PeripheralRegIndex = Copy_u32Peripheral / REGISTER_SIZE;

	u8 Loc_u8PeripheralIndex = Copy_u32Peripheral % REGISTER_SIZE;

	if(Copy_u32Peripheral > MAX_PRIPH_NUM)
	{
		Loc_enuErrorStatus = NVIC_enuNOK;
	}
	else if(Copy_u8OnOff != NVIC_u8ENABLE && Copy_u8OnOff != NVIC_u8DISABLE)
	{
		Loc_enuErrorStatus = NVIC_enuNOK;
	}
	else
	{
		switch(Copy_u8OnOff)
		{
		case NVIC_u8ENABLE:

			NVIC -> ISPR[Loc_u8PeripheralRegIndex] = 1 << Loc_u8PeripheralIndex;

			break;

		case NVIC_u8DISABLE:

			NVIC -> ICPR[Loc_u8PeripheralRegIndex] = 1 << Loc_u8PeripheralIndex;

			break;
		}
	}

	return Loc_enuErrorStatus;
}

NVIC_tenuActiveStatus NVIC_enuGetActiveStatus(u32 Copy_u32Peripheral)
{
	NVIC_tenuActiveStatus Loc_enuActiveStatus = NVIC_enuError;

	u8 Loc_u8PeripheralRegIndex = Copy_u32Peripheral / REGISTER_SIZE;

	u8 Loc_u8PeripheralIndex = Copy_u32Peripheral % REGISTER_SIZE;

	if(Copy_u32Peripheral > MAX_PRIPH_NUM)
	{
		Loc_enuActiveStatus = NVIC_enuError;
	}
	else
	{
		Loc_enuActiveStatus = ((NVIC -> IABR[Loc_u8PeripheralRegIndex]) >> Loc_u8PeripheralIndex) & 1;
	}

	return Loc_enuActiveStatus;
}

u8 NVIC_u8GetEncodingPriority(u8 Copy_u8NumberOfSubGroups, u8 Copy_u8SubGroupPrioprity, u8 Copy_u8PreemptivePriority)
{
	u8 Loc_u8Priority = 0;

	if(Copy_u8NumberOfSubGroups <= 4)
	{
		Loc_u8Priority |= (Copy_u8SubGroupPrioprity << 4) | (Copy_u8PreemptivePriority << (4 + Copy_u8NumberOfSubGroups));
	}

	return Loc_u8Priority;
}


