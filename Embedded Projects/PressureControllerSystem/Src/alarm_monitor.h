/******************************************************************************
 * File Name: alarm_monitor.h
 * Description: Header file for alarm monitor
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef ALARM_MONITOR_H_
#define ALARM_MONITOR_H_

#include "Platform_Types.h"
#include "driver.h"
#include "state.h"
/*******************************************************************************
 *                              User configuration                          *
 *******************************************************************************/

#define ALARM_TIME (6000000u)

/*******************************************************************************
 *                              Extern Variables                               *
 *******************************************************************************/

extern void(*AlarmMonitor_state)();
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
 
typedef enum{
	AlarmMonitor_waiting,AlarmMonitor_alarmON,AlarmMonitor_alarmOFF
}AlarmMonitor_states_t;

/*******************************************************************************
 *                              Module States                             *
 *******************************************************************************/
//state for waiting untill pressure controll send signal to turn on alarm
CREATE_STATE(AlarmMonitor_waiting);
//state to send signal to alarm actuator to turn on
CREATE_STATE(AlarmMonitor_alarmON);
//state to send signal to alarm actuator to turn off
CREATE_STATE(AlarmMonitor_alarmOFF);

#endif /* ALARM_MONITOR_H_ */
