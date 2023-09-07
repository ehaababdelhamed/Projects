/*
 * Timer1_PWM.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */
#include <avr/io.h>/* To use the IO Ports Registers */
#include "Timer1_PWM.h"

void Timer1_PWM_init(uint8 channel){
	TCNT1 = 0;		/* Set timer1 initial count to zero */
	ICR1 =(F_CPU/(400));  /* Set TOP count for timer1 in ICR1 register */
	if(channel==OC1A){
		OCR1A = 0;
		/* Configure timer control register TCCR1A
	     * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
	     * 2. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
         * 3. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
	     * */
		TCCR1A&=0x10;
		TCCR1A|=(1<<WGM11) | (1<<COM1A1);
	}else if(channel==OC1B){
		OCR1B = 0;
		/* Configure timer control register TCCR1A
	     * 1. Clear OC1B on compare match (non inverting mode) COM1B1=1 COM1B0=0
	     * 2. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
         * 3. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
	     * */
		TCCR1A&=0x80;
		TCCR1A|=(1<<WGM11) | (1<<COM1B1);
	}
	/* Configure timer control register TCCR1B
	 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
	 * 2. Prescaler = F_CPU/8
     */
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS11);
}

void Timer1_PWM_setDutyCycle(uint16 duty_cycle,uint8 channel){
	if(channel==OC1A){
		OCR1A = duty_cycle;
	}else if(channel==OC1B){
		OCR1B = duty_cycle;
	}
}

