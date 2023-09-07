/*
 * Exercise4.c
 *
 *  Created on: Jun 21, 2017
 *  Author: Mohamed Tarek
 */

#include "Servo.h"
#include <util/delay.h>
#include "LDR.h"
#include "adc.h"

#define MAXIMUM_VERTICAL_DEGREE 160
#define MINIMUM_VERTICAL_DEGREE 10
#define MAXIMUM_HORIZONTAL_DEGREE 170
#define MINIMUM_HORIZONTAL_DEGREE 10

#define LEFT_TOP_CHANNEL 0
#define RIGHT_TOP_CHANNEL 1
#define LEFT_DOWN_CHANNEL 2
#define RIGHT_DOWN_CHANNEL 3

#define Tolerance 10
#define timedelay 20


uint16 LeftTop=0;
uint16 LeftDown=0;
uint16 RightTop=0;
uint16 RightDown=0;

uint8 ServoVertical=90;
uint8 ServoHorizontal=90;


int main(void)
{
	uint16 AvrageTop=0;
	uint16 AvrageDown=0;
	uint16 AvrageRight=0;
	uint16 AvrageLeft=0;
	uint16 AvrageTopDown=0;
	uint16 AvrageLeftRight=0;

	Servo_init(OC1A);
	Servo_init(OC1B);
	Servo_write(ServoVertical,OC1A);
	Servo_write(ServoHorizontal,OC1B);
	ADC_ConfigType ADC_Config={AVCC,POLLING,F_CPU_64};
	ADC_init(&ADC_Config);
	_delay_ms(2500);
	while(1)
	{
		LeftTop=LDR_getLight(LEFT_TOP_CHANNEL);
		LeftDown=LDR_getLight(LEFT_DOWN_CHANNEL);
		RightTop=LDR_getLight(RIGHT_TOP_CHANNEL);
		RightDown=LDR_getLight(RIGHT_DOWN_CHANNEL);

		AvrageTop=(uint16)((RightTop+LeftTop)/2);
		AvrageDown=(uint16)((RightDown+LeftDown)/2);
		AvrageRight=(uint16)((RightTop+RightDown)/2);
		AvrageLeft=(uint16)((LeftTop+LeftDown)/2);

		AvrageTopDown=abs(AvrageTop-AvrageDown);
		AvrageLeftRight=abs(AvrageRight-AvrageLeft);

		if(AvrageTopDown>Tolerance){
			if(AvrageTop<(AvrageDown-Tolerance)){
				ServoVertical++;
				if(ServoVertical>=MAXIMUM_VERTICAL_DEGREE){
					ServoVertical=MAXIMUM_VERTICAL_DEGREE;
				}
			}else if(AvrageTop>(AvrageDown+Tolerance)){
				ServoVertical--;
				if(ServoVertical<=MINIMUM_VERTICAL_DEGREE){
					ServoVertical=MINIMUM_VERTICAL_DEGREE;
				}
			}
			Servo_write(ServoVertical,OC1A);
		}
		if(AvrageLeftRight>Tolerance){
			if(AvrageLeft>(AvrageRight+Tolerance)){
				ServoHorizontal++;
				if(ServoHorizontal>=MAXIMUM_HORIZONTAL_DEGREE){
					ServoHorizontal=MAXIMUM_HORIZONTAL_DEGREE;
				}
			}else if(AvrageLeft<(AvrageRight-Tolerance)){
				ServoHorizontal--;
				if(ServoHorizontal<=MINIMUM_HORIZONTAL_DEGREE){
					ServoHorizontal=MINIMUM_HORIZONTAL_DEGREE;
				}
			}
			Servo_write(ServoHorizontal,OC1B);
		}
		_delay_ms(timedelay);
	}
}
