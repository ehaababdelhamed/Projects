/*
 * Servo.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */
#include "Timer1_PWM.h"
#include "gpio.h"
#include "Servo.h"
#include <math.h>

#define SERVOANGLE0  (((F_CPU/8000)*1)-1)
#define SERVOANGLE180  (((F_CPU/8000)*2)-1)
#define DGREE (5.56)


uint8 g_Postion=0;

void Servo_init(uint8 PWM_Channel){
	Timer1_PWM_init(PWM_Channel);
	if(PWM_Channel==OC1A){
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
	}else if(PWM_Channel==OC1B){
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
	}
}

void Servo_write(uint8 Postion,uint8 PWM_Channel){
	g_Postion=Postion;
	uint16 Pos=(uint16)(SERVOANGLE0+((float)Postion*DGREE));
	if(Pos>SERVOANGLE180){
		Pos=SERVOANGLE180;
	}else if(Pos<SERVOANGLE0){
		Pos=SERVOANGLE0;
	}
	Timer1_PWM_setDutyCycle(Pos,PWM_Channel);
}
uint8 Servo_readPosition(){
	uint8 lastPostion=g_Postion;
	return lastPostion;
}



