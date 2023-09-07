/******************************************************************************
 * File Name: main.c
 * Description: Pressure controller system
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#include "pressure_controller.h"
#include "pressure_sensor.h"
#include "alarm_actuator.h"
#include "alarm_monitor.h"
#include "driver.h"

void App_init(){
	//Initialization all modules
	GPIO_INITIALIZATION ();
	PS_init();
	AlarmActuator_init();
}

//Running Application
void App_start(){
	/********* Super Loop************/
	while(1){
		//Call states;
		(*PS_state)();
		(*PressureController_state)();
		(*AlarmMonitor_state)();
		(*AlarmActuator_state)();
	}
}

//Main Function
void main(void){
	App_init();
	App_start();
}
