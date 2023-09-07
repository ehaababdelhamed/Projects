/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ehab Mohamed Abdelhamed
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ehab's ID = 2000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port init */
#define PORT_INIT_SID                      (uint8)0X00
   
 /* Service ID for Port set pin direction */  
#define PORT_SET_PIN_DIRECTION_SID         (uint8)0X01
   
   /* Service ID for Port refresh direction */
#define Port_REFRESH_PORT_DIRECTION_SID    (uint8)0X02
   
   
/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID          (uint8)0x03
   
 /* Service ID for Port set pin mode */
#define PORT_SET_PIN_MODE_SID              (uint8)0x04    
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/*Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                 (uint8)0x0A 

/*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)0x0B

/*API Port_Init service called with wrong parameter.*/
#define  PORT_E_PARAM_CONFIG             (uint8)0x0C

/*API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_PARAM_INVALID_MODE        (uint8)0x0D 

/*Invalid Mode ID requested */
#define PORT_E_MODE_UNCHANGEABLE         (uint8)0x0E

/*API service called without module initialization */
#define PORT_E_UNINIT                    (uint8)0x0F 

/*APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER             (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Data type for the symbolic name of a port pin*/
typedef uint8       Port_PinType; 

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8     Port_PinLevelType;
typedef uint8     Port_PortType;   

 

/*Possible directions of a port pin.*/
typedef enum {
  PORT_PIN_IN,
  PORT_PIN_OUT
}Port_PinDirectionType;


typedef enum
{
  MA_2,
  MA_4,
  MA_8
}PORT_PinOutputCurrentType;


/*Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_PinInternalResistorType;


 /*Different port pin modes*/
typedef enum Port_PinModeType {
PORT_PIN_MODE_DIO,          /*Port Pin configured for DIO.It shall be used under control of the DIO driver.*/ 
PORT_PIN_MODE_UART_0,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_1,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_2,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_3,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_4,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_5,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_6,   /*Port Pin used for UART*/
PORT_PIN_MODE_UART_7,   /*Port Pin used for UART*/
PORT_PIN_MODE_SSI_0 ,       /*Port Pin used by SPI 0*/ 
PORT_PIN_MODE_SSI_1,        /*Port Pin used by SPI 1*/ 
PORT_PIN_MODE_SSI_2,        /*Port Pin used by SPI 2*/
PORT_PIN_MODE_SSI_3,        /*Port Pin used by SPI 3*/
PORT_PIN_MODE_I2C_0,        /*Port Pin used for I2c 0*/
PORT_PIN_MODE_I2C_1,        /*Port Pin used for I2c 1*/
PORT_PIN_MODE_I2C_2,        /*Port Pin used for I2c 2*/
PORT_PIN_MODE_I2C_3,        /*Port Pin used for I2c 3*/
PORT_PIN_MODE_PWM_0,        /*Port Pin used by PWM MOUDLE 0*/
PORT_PIN_MODE_PWM_1,        /*Port Pin used by PWM MOUDLE 1*/
PORT_PIN_MODE_GPT,      /*Port Pin configured for GPT.*/
PORT_PIN_MODE_CAN_0,        /*Port Pin used for CAN 0*/
PORT_PIN_MODE_CAN_1,  /*Port Pin used for CAN 1*/
PORT_PIN_MODE_NMI ,          /*Port Pin used for NMI */
PORT_PIN_MODE_USB,          /*Port Pin used for USB */
PORT_PIN_MODE_ADC                   /*Port Pin used by ADC*/
}Port_PinModeType;


/*Enum to indicate if the mode/Direction is changeable */
typedef enum Port_PinChangeableType {
  CHANGEABLE_DISABLE,
  CHANGEABLE_ENABLE
}Port_PinChangeableType;


/*data structure for Configuration of the individual port pins*/
typedef struct Port_PinConfigType{
  Port_PortType PortId;
  Port_PinType PinId;
  Port_PinModeType PortPinMode;
  Port_PinDirectionType PortPinDirection;
  Port_PinLevelType PortPinIntialValue;
  PORT_PinOutputCurrentType Current;
  Port_PinInternalResistorType PortPinInternalResistor;
  Port_PinChangeableType PortPinDirectionChangeable;
  Port_PinChangeableType PortPinModeChangeable;
}Port_PinConfigType;

/*Type of the external data structure containing the initialization data for this module*/
typedef struct Port_ConfigType{
  Port_PinConfigType  PortPins[PORT_NUMBER_OF_PORT_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*Function to initialize the Port Driver module. */
void Port_Init(const Port_ConfigType *ConfigPtr);

/*Function to Set the port pin direction  */
#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection( 
 Port_PinType Pin, 
 Port_PinDirectionType Direction 
   );
#endif
/*Function to Refreshe port direction*/
void Port_RefreshPortDirection( void );

/*Function to get the version information of this module*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/*Function to Set the port pin mode*/
#if (PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode( 
 Port_PinType Pin, 
 Port_PinModeType Mode 
   );
#endif
/*******************************************************************************
 *                              Module Defination                              *
 *******************************************************************************/


#define UNLOCK_GPIOCR_REG                   0x4C4F434B /* Unlock the GPIOCR register */
#define NUMBEROFMODES                          (24U)
/*mode masking*/
#define PORT_PIN_MODE_DIO_MASK              0xFFFFFFF0         
#define PORT_PIN_MODE_UART_1_MASK           0x00000002
#define PORT_PIN_MODE_UART_MASK             0x00000001 
#define PORT_PIN_MODE_SSI_MASK              0x00000002               
#define PORT_PIN_MODE_I2C_MASK              0x00000003             
#define PORT_PIN_MODE_PWM_0_MASK            0x00000004     
#define PORT_PIN_MODE_PWM_1_MASK            0x00000005      
#define PORT_PIN_MODE_GPT_MASK              0x00000007     
#define PORT_PIN_MODE_CAN_MASK              0x00000008    
#define PORT_PIN_MODE_CAN_0_MASK            0x00000003
#define PORT_PIN_MODE_NMI_MASK              0x00000008        
#define PORT_PIN_MODE_USB_MASK              0x00000008        




/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/ 

extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */


