/******************************************************************************
 * File Name: pressure_controller.c
 * Description: soruce file for pressure controller to detect high pressure
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#include "pressure_controller.h"

/*******************************************************************************
 *                         Module Global Variables                             *
 ******************************************************************************/
 
uint32 pressure=0;
uint32 threshold=PRESSURE_THRESHOLD;
void(*PressureController_state)()=STATE(PressureController_busy);
PressureController_states_t PressureController_state_id=PressureController_idle;

/*******************************************************************************
 *                              Functions Definition                           *
 ******************************************************************************/
 
 /************************************************************************************
 * Function Name: GetPressureValue
 * Description: Function to pressure value from pressure sensor
 ************************************************************************************/

void GetPressureValue(int Pval){
	pressure=Pval;
	PressureController_state=STATE(PressureController_busy);
}

 /************************************************************************************
 * Function Name: CREATE_STATE(PressureController_idle)
 * Description: Function to waiting untill sensor send pressure value
 ************************************************************************************/

CREATE_STATE(PressureController_idle){
	//state name
	PressureController_state_id=PressureController_idle;
	//state action
	//no thing , waiting untill sensor send pressure value
}
 /************************************************************************************
 * Function Name: CREATE_STATE(PressureController_busy)
 * Description: Function to check if pressure value larger than threshold
 ************************************************************************************/

CREATE_STATE(PressureController_busy){
	//state name
	PressureController_state_id=PressureController_busy;
	//state action
	if(pressure>=threshold){
		AlarmMointorTurnON();
	}
	PressureController_state=STATE(PressureController_idle);
}
