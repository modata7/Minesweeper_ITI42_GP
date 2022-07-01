/*
 * HMagnet.h
 *
 *  Created on: Mar 25, 2022
 *      Author: modata7
 */

#ifndef HMAG_H_
#define HMAG_H_

typedef struct
{
	void* Port;

	u8 Pin;

	u8 Mode;

	u8 Active_Status;

}Magnet_tenuCfg;

typedef enum
{
	HMagnet_enuOK,

	HMagnet_enuInvalidInput,

	HMagnet_enuNOK

}HMagnet_tenuErrorStatus;

/* MAG States */
#define	HMAG_u8MAG_ON	0
#define	HMAG_u8MAG_OFF	1

/* Function Prototypes */
extern HMagnet_tenuErrorStatus HMagnet_enuMagnetInit(void);

extern HMagnet_tenuErrorStatus HMagnet_enuMagnetSetState(u8 Copy_u8MagnetNum , u8 Copy_u8MagnetState);

#endif /* HMAG_H_ */
