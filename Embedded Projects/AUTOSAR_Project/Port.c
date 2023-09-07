/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT==(STD_ON))

#include "Det.h"

/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
		|| (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
		|| (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_PinConfigType *Port_PinConfig = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to initialize the Port Driver module. 
 ************************************************************************************/

void Port_Init(const Port_ConfigType *ConfigPtr) {
	volatile uint32 *Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
	volatile uint32 delay = 0;
	Port_PinType PinIndex = 0;
	boolean error = FALSE;
	Port_PinConfig = ConfigPtr->PortPins;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == ConfigPtr) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
				PORT_E_PARAM_CONFIG);
		error = TRUE;
	} else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		Port_Status = PORT_INITIALIZED;
	}

	if(error==FALSE){
		for (PinIndex = 0; PinIndex < PORT_NUMBER_OF_PORT_PINS; PinIndex++){
			/*select the required port*/
			switch(Port_PinConfig[PinIndex].PortId){
			case PortConf_PORT_A:
				Port_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
				break;
			case PortConf_PORT_B:
				Port_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
				break;
			case PortConf_PORT_C:
				Port_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				break;
			case PortConf_PORT_D:
				Port_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
				break;
			case PortConf_PORT_E:
				Port_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
				break;
			case PortConf_PORT_F:
				Port_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
				break;
			default: 
				/* No Action Required */
				break;
			}
			if(Port_Ptr!=NULL_PTR){
				/* Enable clock for PORT and allow time for clock to start*/
				SYSCTL_REGCGC2_REG |= (1 << Port_PinConfig[PinIndex].PortId);
				delay = SYSCTL_REGCGC2_REG;

				if((PinIndex==PORT_D_PIN_7_INDEX)||(PinIndex==PORT_F_PIN_0_INDEX)){ /*For PD7 PF0*/
					/* Unlock the GPIOCR register */ 
					*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_LOCK_REG_OFFSET) = UNLOCK_GPIOCR_REG;
					/* Set the corresponding bit in GPIOCR register to allow changes on this pin */
					SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_COMMIT_REG_OFFSET),Port_PinConfig[PinIndex].PinId );
				}else{
				/* Do Nothing ... No need to unlock the commit register for this pin */			}
				if(PinIndex>=PORT_C_PIN_0_INDEX&&PinIndex<=PORT_C_PIN_3_INDEX){
					/*Do No thing .... PINS FOR JTAG CONNECTION !*/
				}else{
					/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
					CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinConfig[PinIndex].PinId);

					/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinConfig[PinIndex].PinId);
					/*Set Required mode*/

					/* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[PinIndex].PinId);
					switch(Port_PinConfig[PinIndex].PortPinMode){

					case PORT_PIN_MODE_DIO:
						/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[PinIndex].PinId);
						/* Set the number of dio mode for this pin by clear the corresponding bits in PMX register */
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= (PORT_PIN_MODE_DIO_MASK<< (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_UART_1:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						if((Port_PinConfig[PinIndex].PortPinMode==PORT_PIN_MODE_UART_1)/*Special  UART1 mode number For PC4 PC5 */
								&&(PinIndex==PORT_C_PIN_4_INDEX||PinIndex==PORT_C_PIN_5_INDEX)){
							*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_1_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						}else{
							*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						}
						break;
					case PORT_PIN_MODE_UART_0:
					case PORT_PIN_MODE_UART_2:
					case PORT_PIN_MODE_UART_3:
					case PORT_PIN_MODE_UART_4:
					case PORT_PIN_MODE_UART_5:
					case PORT_PIN_MODE_UART_6:
					case PORT_PIN_MODE_UART_7:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_SSI_0 :
					case PORT_PIN_MODE_SSI_1 :
					case PORT_PIN_MODE_SSI_2 :
					case PORT_PIN_MODE_SSI_3 :
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_SSI_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_I2C_0:
					case PORT_PIN_MODE_I2C_1:
					case PORT_PIN_MODE_I2C_2:
					case PORT_PIN_MODE_I2C_3:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_I2C_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_PWM_0:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM_0_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_PWM_1:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM_1_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_GPT:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_GPT_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_CAN_0:
						if((Port_PinConfig[PinIndex].PortPinMode==PORT_PIN_MODE_CAN_0) /*Special Can0 mode number for PF0 PF3 */
								&&(PinIndex==PORT_F_PIN_0_INDEX||PinIndex==PORT_F_PIN_3_INDEX)){
							*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_0_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						}else{
							*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						}
						break;
					case PORT_PIN_MODE_CAN_1:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_NMI:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_NMI_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_USB:
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_NMI_MASK << (Port_PinConfig[PinIndex].PinId * 4));
						break;
					case PORT_PIN_MODE_ADC:
						/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[PinIndex].PinId);
						/* CLEAR the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinConfig[PinIndex].PinId);
						/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
						SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						/* Set the corresponding bit in the GPIOADCCTL register to to enable ADC trigger */
						SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_ADC_CTL_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						break;
					default:
                                                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[PinIndex].PinId);
						/* Set the number of dio mode for this pin by clear the corresponding bits in PMX register */
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= (PORT_PIN_MODE_DIO_MASK<< (Port_PinConfig[PinIndex].PinId * 4));
						break;
					}
					/*Set Pin Direction*/
					if ((Port_PinConfig[PinIndex].PortPinDirection == PORT_PIN_OUT)) {
						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
						SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						if (Port_PinConfig[PinIndex].PortPinIntialValue== STD_HIGH) {

							/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						}else{

							/* Set the corresponding bit in the GPIODATA register to provide initial value 0 */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						} 
						/* Set the corresponding bit in the GPIODR8R register to set the requried cuurent */
						if(Port_PinConfig[PinIndex].Current==MA_8){
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_8MA_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						}else if(Port_PinConfig[PinIndex].Current==MA_4){
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_4MA_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						}else{ 
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_2MA_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						}
					}else if ((Port_PinConfig[PinIndex].PortPinDirection== PORT_PIN_IN)) {

						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
						CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						if (Port_PinConfig[PinIndex].PortPinInternalResistor == PULL_UP) {
							/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[PinIndex].PinId); 
						}else if(Port_PinConfig[PinIndex].PortPinInternalResistor == PULL_DOWN) {
							/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						} else{
							/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[PinIndex].PinId); 
							/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						}
					}else{
						/* Do Nothing */
					}


				}
			}
			else{
						/* Do Nothing */
			}
		}
	}else{
		/*No action Required*/ 
	}

}

/************************************************************************************
 * Service Name: Port_SetPinDirection 
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number 
 Direction - Port Pin Direction 
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin direction  
 ************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection(
		Port_PinType Pin, 
		Port_PinDirectionType Direction
) 
{

	volatile uint32 *Port_Ptr = NULL_PTR;
	boolean error =FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if Port is intialized */
	if (Port_Status == PORT_NOT_INITIALIZED) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	} else{
		/*No Action Required */
	}

	/* Check if Pin Id is valid */
	if (PORT_NUMBER_OF_PORT_PINS<=Pin) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	} else{
		/*No Action Required */
	}

	/* Check if Pin is Changeable*/
	if (Port_PinConfig[Pin].PortPinDirectionChangeable==CHANGEABLE_DISABLE){
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
	} else{
		/*No Action Required */
	}

#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	/*select the required port*/
	if(FALSE==error){
		switch(Port_PinConfig[Pin].PortId){
		case PortConf_PORT_A:
			Port_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			break;
		case PortConf_PORT_B:
			Port_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
			break;
		case PortConf_PORT_C:
			Port_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
			break;
		case PortConf_PORT_D:
			Port_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
			break;
		case PortConf_PORT_E:
			Port_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
			break;
		case PortConf_PORT_F:
			Port_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
			break;
		default: 
			/* No Action Required */
			break;
		}
		if(Pin>=PORT_C_PIN_0_INDEX&&Pin<=PORT_C_PIN_3_INDEX){
			/*Do No thing .... PINS FOR JTAG CONNECTION !*/
		}else{
			if ((Direction == PORT_PIN_OUT)) {
				/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
				CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[Pin].PinId); 
				/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
				CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[Pin].PinId);
				/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[Pin].PinId);
				if (Port_PinConfig[Pin].PortPinIntialValue== STD_HIGH) {
					/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
					SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[Pin].PinId);
				}else{

					/* Set the corresponding bit in the GPIODATA register to provide initial value 0 */
					CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[Pin].PinId);
				} 
			}else if ((Direction== PORT_PIN_IN)) {

				/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[Pin].PinId);
				if (Port_PinConfig[Pin].PortPinInternalResistor == PULL_UP) {
					/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
					SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[Pin].PinId); 
				}else if(Port_PinConfig[Pin].PortPinInternalResistor == PULL_DOWN) {
					/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
					SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[Pin].PinId);
				} else{
					/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
					CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[Pin].PinId); 
					/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
					CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[Pin].PinId);
				}
			}else{
				/* Do Nothing */
			}

		}
	}
	else{
		/* Do Nothing */
	}



}

#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection  
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Refreshe port direction
 ************************************************************************************/
void Port_RefreshPortDirection(void) {
	volatile uint32 *Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
	volatile uint32 delay = 0;
	Port_PinType PinIndex = 0;
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if Port is intialized */
	if (Port_Status == PORT_NOT_INITIALIZED) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	} else{
		/*No Action Required */
	}
#endif
	if(error==FALSE){
		for (PinIndex = 0; PinIndex < PORT_NUMBER_OF_PORT_PINS; PinIndex++){
			/*select the required port*/
			if(Port_PinConfig[PinIndex].PortPinDirectionChangeable==CHANGEABLE_ENABLE){
				switch(Port_PinConfig[PinIndex].PortId){
				case PortConf_PORT_A:
					Port_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					break;
				case PortConf_PORT_B:
					Port_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					break;
				case PortConf_PORT_C:
					Port_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
					break;
				case PortConf_PORT_D:
					Port_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					break;
				case PortConf_PORT_E:
					Port_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					break;
				case PortConf_PORT_F:
					Port_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					break;
				default: 
					/* No Action Required */
					break;
				}
				if(PinIndex>=PORT_C_PIN_0_INDEX&&PinIndex<=PORT_C_PIN_3_INDEX){
					/*Do No thing .... PINS FOR JTAG CONNECTION !*/
				}else{
					if ((Port_PinConfig[PinIndex].PortPinDirection == PORT_PIN_OUT)) {
						/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
						CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[PinIndex].PinId); 
						/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
						CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
						SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						if (Port_PinConfig[PinIndex].PortPinIntialValue== STD_HIGH) {

							/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						}else{

							/* Set the corresponding bit in the GPIODATA register to provide initial value 0 */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DATA_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						} 
					}else if ((Port_PinConfig[PinIndex].PortPinDirection== PORT_PIN_IN)) {

						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
						CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_DIR_REG_OFFSET), Port_PinConfig[PinIndex].PinId);
						if (Port_PinConfig[PinIndex].PortPinInternalResistor == PULL_UP) {
							/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[PinIndex].PinId); 
						}else if(Port_PinConfig[PinIndex].PortPinInternalResistor == PULL_DOWN) {
							/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
							SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						} else{
							/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_UP_REG_OFFSET),Port_PinConfig[PinIndex].PinId); 
							/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
							CLEAR_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_PULL_DOWN_REG_OFFSET),Port_PinConfig[PinIndex].PinId);
						}
					}else{
						/* Do Nothing */
					}
				}
			}else{
				/*No action required*/
			}
		}
	}else{
		/*No action required*/
	}

}

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == versioninfo) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
				PORT_E_PARAM_POINTER);
	} else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16) PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16) PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8) PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8) PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8) PORT_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin  : Port Pin ID number Parameters  
 Mode : New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to Set the port pin mode. 
 ************************************************************************************/

#if (PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode(
		Port_PinType Pin,
		Port_PinModeType Mode
) 
{

	volatile uint32 *Port_Ptr = NULL_PTR;
	boolean error =FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if Port is intialized */
	if (Port_Status == PORT_NOT_INITIALIZED) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	} else{
		/*No Action Required */
	}

	/* Check if Pin Id is valid */
	if (PORT_NUMBER_OF_PORT_PINS<=Pin) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	} else{
		/*No Action Required */
	}

	/* Check if mode is Changeable*/
	if (Port_PinConfig[Pin].PortPinModeChangeable==CHANGEABLE_DISABLE){
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_MODE_UNCHANGEABLE); 
		error = TRUE;
	} else{
		/*No Action Required */
	}
        	/* Check if Pin Id is valid */
	if (NUMBEROFMODES<=Mode) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
	} else{
		/*No Action Required */
	}

#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	/*select the required port*/
	if(FALSE==error){
		switch(Port_PinConfig[Pin].PortId){
		case PortConf_PORT_A:
			Port_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			break;
		case PortConf_PORT_B:
			Port_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
			break;
		case PortConf_PORT_C:
			Port_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
			break;
		case PortConf_PORT_D:
			Port_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
			break;
		case PortConf_PORT_E:
			Port_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
			break;
		case PortConf_PORT_F:
			Port_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
			break;
		default: 
			/* No Action Required */
			break;
		}

		if(Pin>=PORT_C_PIN_0_INDEX&&Pin<=PORT_C_PIN_3_INDEX){
			/*Do No thing .... PINS FOR JTAG CONNECTION !*/
		}else{
			/*Set Required mode*/
			switch(Port_PinConfig[Pin].PortPinMode){

			case PORT_PIN_MODE_DIO:
				/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[Pin].PinId);
				/* Set the number of dio mode for this pin by clear the corresponding bits in PMX register */
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= (PORT_PIN_MODE_DIO_MASK<< (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_UART_1:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[Pin].PinId * 4));
				if((Port_PinConfig[Pin].PortPinMode==PORT_PIN_MODE_UART_1)/*Special  UART1 mode number For PC4 PC5 */
						&&(Pin==PORT_C_PIN_4_INDEX||Pin==PORT_C_PIN_5_INDEX)){
					*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_1_MASK << (Port_PinConfig[Pin].PinId * 4));
				}else{
					*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[Pin].PinId * 4));
				}
				break;
			case PORT_PIN_MODE_UART_0:
			case PORT_PIN_MODE_UART_2:
			case PORT_PIN_MODE_UART_3:
			case PORT_PIN_MODE_UART_4:
			case PORT_PIN_MODE_UART_5:
			case PORT_PIN_MODE_UART_6:
			case PORT_PIN_MODE_UART_7:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_SSI_0 :
			case PORT_PIN_MODE_SSI_1 :
			case PORT_PIN_MODE_SSI_2 :
			case PORT_PIN_MODE_SSI_3 :
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_SSI_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_I2C_0:
			case PORT_PIN_MODE_I2C_1:
			case PORT_PIN_MODE_I2C_2:
			case PORT_PIN_MODE_I2C_3:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_I2C_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_PWM_0:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM_0_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_PWM_1:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM_1_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_GPT:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_GPT_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_CAN_0:
				if((Port_PinConfig[Pin].PortPinMode==PORT_PIN_MODE_CAN_0) /*Special Can0 mode number for PF0 PF3 */
						&&(Pin==PORT_F_PIN_0_INDEX||Pin==PORT_F_PIN_3_INDEX)){
					*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_0_MASK << (Port_PinConfig[Pin].PinId * 4));
				}else{
					*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_MASK << (Port_PinConfig[Pin].PinId * 4));
				}
				break;
			case PORT_PIN_MODE_CAN_1:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_NMI:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_NMI_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_USB:
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_NMI_MASK << (Port_PinConfig[Pin].PinId * 4));
				break;
			case PORT_PIN_MODE_ADC:
				/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Port_PinConfig[Pin].PinId);
				/* CLEAR the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinConfig[Pin].PinId);
				/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
				SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinConfig[Pin].PinId);
				/* Set the corresponding bit in the GPIOADCCTL register to to enable ADC trigger */
				SET_BIT(*(volatile uint32*) ((volatile uint8*) Port_Ptr+ PORT_ADC_CTL_REG_OFFSET), Port_PinConfig[Pin].PinId);
				break;
			default: 
				/*No action required*/
				break;
			}
		}
	}else{
		/*No action Required*/

	}

}

#endif

