 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/

#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16 g_adc = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ADC driver
 * 	1. Set the required voltage reference
 * 	2. Set the required frequency.
 * 	3. Enable ADC.
 * 	4. Set the required techinqe (polling or interrupt).
 */
void ADC_init(const ADC_ConfigType *config_ptr) {
	/*MUX0...MUX4=0  intial channal 0
	 * insert the required Voltage Reference in REFS1,REFS2 bit in ADMUX Register
	 */
	ADMUX = ((config_ptr->ref_volt & 0x03) << 6);
	/*Enable ADC Driver*/
	ADCSRA = (1 << ADEN);
	/*Enable or Disable interrupt in ADEN,ADIE bit in ADCSRA Register */
	if (config_ptr->techinqe == INTERRUPT) {
		SET_BIT(ADCSRA, ADIE);
		SET_BIT(ADCSRA, ADSC);
	}
	/* insert the required Clock in ADPS0..ADPS2 bit in ADCSRA Register*/
	ADCSRA = (ADCSRA & 0xF8) | ((config_ptr-> prescaler) & 0x07);
}

/*
 * Function to set the required channel and read the The ADC value
 */
uint16 ADC_readChannel(uint8 channel_num) {
	/* insert the required channal MUX0..MUX4 bit in ADMUX Register*/
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x1F);
	/*ADC Start converstion analog signal from channel*/
	SET_BIT(ADCSRA, ADSC);
	while (BIT_IS_CLEAR(ADCSRA, ADIF))
		;
	SET_BIT(ADCSRA, ADIF);
	return ADC;
}

/*
 * Function to set the required channel and start conversation for interrupt
 */
void ADC_conversation(uint8 channel_num) {
	/* insert the required channal MUX0..MUX4 bit in ADMUX Register*/
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x1F);
	SET_BIT(ADCSRA, ADSC);
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(ADC_vect) {
	/*read the value Of ADC every interrupt*/
	g_adc = ADC;
}
