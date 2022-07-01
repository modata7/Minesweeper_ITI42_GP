/*
 * Collection.h
 *
 *  Created on: Jun 23, 2022
 *      Author: WINDOWS
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_


#define     SERVO_UP_STATE            'F'
#define     SERVO_DOWN_STATE          'B'
#define     SERVO_AUTO_STATE          'R'
#define     MAG_ON_STATE              'O'
#define     MAG_OFF_STATE             'X'

void Servo_vidUp(u8 Copy_u8Servo1,u8 Copy_u8Servo2);
void Servo_vidDown(u8 Copy_u8Servo1,u8 Copy_u8Servo2);
u8 Servo_vidAuto(u8 Copy_u8Servo1,u8 Copy_u8Servo2);


void Collection();

#endif /* COLLECTION_H_ */
