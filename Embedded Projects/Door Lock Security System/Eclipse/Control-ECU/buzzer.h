/*
 * buzzer.h
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT    PORTD_ID
#define BUZZER_PIN     PIN4_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*Description
 *The Function responsible for setup the direction for the buzzer pin.
 *turn off the buzzer at the beginning
 */
void Buzzer_init();

/*Description
 *The Function to turn on the buzzer
 */
void Buzzer_ON();

/*Description
 *The Function to turn on the buzzer
 */
void Buzzer_OFF();

#endif /* BUZZER_H_ */
