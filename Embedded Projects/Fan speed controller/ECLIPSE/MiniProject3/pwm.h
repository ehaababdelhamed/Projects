 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: header file for the PWM MODE FROM TIMER driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/

#include "std_types.h"

#define TIMER0_MAXIMUM_VALUE    255


#ifndef PWM_H_
#define PWM_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*intialize timer0 to generate pwm*/

void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
