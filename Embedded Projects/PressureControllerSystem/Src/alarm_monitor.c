/******************************************************************************
 * File Name: alarm_monitor.c
 * Description: soruce file for alarm monitor to give alarm when high pressure detected
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#include "alarm_monitor.h"

/*******************************************************************************
 *                         Module Global Variables                             *
 ******************************************************************************/
 
void(*AlarmMonitor_state)()=STATE(AlarmMonitor_alarmOFF);
AlarmMonitor_states_t AlarmMonitor_state_id=AlarmMonitor_alarmOFF;


/*******************************************************************************
 *                              Functions Definition                           *
 ******************************************************************************/
 
 /************************************************************************************
 * Function Name: STATE_AlarmMonitor_alarmOFF
 * Description: Function to make alarm mointor on state when high pressure detection
 ************************************************************************************/
 void AlarmMointorTurnON(){
	AlarmMonitor_state=STATE(AlarmMonitor_alarmON);
}
 
/************************************************************************************
 * Function Name: STATE_AlarmMonitor_alarmOFF
 * Description: intial state of alarm mointor and actutors is turned off
 ************************************************************************************/

CREATE_STATE(AlarmMonitor_alarmOFF){
	//state name
	AlarmMonitor_state_id=AlarmMonitor_alarmOFF;
}

/************************************************************************************
 * Function Name: STATE_AlarmMonitor_alarmON
 * Description: state for send signal to alarm actuator to turn on
 ************************************************************************************/

CREATE_STATE(AlarmMonitor_alarmON){
	//state name
	AlarmMonitor_state_id=AlarmMonitor_alarmON;
	//state action
	//start alarm actuators then move to waiting state
	AlarmStart();
	AlarmMonitor_state=STATE(AlarmMonitor_waiting);
}

/************************************************************************************
 * Function Name: STATE_AlarmMonitor_waiting
 * Description: state for keep alarm on for alarm time period then turn off
 ************************************************************************************/

CREATE_STATE(AlarmMonitor_waiting){
	//State name
	AlarmMonitor_state_id=AlarmMonitor_waiting;
	//state action
	//Keep alarm on for alarm time period
	Delay(ALARM_TIME);
	AlarmStop();
	//move to alarm off state
	AlarmMonitor_state=STATE(AlarmMonitor_alarmOFF);
}

