 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the AVR ADC driver
 *
 * Author: Ehab Mohammed
 *
 *******************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern volatile uint16 g_adc;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

typedef enum {
	AREF, AVCC, INTERNAL = 3
} ADC_ReferenceVolatge;
typedef enum {
	POLLING, INTERRUPT
} ADC_Techinqe;

typedef enum {
	F_CPU_2 = 1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
} ADC_Prescaler;

typedef struct {
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
	ADC_Techinqe techinqe;
} ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void ADC_init(const ADC_ConfigType *config_ptr);
uint16 ADC_readChannel(uint8 channel_num);
void ADC_conversation(uint8 channel_num);

#endif /* ADC_H_ */
