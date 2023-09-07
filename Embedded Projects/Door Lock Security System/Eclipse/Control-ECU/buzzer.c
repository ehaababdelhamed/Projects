/*
 * buzzer.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */

#include "gpio.h"
#include "common_macros.h"
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*Description
 *The Function responsible for setup the direction for the buzzer pin.
 *turn off the buzzer at the beginning
 */
void Buzzer_init() {
	/*Make pin of buzzer output pins*/
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	/*turn off the buzzer at the beginning*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*Description
 *The Function to turn on the buzzer
 */
void Buzzer_ON(){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

/*Description
 *The Function to turn on the buzzer
 */
void Buzzer_OFF(){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
