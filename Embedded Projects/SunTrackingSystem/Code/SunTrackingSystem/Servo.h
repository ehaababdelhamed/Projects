/*
 * Servo.h
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "std_types.h"

#define OC1A 0
#define OC1B 1
#define SERVOANGLE0  (((F_CPU/8000)*1)-1)
#define SERVOANGLE180  (((F_CPU/8000)*2)-1)
#define DGREE (5.56)


void Servo_init(uint8 PWM_Channel);
void Servo_write(uint8 Postion,uint8 PWM_Channel);
uint8 Servo_readPosition();

#endif /* SERVO_H_ */
