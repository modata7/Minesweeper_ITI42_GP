/*
 * Detection.h
 *
 *  Created on: Jun 27, 2022
 *      Author: Ahmed Soliman
 */

#ifndef DETECTION_H_
#define DETECTION_H_


/*for Detection Circuit*/
#define detectionPIN							GPIO_u8PIN_02

/*for Buzzer Alert*/
#define buzzerPIN								GPIO_u8PIN_07

/*for Proximity Sensor*/
#define proximityPIN							GPIO_u8PIN_08

#define RCC_EN_PORT                             RCC_AHB_GPIOB

#define DETECT_PORT                             PORTB

#define DETECTED								0x01

#define UNDERGROUND								0x00

#define SURFACE									0x01

#define BUZZER_ON								GPIO_LOW

#define BUZZER_OFF								GPIO_HIGH

#define CALIBRATIONLIMIT						800




/*Note*/
/*
  Noise Flag:-
    -When a mine is detected, it returns a lot of signals.
    -So I want to make sure if its real detection or just noise,
    -I define a flag to calibration the number of signals,
    -if it is more than 10, then it is a real detection
    -if not, it is just a noise.
 */


/*Global Variables*/
u8 detectionVar;
u8 proximityVar;

/*Function Prototypes*/
void initPins(void);
void DetectionTask(void);


#endif /* DETECTION_H_ */
