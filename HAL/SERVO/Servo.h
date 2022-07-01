/*
 * Servo.h
 *
 *  Created on: Jun 23, 2022
 *      Author: WINDOWS
 */

#ifndef SERVO_H_
#define SERVO_H_


typedef struct{
	u32 TimNum;
	u32 Channel;
}Servo_cfg;


void Servo_vidInit(u8 Copy_u8ServoNum);
void Servo_vidSetAngle(u8 Copy_u8ServoNum,u8 Copy_u8Angle);


#endif /* SERVO_H_ */
