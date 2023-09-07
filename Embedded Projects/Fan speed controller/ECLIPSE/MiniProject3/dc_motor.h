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
#define DCMOTOR_OUT1_PORT PORTB_ID
#define DCMOTOR_OUT1_PIN  PIN5_ID

#define DCMOTOR_OUT2_PORT PORTB_ID
#define DCMOTOR_OUT2_PIN  PIN4_ID


typedef enum {
	OFF,ON_CW,ON_ACW
} DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DcMotor_init();
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
