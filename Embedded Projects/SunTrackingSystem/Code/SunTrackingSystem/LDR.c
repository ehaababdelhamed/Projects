/*
 * LDR.c
 *
 *  Created on: ???/???/????
 *      Author: Ehab Mohamed
 */
#include "adc.h"
#include "LDR.h"

/*
 * Description :
 * Function responsible for calculate the Percentage of light from the ADC digital value.
 */
uint16 LDR_getLight(uint8 LDR_channel)
{
	uint16 light_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	light_value = ADC_readChannel(LDR_channel);

	return light_value;
}


