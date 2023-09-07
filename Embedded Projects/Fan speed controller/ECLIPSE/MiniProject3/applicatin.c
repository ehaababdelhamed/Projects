/******************************************************************************
 *
 * File Name: application.c
 *
 * Description: Fan Controller system
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/
#include "lcd.h"
#include "pwm.h"
#include "adc.h"
#include "dc_motor.h"

int main() {
	/*intial value of temprature =0*/
	uint8 tempratureValue = 0;
	/*intialization of LCD driver*/
	LCD_init();
	/*set configrations of ADC driver*/
	ADC_ConfigType ADC_Config = { INTERNAL, F_CPU_8, POLLING };
	ADC_init(&ADC_Config);
	/*intialization of dc motor*/
	DcMotor_init();
	/*display string on LCD At specific location*/
	LCD_displayStringRowColumn(1, 3,"Temp= ");
	while (1) {
		LCD_moveCursor(1, 9);
		/*read the temprature value from temprature sensor*/
		tempratureValue = LM35_getTemperature();
		/*display the value of temprature on LCD*/
		LCD_intgerToString(tempratureValue);
		LCD_displayCharacter('C');
		LCD_displayCharacter(' ');
		/* If the temperature is less than 30C turn off the fan.
		 * If the temperature is greater than or equal 30C turn on the fan with 25% of its
		 maximum speed.
		 * If the temperature is greater than or equal 60C turn on the fan with 50% of its
		 maximum speed.
		 * If the temperature is greater than or equal 90C turn on the fan with 75% of its
		 maximum speed.
		 *If the temperature is greater than or equal 120C turn on the fan with 100% of its
		 maximum speed.
		 */
		if (tempratureValue >= 120) {
			DcMotor_Rotate(ON_CW, 100);
			LCD_displayStringRowColumn(0, 3, "Fan is ON");
		} else if (tempratureValue >= 90) {
			DcMotor_Rotate(ON_CW, 75);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (tempratureValue >= 60) {
			DcMotor_Rotate(ON_CW, 50);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (tempratureValue >= 30) {
			DcMotor_Rotate(ON_CW, 25);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (tempratureValue < 30) {
			DcMotor_Rotate(OFF, 0);
			LCD_displayStringRowColumn(0, 3, "Fan is OFF ");
		}
	}
}
