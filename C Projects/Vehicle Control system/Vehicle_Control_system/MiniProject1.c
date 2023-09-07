/*
 *********************************************************************************
 * Name        :  MiniProject1.c
 * Author      :  Ehab mohamed abdelhamed
 * Created on  :  15/4/2022
 * Description :  Vehicle Control System Project
 **********************************************************************************
 */

#include <stdio.h>
#define undifned -1 //for undesired input

//the options States Of System
enum state {
	OFF, ON, QUIT
};

//Variables For vehicle system
typedef struct {
	char Colour;
	float RoomTemprature;
	float engineTemprature;
	float Speed;
	enum state AC, EngineTempController;
} VS;

//Function to print states of vehicle
void PrintState(void) {
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
}

//to return the state of system passing by value
char StateVehicle(char ES) {
	if (ES == 'a')
		return ON;
	else if (ES == 'b')
		return OFF;
	else if (ES == 'c')
		return QUIT;
	else
		return undifned; //in case enter charcter other than a,b,c
}

//to display the sensors menu if engine is ON
void PrintSensorsMenu() {
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
}

//b)Traffic lights function
void TrafficLights(char *light, float *speed) {
	printf("enter the Required Colour: \n");
	scanf(" %c", light);  //enter the colour form user
	switch (*light) {      //check Colour to set the speed
	case 'g':
	case 'G':
		*speed = 100;
		break;
	case 'o':
	case 'O':
		*speed = 30;
		break;
	case 'r':
	case 'R':
		*speed = 0;
		break;
	default:
		*light = undifned; //in case enter Another Charcter
	}
}
//c)RoomTemprature function passing vairables by address
void RoomTempratureSensor(float *Temp, enum state *ac) {
	printf("Enter The required room temprature\n");
	scanf("%f", Temp); //enter room temprature value from user to set AC state
	if (*Temp <= 10 || *Temp > 30) {
		*ac = ON;
		*Temp = 20;
	} else {
		*ac = OFF;
	}
}
//d)Engine Temprature function passing by address
void EngineTempratureSensor(float *Etemp, enum state *ECT) {
	printf("Enter the Required Engine temprature\n");
	scanf("%f", Etemp); //enter the engine temprature from user
	if (*Etemp < 100 || *Etemp > 150) {
		*ECT = ON;
		*Etemp = 125;
	} else {
		*ECT = OFF;
	}
}

//function takes structure by address
void CheckSpeed(VS *ptr) {
	if (ptr->Speed == 30) {
		ptr->AC = ON;
		ptr->RoomTemprature = ptr->RoomTemprature * (5.0 / 4) + 1;
		ptr->EngineTempController = ON;
		ptr->engineTemprature = ptr->engineTemprature * (5.0 / 4) + 1;
	}
}

//to Display the current vehicle state
void DisplayState(VS *ptr, enum state *Enginestate) {
	if (*Enginestate == ON)
		printf("\nEngine state is ON\n");
	else
		printf("\nEngine state is OFF\n");
	if (ptr->AC == ON)
		printf("AC state is ON\n");
	else
		printf("Engine state is OFF\n");
	printf("Vehicle Speed = %0.2f Km/hr\n", ptr->Speed);
	printf("Room Temperature = %0.2f C\n", ptr->RoomTemprature);
	if (ptr->EngineTempController == ON)
		printf("Engine Temperature Controller State is ON\n");
	else
		printf("Engine Temperature Controller State is OFF\n");
	printf("Engine Temperature = %0.2f C\n\n", ptr->engineTemprature);
}

//start main function
int main(void) {
	setbuf(stdout, NULL);
	VS Vehicle = { 'g', 35, 110, 100, ON, OFF }; /*Defination Variable of type structure Vechile*/
	char inputES, MenuSensor; /* Variables to take Values from user*/
	enum state EngineState;
	while (1) { /*Super Loop*/
		PrintState(); /*call function print the options of states of engine*/
		scanf(" %c", &inputES);
		EngineState = StateVehicle(inputES);
		if (EngineState == ON) {
			printf("Turn on the vehicle engine\n\n");
			while (1) { /*second loop for the sensors menu*/
				PrintSensorsMenu();
				scanf(" %c", &MenuSensor);
				if (MenuSensor == 'a') {
					EngineState = OFF;
					break; //break second loop and enter first loop print the engine state
				} else if (MenuSensor == 'b') {
					/*looping if enter another Charcter
					 * program ask user agian to enter the colour untill enter right colour*/
					do {
						TrafficLights(&Vehicle.Colour, &Vehicle.Speed);
					} while (Vehicle.Colour == undifned);
					/*the Colour remains in is undifned if user enter wrong colour*/
				} else if (MenuSensor == 'c') {
					RoomTempratureSensor(&Vehicle.RoomTemprature, &Vehicle.AC);
				} else if (MenuSensor == 'd') {
					EngineTempratureSensor(&Vehicle.engineTemprature,
							&Vehicle.EngineTempController);
				}
				CheckSpeed(&Vehicle); //change values only when speed =30
				DisplayState(&Vehicle, &EngineState); //display all states
			}
		} else if (EngineState == OFF) {
			printf("Turn off the vehicle engine\n\n");
			continue;
		} else if (EngineState == QUIT) {
			printf("Quit the system\n");
			break; //break first loop and end the program
		}
	}
	return 0;
}
