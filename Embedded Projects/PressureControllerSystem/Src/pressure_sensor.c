/******************************************************************************
 * File Name: pressure_sesnor.c
 * Description: source file for pressure sensor driver to read pressure value
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#include "pressure_sensor.h"

/*******************************************************************************
 *                         Module Global Variables                             *
 ******************************************************************************/

uint32 PS_pressure=0;
void(*PS_state)()=STATE(PS_reading);
ePS_states_t PS_state_id=PS_READING;

/*******************************************************************************
 *                              Functions Definition                           *
 ******************************************************************************/
 
 /************************************************************************************
 * Function Name: PS_init()
 * Description: Function to intialize pressure sensor driver
 ************************************************************************************/

void PS_init(){
	/*intializtion of GPIO Pins of the module*/
}

 /************************************************************************************
 * Function Name: STATE_PS_reading
 * Description: Function to  measure pressure value 
 ************************************************************************************/
CREATE_STATE(PS_reading){
	//state name
	PS_state_id=PS_READING;
	//state action
	/*
	* Read from pressure sensor
	* Send the measured value to pressure controller module
	*/
	PS_pressure=getPressureVal();
	GetPressureValue(PS_pressure);
	//Jump to waiting state
	PS_state=STATE(PS_waiting);
}

 /************************************************************************************
 * Function Name: STATE_PS_waiting
 * Description: Function to wait fo pulling time
 ************************************************************************************/
CREATE_STATE(PS_waiting){
	//state name
	PS_state_id=PS_WAITING;
	//state action
	/*
	* waiting pull time
	* jump to reading state
	*/
	Delay(10000);
	PS_state=STATE(PS_reading);
}