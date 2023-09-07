 /******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dc_motor.h
 *
 * Description: Headar file for dc motor driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/

#include "std_types.h"

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
#define DCMOTOR_OUT1_PORT PORTC_ID
#define DCMOTOR_OUT1_PIN  PIN2_ID

#define DCMOTOR_OUT2_PORT PORTC_ID
#define DCMOTOR_OUT2_PIN  PIN3_ID


typedef enum {
	OFF,ON_CW,ON_ACW
} DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*Description
 *The Function responsible for setup the direction for the two motor pins.
 *Stop at the DC-Motor at the beginning
 */

void DcMotor_init();

/*Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 stop the motor based on the state input state value.
 */


void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
