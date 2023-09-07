/******************************************************************************
 * File Name: pressure_controller.h
 * Description: Header file for pressure controller
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef PRESSURE_CONTROLLER_H_
#define PRESSURE_CONTROLLER_H_

#include "Platform_Types.h"
#include "state.h"

/*******************************************************************************
 *                              User configuration                          *
 *******************************************************************************/

#define PRESSURE_THRESHOLD (20u)

/*******************************************************************************
 *                              Extern Variables                               *
 *******************************************************************************/
 
extern void(*PressureController_state)();


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
 
typedef enum{
	PressureController_idle,PressureController_busy
}PressureController_states_t;

/*******************************************************************************
 *                              Module States                             *
 *******************************************************************************/
 
/*State for waiting the pressure value from pressure signal */
CREATE_STATE(PressureController_idle);

/*State for check if the pressure value larger than threshold
* if it larger than threshold turn on alarm mointor
* if not back to idle state
*/
CREATE_STATE(PressureController_busy);

#endif /* PRESSURE_CONTROLLER_H_ */
