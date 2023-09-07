 /******************************************************************************
 *
 * Module: Timer(Timer0-Timer1-Timer2)
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR Timer driver(Timer0-Timer1-Timer2)
 *
 * Author: Ehab Mohamed Abdelhamed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NORMAL_MODE,COMPARE_MATCH_MODE
}Timer_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Prescale;

typedef enum
{
	TIMER_0,TIMER_1,TIMER_2
}Timer_TimerNumber;


typedef struct
{
	Timer_TimerNumber timer_number;
	Timer_Mode mode;
	uint16 intial_value;
	uint16 compare_value;
	Timer_Prescale prescale;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer driver (Timer0-Timer1-Timer2)
 *  1. Initialize the required Timer Registers
 * 	2. Set the required mode for Timer
 * 	3. Set the required presacle.
 * 	4. Enable the Interrupt.
 * 	5.set the intial value for timer
 */
void Timer_init(Timer_ConfigType *Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));

void Timer2_setCallBack(void (*a_ptr)(void));

/*
 * Description: Function to disable the Requried Timer (Timer0-Timer1-Timer2)
 */
void Timer_deInit(Timer_TimerNumber timer_number);


#endif /* TIMER_H_ */
