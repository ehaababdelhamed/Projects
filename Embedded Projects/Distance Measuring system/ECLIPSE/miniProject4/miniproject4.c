/*
 * miniproject4.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr\io.h>

int main(){
	SREG|=(1<<7); /*enable global interrupt*/
	uint16 Distance=0; /* variable to save the distance value*/
	/*intialize LCD Driver*/
	LCD_init();
	/*intialize Ultrasonic Driver*/
	Ultrasonic_init();
	LCD_displayString("Distance= ");
	while(1){
		/* read distace by ultrasonic sensor*/
		Distance=Ultrasonic_readDistance();
		 LCD_moveCursor(0,10);
		 /*display distance on screen*/
		LCD_intgerToString(Distance);
		LCD_displayString("cm");
		LCD_displayCharacter(' ');
	}
}
