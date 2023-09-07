/*
 ================================================================================================
 Name        : HMI-ECU.h
 Author      : Ehab Mohamed Abdelhamed
 Description : HMI_ECU for door locker security system
 Date        : 10/7/2022
 ================================================================================================
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

/*******************************************************************************
 *                                Include                                      *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
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
#define ECU2_READY 0xFF
#define NUMBEROFTICKSPERSECOND 4
#define TIMEOFDOOROPEN 33
#define TIMEOFBUZZERON 60

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to display main options on screen
 */

void displayMainOption();

/*
 * Description: call back Function by timer to calcuate time of door open
 * 15 seconds CW
 * 3 seconds
 * 15 seconds ACW
 */
void displayOpenDoorticks(void);


/*
 * Description: Function to display door is open for 33 seconds
 */
void displayOpenDoor(void);


/*
 * Description: call back Function by timer to calcuate time of alaram
 */

void displayWarningMessageticks();


/*
 * Description: Function to display warning message for 1 minuts
 */
void displayWarningMessage();

/*
 * Description: Function to enter new password for system
 * enter new password
 * re enter new password
 * if match send to control ECU to save it in eeprom
 */

void enterNewPassword();

/*
 * Description: Function to enter password to open door or change password
 * enter password
 * send to control ECU to match it with system password
 */

void enterPassword();

#endif /* HMI_ECU_H_ */
