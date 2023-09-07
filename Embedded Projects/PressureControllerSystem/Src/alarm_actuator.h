/******************************************************************************
 * File Name: alarm_actuator.h
 * Description: Header file for alarm actuator driver
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef ALARM_ACTUATOR_H_
#define ALARM_ACTUATOR_H_

#include "Platform_Types.h"
#include "driver.h"
#include "state.h"
/*******************************************************************************
 *                              Extern Variables                           *
 *******************************************************************************/
extern void(*AlarmActuator_state)();

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef enum{
	AlarmActuator_waiting,AlarmActuator_alarmON,AlarmActuator_alarmOFF
}AlarmActuator_states_t;

/*******************************************************************************
 *                              Module States                             *
 *******************************************************************************/
//function to intialize actuator driver
void AlarmActuator_init();
//waiting state for receive signal 
CREATE_STATE(AlarmActuator_waiting);
//turn on alarm actuator  
CREATE_STATE(AlarmActuator_alarmON);
//turn off alarm actuator  
CREATE_STATE(AlarmActuator_alarmOFF);

#endif /* ALARM_ACTUATOR_H_ */
