/******************************************************************************
 * File Name: alarm_actuator.c
 * Description: Source file for alarm actuator driver
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#include "alarm_actuator.h"
/*******************************************************************************
 *                         Module Global Variables                             *
 ******************************************************************************/

void(*AlarmActuator_state)()=STATE(AlarmActuator_waiting);
AlarmActuator_states_t AlarmActuator_state_id=AlarmActuator_waiting;

/*******************************************************************************
 *                              Functions Definition                           *
 ******************************************************************************/
 
 /************************************************************************************
 * Function Name: AlarmStart
 * Description: Signal to make alarm actuator in on state
 ************************************************************************************/

void AlarmStart(){
	AlarmActuator_state=STATE(AlarmActuator_alarmON);
}
/************************************************************************************
 * Function Name: AlarmStop
 * Description: Signal to make alarm actuator in off state
 ************************************************************************************/

void AlarmStop(){
	AlarmActuator_state=STATE(AlarmActuator_alarmOFF);
}
/************************************************************************************
 * Function Name: AlarmActuator_init
 * Description: Function to initailze actuator driver
 ************************************************************************************/

void AlarmActuator_init(){
	/*intialization*/
	//intiatilze actuators by off (Active Low)
	Set_Alarm_actuator(TRUE);
}

/************************************************************************************
 * Function Name: STATE_AlarmActuator_waiting
 * Description: waiting signal to action
 ************************************************************************************/

CREATE_STATE(AlarmActuator_waiting){
	//State Name
	AlarmActuator_state_id=AlarmActuator_waiting;
}
/************************************************************************************
 * Function Name: STATE_AlarmActuator_alarmON
 * Description: turn on alarm actuator then back to waiting state
 ************************************************************************************/

CREATE_STATE(AlarmActuator_alarmON){
	//State Name
	AlarmActuator_state_id=AlarmActuator_alarmON;
	//State action
	Set_Alarm_actuator(FALSE);
	AlarmActuator_state=STATE(AlarmActuator_waiting);

}
/************************************************************************************
 * Function Name: STATE_AlarmActuator_alarmOFF
 * Description: turn off alarm actuator then back to waiting state
 ************************************************************************************/
CREATE_STATE(AlarmActuator_alarmOFF){
	//State Name
	AlarmActuator_state_id=AlarmActuator_alarmOFF;
	//State action
	Set_Alarm_actuator(TRUE);
	AlarmActuator_state=STATE(AlarmActuator_waiting);
}

