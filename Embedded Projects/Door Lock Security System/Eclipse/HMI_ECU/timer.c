/******************************************************************************
 *
 * Module: Timer (Timer0-Timer1-Timer2)
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR Timer driver (Timer0-Timer1-Timer2)
 *
 * Author: Ehab Mohamed Abdelhamed
 *
 *******************************************************************************/
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h> /* For Timer ISRs */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_timer0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer2_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/******************************************* Timer0 ISR ***************************************/
ISR(TIMER0_COMP_vect) {
	if (g_timer0_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_OVF_vect) {
	if (g_timer0_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/******************************************* Timer1 ISR ***************************************/

ISR(TIMER1_COMPA_vect) {
	if (g_timer1_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect) {
	if (g_timer1_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/******************************************* Timer2 ISR ***************************************/

ISR(TIMER2_COMP_vect) {
	if (g_timer2_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_OVF_vect) {
	if (g_timer2_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the requried Timer driver (Timer0-Timer1-Timer2)
 *  1. Initialize The required Timer Registers
 * 	2. Set the required mode for Timer
 * 	3. Set the required presca le.
 * 	4. Enable the Interrupt.
 * 	5. Set the intial value for timer
 */

void Timer_init(const Timer_ConfigType *Config_Ptr) {
	switch (Config_Ptr->timer_number) {
	case TIMER_0:
		/*FOC0=1 for non-PWM mode */
		TCCR0 = (1 << FOC0);
		/*set the required mode for timer*/
		/*for normal mode WGM00=0,WGM01=0;
		 *for compare match mode WGM00=0,WGM01=1
		 * */
		if (Config_Ptr->mode == COMPARE_MATCH_MODE) {
			SET_BIT(TCCR0, WGM01);
			/*
			 * insert the required compare match value in OCR0 Register
			 */
			OCR0 = Config_Ptr->compare_value;
			/* Enable the compare match interrupt to generate an interrupt when compare match occurs*/
			SET_BIT(TIMSK, OCIE0);
		} else if (Config_Ptr->mode == NORMAL_MODE) {
			/* Enable the overflow interrupt to generate an interrupt when overflow occurs*/
			SET_BIT(TIMSK, TOIE0);
		}
		/*
		 * insert the required clock value in the first three bits (CS00, CS01 and CS02)
		 * of TCCR0 Register
		 */
		TCCR0 = (TCCR0 & 0XF8) | (Config_Ptr->prescale & 0x07);
		/*
		 * insert the required intial value in TCNT0 Register
		 */
		TCNT0 = Config_Ptr->intial_value;
		break;
	case TIMER_1:
		/*FOC1A=1 ,FOC1B=1 for non-PWM mode */
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		/*set the required mode for timer*/
		/*for normal mode WGM10=0,WGM11=0,WGM12=0,WGM13=0;
		 *for compare match mode WGM10=0,WGM11=0,WGM12=1,WGM13=0
		 * */
		if (Config_Ptr->mode == COMPARE_MATCH_MODE) {
			TCCR1B = (1 << WGM12);
			/*
			 * insert the required compare match value in OCR1A Register
			 */
			OCR1A = Config_Ptr->compare_value;
			/* Enable the compare match interrupt to generate an interrupt when compare match occurs*/
			SET_BIT(TIMSK, OCIE1A);
		} else if (Config_Ptr->mode == NORMAL_MODE) {
			/* Enable the overflow interrupt to generate an interrupt when overflow occurs*/
			SET_BIT(TIMSK, TOIE1);
		}
		/*
		 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
		 * of TCCR1B Register
		 */
		TCCR1B = (TCCR1B & 0XF8) | (Config_Ptr->prescale & 0x07);
		/*
		 * insert the required intial value in TCNT1 Register
		 */
		TCNT1 = Config_Ptr->intial_value;
		break;
	case TIMER_2:
		/*FOC2=1 for non-PWM mode */
		TCCR2 = (1 << FOC2);
		/*set the required mode for timer*/
		/*for normal mode WGM20=0,WGM21=0;
		 *for compare match mode WGM20=0,WGM21=1
		 * */
		if (Config_Ptr->mode == COMPARE_MATCH_MODE) {
			SET_BIT(TCCR2, WGM21);
			/*
			 * insert the required compare match value in OCR2 Register
			 */
			OCR2 = Config_Ptr->compare_value;
			/* Enable the compare match interrupt to generate an interrupt when compare match occurs*/
			SET_BIT(TIMSK, OCIE2);
		} else if (Config_Ptr->mode == NORMAL_MODE) {
			/* Enable the overflow interrupt to generate an interrupt when overflow occurs*/
			SET_BIT(TIMSK, TOIE2);
		}
		/*
		 * insert the required clock value in the first three bits (CS20, CS21 and CS22)
		 * of TCCR2 Register
		 */
		if (Config_Ptr->prescale > F_CPU_8) {
			/*Because there is a difference in the order of prescale between timer2 and timer0&timer1 */
			TCCR2 = (TCCR2 & 0XF8) | ((Config_Ptr->prescale + 2) & 0x07);
		} else {
			TCCR2 = (TCCR2 & 0XF8) | ((Config_Ptr->prescale) & 0x07);
		}
		/*
		 * insert the required intial value in TCNT2 Register
		 */
		TCNT2 = Config_Ptr->intial_value;
		break;
	}
}

/*
 * Description: Function to set the Call Back function address.
 */

/******************************************* Timer0 Call back function ***********************************/

void Timer0_setCallBack(void (*a_cb0_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_timer0_callBackPtr = a_cb0_ptr;
}

/******************************************* Timer1Call back function ***********************************/

void Timer1_setCallBack(void (*a_cb1_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_timer1_callBackPtr = a_cb1_ptr;
}

/******************************************* Timer2Call back function ***********************************/
void Timer2_setCallBack(void (*a_cb2_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_timer2_callBackPtr = a_cb2_ptr;
}

/*
 * Description: Function to disable the Requried Timer (Timer0-Timer1-Timer2)
 */
void Timer_deInit(Timer_TimerNumber timer_number) {
	switch (timer_number) {
	case TIMER_0:
		/* Clear All Timer0 Registers */
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		/* Disable the interrupt */
		TIMSK &= ~(1 << TOIE0) & ~(1 << OCIE0);
		break;
	case TIMER_1:
		/* Clear All Timer1 Registers */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		/* Disable the interrupt */
		TIMSK &= ~(1 << TOIE1) & ~(1 << OCIE1A);
		break;
	case TIMER_2:
		/* Clear All Timer2 Registers */
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		/* Disable the interrupt */
		TIMSK &= ~(1 << TOIE2) & ~(1 << OCIE2);
		break;
	}
}

