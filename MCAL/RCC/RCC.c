

#include "STD_TYPES.h"

#include "RCC.h"

/* REGISTER DEFINTIONS */
#define		CR				*((volatile u32* const)0x40023800)
#define		PLLCFGR			*((volatile u32* const)0x40023804)
#define		CFGR			*((volatile u32* const)0x40023808)
#define		CIR				*((volatile u32* const)0x4002380C)
#define		AHB1RSTR		*((volatile u32* const)0x40023810)
#define		AHB2RSTR		*((volatile u32* const)0x40023814)
#define		APB1RSTR		*((volatile u32* const)0x40023820)
#define		APB2RSTR		*((volatile u32* const)0x40023824)
#define		AHB1ENR			*((volatile u32* const)0x40023830)
#define		AHB2ENR			*((volatile u32* const)0x40023834)
#define		APB1ENR			*((volatile u32* const)0x40023840)
#define		APB2ENR			*((volatile u32* const)0x40023844)
#define		AHB1LPENR		*((volatile u32* const)0x40023850)
#define		AHB2LPENR		*((volatile u32* const)0x40023854)
#define		APB1LPENR		*((volatile u32* const)0x40023860)
#define		APB2LPENR		*((volatile u32* const)0x40023864)
#define		BDCR			*((volatile u32* const)0x40023870)
#define		CSR				*((volatile u32* const)0x40023874)
#define		SSCGR			*((volatile u32* const)0x40023880)
#define		PLLI2SCFGR		*((volatile u32* const)0x40023884)
#define		DCKCFGR			*((volatile u32* const)0x4002388C)

/*
typedef	struct{

	volatile u32 	CR			;
    volatile u32 	PLLCFGR		;
    volatile u32 	CFGR		;
    volatile u32 	CIR			;
    volatile u32 	AHB1RSTR	;
    volatile u32 	AHB2RSTR	;
			 u32	RES0[2]		;
    volatile u32 	APB1RSTR	;
    volatile u32 	APB2RSTR	;
			 u32	RES1[2]		;
    volatile u32 	AHB1ENR		;
    volatile u32 	AHB2ENR		;
			 u32	RES2[2]		;
    volatile u32 	APB1ENR		;
    volatile u32 	APB2ENR		;
			 u32	RES3[2]		;
    volatile u32 	AHB1LPENR	;
    volatile u32 	AHB2LPENR	;
			 u32	RES4[2]		;
    volatile u32 	APB1LPENR	;
    volatile u32 	APB2LPENR	;
			 u32	RES5[2]		;
    volatile u32 	BDCR		;
    volatile u32 	CSR			;
			 u32	RES6[2]		;
    volatile u32 	SSCGR		;
    volatile u32 	PLLI2SCFGR	;
			 u32	RES7		;
    volatile u32 	DCKCFGR
}RCC_t;


#define	RCC	((volatile RCC_t*)0x40023800)
 */

/*CLOCK READY*/
#define	RCC_HSE_RDY		0x00020000
#define	RCC_HSI_RDY		0x00000002
#define	RCC_PLL_RDY		0x02000000


/*BUS ID MASK*/
#define BUS_ID_MASK    	0xC0000000

/* BUS ID */
#define	RCC_AHB1		0x00000000
#define	RCC_AHB2		0x40000000
#define	RCC_APB1		0x80000000
#define	RCC_APB2		0xC0000000

/* SYSTEM CLOCK SWITCH STATUS */
#define	RCC_SWS			0x0000000C

/*RCC SWS MASKS*/
#define	RCC_HSI_SWS	0x00000000
#define	RCC_HSE_SWS	0x00000004
#define	RCC_PLL_SWS	0x00000008

#define	MAX_NUM_PRIPH	0xC0040000

#define WAIT_INSTRUCTIONS	50

#define PLL_RESET_REG		0x20000000

#define TWO_BITS_SHIFT		2

#define CLOCK_TYPES_NUM		2


RCC_tenumErrorStatus RCC_enuControlClock(u32 RCC_u32ClockType, u8 RCC_u8On_Off)
{
	u8 Loc_u8TimeOut = WAIT_INSTRUCTIONS;

	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuClockError;

	if(RCC_u32ClockType != RCC_HSI && RCC_u32ClockType != RCC_HSE_CRYSTAL && RCC_u32ClockType != RCC_HSE_BYPASS  && RCC_u32ClockType != RCC_PLL)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else if(RCC_u8On_Off != RCC_ON && RCC_u8On_Off != RCC_OFF)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{
		switch(RCC_u8On_Off)
		{
		case RCC_ON:
			switch(RCC_u32ClockType)
			{
			case RCC_HSI:

				//Turn HSI ON
				CR |= RCC_u32ClockType;

				//Wait for the Ready Flag
				while(Loc_u8TimeOut && !(CR & RCC_HSI_RDY))
				{
					Loc_u8TimeOut--;
				}

				//Check if the Clock is Ready
				if(CR & RCC_HSI_RDY)
				{
					Loc_enuErrorStatus = RCC_enuOK;
				}

				break;

			case RCC_HSE_CRYSTAL:

				//Turn HSE Crystal ON
				CR |= RCC_u32ClockType;

				//Wait for the Ready Flag
				while(Loc_u8TimeOut && !(CR & RCC_HSE_RDY))
				{
					Loc_u8TimeOut--;
				}

				//Check if the Clock is Ready
				if(CR & RCC_HSE_RDY)
				{
					Loc_enuErrorStatus = RCC_enuOK;
				}

				break;

			case RCC_HSE_BYPASS:

				//Turn HSE ByPass ON
				CR |= RCC_u32ClockType;

				//Wait for the Ready Flag
				while(Loc_u8TimeOut && !(CR & RCC_HSE_RDY))
				{
					Loc_u8TimeOut--;
				}

				//Check if the Clock is Ready
				if(CR & RCC_HSE_RDY)
				{
					Loc_enuErrorStatus = RCC_enuOK;
				}

				break;

			case RCC_PLL:

				//Turn PLL ON
				CR |= RCC_u32ClockType;

				//Wait for the Ready Flag
				while(Loc_u8TimeOut && !(CR & RCC_PLL_RDY))
				{
					Loc_u8TimeOut--;
				}

				//Check if the Clock is Ready
				if(CR & RCC_PLL_RDY)
				{
					Loc_enuErrorStatus = RCC_enuOK;
				}

				break;

			}

			break;

			case RCC_OFF:

				//Turn Clock OFF
				CR &= ~(RCC_u32ClockType);

				break;
		}
	}

	return Loc_enuErrorStatus;
}

RCC_tenumErrorStatus RCC_enuSelectSystemClock(RCC_tenumSysClockSW RCC_enuSysClockType)
{
	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuClockError;

	RCC_tenumSysClockSW Loc_enuSWS;

	if(RCC_enuSysClockType > CLOCK_TYPES_NUM)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{
		//Select System Clock
		CFGR |= RCC_enuSysClockType;

		//Get the System Clock Status
		Loc_enuSWS = RCC_enuGetSystemClockStatus();

		//Check the System Clock
		if( Loc_enuSWS == RCC_enuSysClockType)
		{
			Loc_enuErrorStatus = RCC_enuOK;
		}
	}

	return Loc_enuErrorStatus;
}

RCC_tenumSysClockSW RCC_enuGetSystemClockStatus(void)
{
	RCC_tenumSysClockSW Loc_enuSWS = RCC_SW_ERROR;

	//Get System Clock Status
	Loc_enuSWS = (CFGR & RCC_SWS) >> TWO_BITS_SHIFT;

	return Loc_enuSWS;
}

RCC_tenumErrorStatus RCC_enuPllConfig(u32 Copy_u32PLLM , u32 Copy_u32PLLN , u32 Copy_u32PLLQ , u32 Copy_u32PLLP , u32 Copy_u32PLLSRC)
{
	// Local Temporary Variable to hold the Reset Value of PLLCFGR but Clearing the config bits
	u32 Loc_u32PllCfgTemp = PLL_RESET_REG;

	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuOK;

	//Check if the PLL is ON asln -> if True return Error
	if(CR & RCC_PLL_RDY)
	{
		Loc_enuErrorStatus = RCC_enuPLL_CFG_Error;
	}
	else if(Copy_u32PLLM > PLLM_DIV_BY_63 || Copy_u32PLLN > PLLN_MUL_BY_432 || Copy_u32PLLQ > PLLQ_DIV_BY_15 || Copy_u32PLLP > PLLP_DIV_BY_8 || (Copy_u32PLLSRC != PLL_HSE_SRC && Copy_u32PLLSRC != PLL_HSI_SRC))
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{
		//Configure the PLL
		Loc_u32PllCfgTemp = Copy_u32PLLM | Copy_u32PLLN | Copy_u32PLLQ | Copy_u32PLLP | Copy_u32PLLSRC;

		PLLCFGR = Loc_u32PllCfgTemp;
	}

	return Loc_enuErrorStatus;
}

RCC_tenumErrorStatus RCC_enuEnablePrephiralClock(u32 Copy_u32PrephiralId)
{
	u32 Loc_u32BusId;

	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuOK;

	if(Copy_u32PrephiralId > MAX_NUM_PRIPH)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{
		//Get the BUS ID
		Loc_u32BusId = Copy_u32PrephiralId & BUS_ID_MASK;

		//Clear the selection bit on the Reserved bits
		Copy_u32PrephiralId &= ~(BUS_ID_MASK);

		//Enable the Prephiral
		switch(Loc_u32BusId)
		{
		case RCC_AHB1:

			AHB1ENR |= Copy_u32PrephiralId;

			break;

		case RCC_AHB2:

			AHB2ENR |= Copy_u32PrephiralId;

			break;

		case RCC_APB1:

			APB1ENR |= Copy_u32PrephiralId;

			break;

		case RCC_APB2:

			APB2ENR |= Copy_u32PrephiralId;

			break;
		}
	}

	return Loc_enuErrorStatus;
}

RCC_tenumErrorStatus RCC_enuDisablePrephiralClock(u32 Copy_u32PrephiralId)
{
	u32 Loc_u32BusId;

	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuOK;

	if(Copy_u32PrephiralId > MAX_NUM_PRIPH)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{
		//Get the BUS ID
		Loc_u32BusId = Copy_u32PrephiralId & BUS_ID_MASK;

		//Clear the selection bit on the Reserved bits
		Copy_u32PrephiralId &= ~(BUS_ID_MASK);

		//Disable the Prephiral
		switch(Loc_u32BusId)
		{
		case RCC_AHB1:

			AHB1ENR &= ~(Copy_u32PrephiralId);

			break;

		case RCC_AHB2:

			AHB2ENR &= ~(Copy_u32PrephiralId);

			break;

		case RCC_APB1:

			APB1ENR &= ~(Copy_u32PrephiralId);

			break;

		case RCC_APB2:

			APB2ENR &= ~(Copy_u32PrephiralId);

			break;
		}
	}

	return Loc_enuErrorStatus;
}

RCC_tenumErrorStatus RCC_enuConfigBusPreScaler(u32 RCC_u32AHB_PRESCAL, u32 RCC_u32APB1_PRESCAL , u32 RCC_u32APB2_PRESCAL)
{
	RCC_tenumErrorStatus Loc_enuErrorStatus = RCC_enuOK;

	// Local Temporary Variable to hold the Reset Value of CFGR
	u32 Loc_u32BusPreScalConfigTemp = CFGR;

	if(RCC_u32AHB_PRESCAL > AHB_PRESCAL_DIV_BY_512 || RCC_u32APB1_PRESCAL > APB1_PRESCAL_DIV_BY_16 || RCC_u32APB2_PRESCAL > APB2_PRESCAL_DIV_BY_16)
	{
		Loc_enuErrorStatus = RCC_enuInValidInput;
	}
	else
	{

		//Configure the Buses Prescaler
		Loc_u32BusPreScalConfigTemp &= ~(RCC_u32AHB_PRESCAL | RCC_u32APB1_PRESCAL | RCC_u32APB2_PRESCAL);

		Loc_u32BusPreScalConfigTemp |= RCC_u32AHB_PRESCAL | RCC_u32APB1_PRESCAL | RCC_u32APB2_PRESCAL;

		CFGR = Loc_u32BusPreScalConfigTemp;
	}

	return Loc_enuErrorStatus;
}
