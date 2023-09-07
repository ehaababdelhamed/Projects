/******************************************************************************
 * File Name: pressure_sesnor.h
 * Description: source file for pressure sensor driver to read pressure value
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/
#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "Platform_Types.h"
#include "driver.h"
#include "state.h"
/*******************************************************************************
 *                              Extern Variables                           *
 *******************************************************************************/
 
extern void(*PS_state)(); //Poninter to function pressure sensor state

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef enum{
	PS_READING,PS_WAITING
}ePS_states_t;
/*******************************************************************************
 *                              Module States                             *
 *******************************************************************************/
 //Function to intiailzation the pressure sensor
void PS_init();
//Reading state for pressure sensor
CREATE_STATE(PS_reading);
//waiting state for pressure sensor
CREATE_STATE(PS_waiting);


#endif /* PRESSURE_SENSOR_H_ */
