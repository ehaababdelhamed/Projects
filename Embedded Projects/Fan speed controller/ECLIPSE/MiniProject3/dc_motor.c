 /******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for dc motor driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/

#include "gpio.h"
#include "pwm.h"
#include  "common_macros.h"
#include   "dc_motor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*Description
 *The Function responsible for setup the direction for the two motor pins.
 *Stop at the DC-Motor at the beginning
 */
void DcMotor_init() {
	/*Make two pin of motors output pins*/
	GPIO_setupPinDirection(DCMOTOR_OUT1_PORT, DCMOTOR_OUT1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_OUT2_PORT, DCMOTOR_OUT2_PIN, PIN_OUTPUT);
	/*STOP motor at the beginning*/
	GPIO_writePin(DCMOTOR_OUT1_PORT, DCMOTOR_OUT1_PIN, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_OUT2_PORT, DCMOTOR_OUT2_PIN, LOGIC_LOW);
}

/*Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 stop the motor based on the state input state value.
 *Control the speed of motor based on duty cycle of pwm
 */

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	PWM_Timer0_Start(speed);
	switch (state) {
	case OFF:
		GPIO_writePin(DCMOTOR_OUT1_PORT, DCMOTOR_OUT1_PIN, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_OUT2_PORT, DCMOTOR_OUT2_PIN, LOGIC_LOW);
		break;
	case ON_CW:
		GPIO_writePin(DCMOTOR_OUT1_PORT, DCMOTOR_OUT1_PIN, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_OUT2_PORT, DCMOTOR_OUT2_PIN, LOGIC_HIGH);
		break;
	case ON_ACW:
		GPIO_writePin(DCMOTOR_OUT1_PORT, DCMOTOR_OUT1_PIN, LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_OUT2_PORT, DCMOTOR_OUT2_PIN, LOGIC_LOW);
		break;
	}
}

