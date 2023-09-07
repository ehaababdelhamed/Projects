 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: source file for the PWM MODE FROM TIMER driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/
#include "pwm.h"
#include "common_macros.h"
#include <avr/io.h>
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*intialize timer0 to generate pwm*/


void PWM_Timer0_Start(uint8 duty_cycle){
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0 ,to make freq=500hz
	 */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01);
	OCR0=(uint8)(((uint16)duty_cycle*255)/(100)); /*Set Compare Value*/
	TCNT0 = 0; /*Set Timer Initial value*/
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);/*set PB3/OC0 as output pin*/
}
