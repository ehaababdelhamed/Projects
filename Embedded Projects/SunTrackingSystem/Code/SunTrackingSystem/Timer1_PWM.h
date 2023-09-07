/*
 * Timer1_PWM.h
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */

#ifndef TIMER1_PWM_H_
#define TIMER1_PWM_H_

#include "std_types.h"

#define OC1A 0
#define OC1B 1

void Timer1_PWM_init(uint8 channel);
void Timer1_PWM_setDutyCycle(uint16 duty_cycle,uint8 channel);

#endif /* TIMER1_PWM_H_ */
