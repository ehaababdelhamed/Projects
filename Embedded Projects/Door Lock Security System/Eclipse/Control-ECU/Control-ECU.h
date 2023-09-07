/*
 ================================================================================================
 Name        : Control-ECU.h
 Author      : Ehab Mohamed Abdelhamed
 Description : Control_ECU for door locker security system
 Date        : 10/7/2022
 ================================================================================================
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

/*******************************************************************************
 *                                Include                                      *
 *******************************************************************************/

#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "timer.h"
#include "buzzer.h"
#include "dc_motor.h"
#include <util/delay.h>
#include <avr/io.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define F_CPU 8000000UL
#define MAXNUMBERS 5
#define ERROR 0
#define SUCCESS 1
#define UART_BAUDRATE 9600
#define TWI_BAUDRATE 400000
#define TWI_SLAVEADDRESS 0X01
#define ECU2_READY 0xFF
#define NUMBEROFTICKSPERSECOND 4
#define TIMEOFOPENDOOR 15
#define TIMEOFHOLDEDOOR 18
#define TIMEOFCLOSEDOOR  33
#define TIMEOFBUZZERON 60
#define DEFUALTVALUE 0XFF
#define MAXMISSING 3
#define EEPROMADDRESS 0x0310


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description: call back Function by timer to calcuate time of door open
 */


void OpenDoorticks(void) ;




/*
 * Description: Function to open the door
 * 15 seconds CW (OPEN)
 * 3 seconds hold (HOLD)
 * 15 seconds ACW (CLOSE)
 */

void OpenDoor(void);


/*
 * Description: call back Function by timer to calcuate time of Runing Buzzer
 */

void turnOnBuzzerticks();


/*
 * Description: Function to turn on buzzer for 1 minute
 */

void turnOnBuzzer();


/*
 * Description: Function to check if it is fist using of the system
 * check if there are password in saved at memory or not
 * send flag to HMI_ECU
 *
 */

void checkIfFirstUse(uint8 *new_password_flag);



/*
 * Description: Function to save new password for the system in eeprom
 * recieve new password from HMI_ECU
 * save new password in eeprom
 */

void SavePasswordeEeprom();


/*
 * Description: Function to recieve password form HMI-ECU to open door or change password
 * Recieve password
 * match it with system password and return success or error
 */

uint8 matchPassword();

#endif /* CONTROL_ECU_H_ */
