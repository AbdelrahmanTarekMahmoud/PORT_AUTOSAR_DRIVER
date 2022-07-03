 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Abdelrahman Tarek
 ******************************************************************************/
#ifndef PORT_H
#define PORT_H
/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1222U)

/* Dio Module Id */
#define PORT_MODULE_ID    (222U)

/* Dio Instance Id */
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
 * Macros for Dio Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"
   
   /******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
#define Port_Init_SID                           (uint8)0x00
#define Port_SetPinDirection_SID                (uint8)0x01
#define Port_RefreshPortDirection_SID           (uint8)0x02
#define Port_GetVersionInfo_SID                 (uint8)0x03
#define Port_SetPinMode_SID                     (uint8)0x04
   /*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
   /*Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN     (uint8)0x0A
   /*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B
   /*API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG    (uint8)0x0C
   /*API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE     (uint8)0x0D
   /*API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_MODE_UNCHANGEABLE    (uint8)0x0E
   /*API service called without module initialization*/
#define PORT_E_UNINIT    (uint8)0x0F
   /*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER   (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
   /*Data type for the symbolic name of a port pin.*/
   typedef uint8 Port_PinType;
   /*Different port pin modes.*/
   typedef uint8 Port_PinModeType;
   /*Possible directions of a port pin.*/   
   typedef enum 
   {
     PORT_PIN_IN,
     PORT_PIN_OUT
   }Port_PinDirectionType;
    /*Possible Resistors of a port pin.*/ 
   typedef enum
   {
     OFF,
     PULL_UP,
     PULL_DOWN
   }Port_InternalResistor;
   typedef enum{

/********* Alternative function = 0,  Pin used as DIO  **************/
    DIO_PIN                     = 0, //!< DIO_PIN
/********************************************************************/

/******** Alternative Function  = 1 For all Pins that have it *******/
    PORT_A_PIN_0_AF1_U0RX       = 1, //!< PORT_A_PIN_0_AF1_U0RX
    PORT_A_PIN_1_AF1_U0TX       = 1, //!< PORT_A_PIN_1_AF1_U0TX

    PORT_B_PIN_0_AF1_U1RX       = 1, //!< PORT_B_PIN_0_AF1_U1RX
    PORT_B_PIN_1_AF1_U1TX       = 1, //!< PORT_B_PIN_1_AF1_U1TX

    PORT_C_PIN_4_AF1_U4RX       = 1, //!< PORT_C_PIN_4_AF1_U4RX
    PORT_C_PIN_5_AF1_U4TX       = 1, //!< PORT_C_PIN_5_AF1_U4TX
    PORT_C_PIN_6_AF1_U3RX       = 1, //!< PORT_C_PIN_6_AF1_U3RX
    PORT_C_PIN_7_AF1_U3TX       = 1, //!< PORT_C_PIN_7_AF1_U3TX

    PORT_D_PIN_0_AF1_SSI3CLK    = 1, //!< PORT_D_PIN_0_AF1_SSI3CLK
    PORT_D_PIN_1_AF1_SSI3FSS    = 1, //!< PORT_D_PIN_1_AF1_SSI3FSS
    PORT_D_PIN_2_AF1_SSI3RX     = 1, //!< PORT_D_PIN_2_AF1_SSI3RX
    PORT_D_PIN_3_AF1_SSI3TX     = 1, //!< PORT_D_PIN_3_AF1_SSI3TX
    PORT_D_PIN_4_AF1_U6RX       = 1, //!< PORT_D_PIN_4_AF1_U6RX
    PORT_D_PIN_5_AF1_U6TX       = 1, //!< PORT_D_PIN_5_AF1_U6TX
    PORT_D_PIN_6_AF1_U2RX       = 1, //!< PORT_D_PIN_6_AF1_U2RX
    PORT_D_PIN_7_AF1_U2TX       = 1, //!< PORT_D_PIN_7_AF1_U2TX

    PORT_E_PIN_0_AF1_U7RX       = 1, //!< PORT_E_PIN_0_AF1_U7RX
    PORT_E_PIN_1_AF1_U7TX       = 1, //!< PORT_E_PIN_1_AF1_U7TX
    PORT_E_PIN_4_AF1_U5RX       = 1, //!< PORT_E_PIN_4_AF1_U5RX
    PORT_E_PIN_5_AF1_U5TX       = 1, //!< PORT_E_PIN_5_AF1_U5TX

    PORT_F_PIN_0_AF1_U1RTS      = 1, //!< PORT_F_PIN_0_AF1_U1RTS
    PORT_F_PIN_1_AF1_U1CTS      = 1, //!< PORT_F_PIN_1_AF1_U1CTS
/********************************************************************/

/******** Alternative Function  = 2 For all Pins that have it *******/
    PORT_A_PIN_2_AF2_SSI0CLK    = 2, //!< PORT_A_PIN_2_AF2_SSI0CLK
    PORT_A_PIN_3_AF2_SSI0FSS    = 2, //!< PORT_A_PIN_3_AF2_SSI0FSS
    PORT_A_PIN_4_AF2_SSI0RX     = 2, //!< PORT_A_PIN_4_AF2_SSI0RX
    PORT_A_PIN_5_AF2_SSI0TX     = 2, //!< PORT_A_PIN_5_AF2_SSI0TX

    PORT_B_PIN_4_AF2_SSI2CLK    = 2, //!< PORT_B_PIN_4_AF2_SSI2CLK
    PORT_B_PIN_5_AF2_SSI2FSS    = 2, //!< PORT_B_PIN_5_AF2_SSI2FSS
    PORT_B_PIN_6_AF2_SSI2RX     = 2, //!< PORT_B_PIN_6_AF2_SSI2RX
    PORT_B_PIN_7_AF2_SSI2TX     = 2, //!< PORT_B_PIN_7_AF2_SSI2TX

    PORT_C_PIN_4_AF2_U1RX       = 2, //!< PORT_C_PIN_4_AF2_U1RX
    PORT_C_PIN_5_AF2_U1TX       = 2, //!< PORT_C_PIN_5_AF2_U1TX

    PORT_D_PIN_0_AF2_SSI1CLK    = 2, //!< PORT_D_PIN_0_AF2_SSI1CLK
    PORT_D_PIN_1_AF2_SSI1FSS    = 2, //!< PORT_D_PIN_1_AF2_SSI1FSS
    PORT_D_PIN_2_AF2_SSI1RX     = 2, //!< PORT_D_PIN_2_AF2_SSI1RX
    PORT_D_PIN_3_AF2_SSI1TX     = 2, //!< PORT_D_PIN_3_AF2_SSI1TX

    PORT_F_PIN_0_AF2_SSI1RX     = 2, //!< PORT_F_PIN_0_AF2_SSI1RX
    PORT_F_PIN_1_AF2_SSI1TX     = 2, //!< PORT_F_PIN_1_AF2_SSI1TX
    PORT_F_PIN_2_AF2_SSI1CLK    = 2, //!< PORT_F_PIN_2_AF2_SSI1CLK
    PORT_F_PIN_3_AF2_SSI1FSS    = 2, //!< PORT_F_PIN_3_AF2_SSI1FSS
/********************************************************************/

/******** Alternative Function  = 3 For all Pins that have it *******/
    PORT_A_PIN_6_AF3_I2C1SCL    = 3, //!< PORT_A_PIN_6_AF3_I2C1SCL
    PORT_A_PIN_7_AF3_I2C1SDA    = 3, //!< PORT_A_PIN_7_AF3_I2C1SDA

    PORT_B_PIN_2_AF3_I2C0SCL    = 3, //!< PORT_B_PIN_2_AF3_I2C0SCL
    PORT_B_PIN_3_AF3_I2C0SDA    = 3, //!< PORT_B_PIN_3_AF3_I2C0SDA


    PORT_D_PIN_0_AF3_I2C3SCL    = 3, //!< PORT_D_PIN_0_AF3_I2C3SCL
    PORT_D_PIN_1_AF3_I2C3SDA    = 3, //!< PORT_D_PIN_1_AF3_I2C3SDA

    PORT_E_PIN_4_AF3_I2C2SCL    = 3, //!< PORT_E_PIN_4_AF3_I2C2SCL
    PORT_E_PIN_5_AF3_I2C2SDA    = 3, //!< PORT_E_PIN_5_AF3_I2C2SDA

    PORT_F_PIN_0_AF3_CAN0RX     = 3, //!< PORT_F_PIN_0_AF3_CAN0RX
    PORT_F_PIN_3_AF3_CAN0TX     = 3, //!< PORT_F_PIN_3_AF3_CAN0TX
/********************************************************************/

/******** Alternative Function  = 4 For all Pins that have it *******/

    PORT_B_PIN_4_AF4_M0PWM2     = 4, //!< PORT_B_PIN_4_AF4_M0PWM2
    PORT_B_PIN_5_AF4_M0PWM3     = 4, //!< PORT_B_PIN_5_AF4_M0PWM3
    PORT_B_PIN_6_AF4_M0PWM0     = 4, //!< PORT_B_PIN_6_AF4_M0PWM0
    PORT_B_PIN_7_AF4_M0PWM1     = 4, //!< PORT_B_PIN_7_AF4_M0PWM1

    PORT_C_PIN_4_AF4_M0PWM6     = 4, //!< PORT_C_PIN_4_AF4_M0PWM6
    PORT_C_PIN_5_AF4_M0PWM7     = 4, //!< PORT_C_PIN_5_AF4_M0PWM7

    PORT_D_PIN_0_AF4_M0PWM6     = 4, //!< PORT_D_PIN_0_AF4_M0PWM6
    PORT_D_PIN_1_AF4_M0PWM7     = 4, //!< PORT_D_PIN_1_AF4_M0PWM7
    PORT_D_PIN_2_AF4_M0FAULT0   = 4, //!< PORT_D_PIN_2_AF4_M0FAULT0
    PORT_D_PIN_6_AF4_M0FAULT0   = 4, //!< PORT_D_PIN_6_AF4_M0FAULT0

    PORT_E_PIN_4_AF4_M0PWM4     = 4, //!< PORT_E_PIN_4_AF4_M0PWM4
    PORT_E_PIN_5_AF4_M0PWM5     = 4, //!< PORT_E_PIN_5_AF4_M0PWM5

    PORT_F_PIN_2_AF4_M0FAULT0   = 4, //!< PORT_F_PIN_2_AF4_M0FAULT0
/********************************************************************/

/******** Alternative Function  = 5 For all Pins that have it *******/
    PORT_A_PIN_6_AF5_M1PWM2     = 5, //!< PORT_A_PIN_6_AF5_M1PWM2
    PORT_A_PIN_7_AF5_M1PWM3     = 5, //!< PORT_A_PIN_7_AF5_M1PWM3

    PORT_D_PIN_0_AF5_M1PWM0     = 5, //!< PORT_D_PIN_0_AF5_M1PWM0
    PORT_D_PIN_1_AF5_M1PWM1     = 5, //!< PORT_D_PIN_1_AF5_M1PWM1

    PORT_E_PIN_4_AF5_M1PWM2     = 5, //!< PORT_E_PIN_4_AF5_M1PWM2
    PORT_E_PIN_5_AF5_M1PWM3     = 5, //!< PORT_E_PIN_5_AF5_M1PWM3

    PORT_F_PIN_0_AF5_M1PWM4     = 5, //!< PORT_F_PIN_0_AF5_M1PWM4
    PORT_F_PIN_1_AF5_M1PWM5     = 5, //!< PORT_F_PIN_1_AF5_M1PWM5
    PORT_F_PIN_2_AF5_M1PWM6     = 5, //!< PORT_F_PIN_2_AF5_M1PWM6
    PORT_F_PIN_3_AF5_M1PWM7     = 5, //!< PORT_F_PIN_3_AF5_M1PWM7
    PORT_F_PIN_4_AF5_M1FAULT0   = 5, //!< PORT_F_PIN_4_AF5_M1FAULT0
/********************************************************************/

/******** Alternative Function  = 6 For all Pins that have it *******/
    PORT_C_PIN_4_AF6_IDX1       = 6, //!< PORT_C_PIN_4_AF6_IDX1
    PORT_C_PIN_5_AF6_PHA1       = 6, //!< PORT_C_PIN_5_AF6_PHA1
    PORT_C_PIN_6_AF6_PHB1       = 6, //!< PORT_C_PIN_6_AF6_PHB1

    PORT_D_PIN_3_AF6_IDX0       = 6, //!< PORT_D_PIN_3_AF6_IDX0
    PORT_D_PIN_6_AF6_PHA0       = 6, //!< PORT_D_PIN_6_AF6_PHA0
    PORT_D_PIN_7_AF6_PHB0       = 6, //!< PORT_D_PIN_7_AF6_PHB0

    PORT_F_PIN_0_AF6_PHA0       = 6, //!< PORT_F_PIN_0_AF6_PHA0
    PORT_F_PIN_1_AF6_PHB0       = 6, //!< PORT_F_PIN_1_AF6_PHB0
    PORT_F_PIN_4_AF6_IDX0       = 6, //!< PORT_F_PIN_4_AF6_IDX0
/********************************************************************/

/******** Alternative Function  = 7 For all Pins that have it *******/
    PORT_B_PIN_0_AF7_T2CCP0     = 7, //!< PORT_B_PIN_0_AF7_T2CCP0
    PORT_B_PIN_1_AF7_T2CCP1     = 7, //!< PORT_B_PIN_1_AF7_T2CCP1
    PORT_B_PIN_2_AF7_T3CCP0     = 7, //!< PORT_B_PIN_2_AF7_T3CCP0
    PORT_B_PIN_3_AF7_T3CCP1     = 7, //!< PORT_B_PIN_3_AF7_T3CCP1
    PORT_B_PIN_4_AF7_T1CCP0     = 7, //!< PORT_B_PIN_4_AF7_T1CCP0
    PORT_B_PIN_5_AF7_T1CCP1     = 7, //!< PORT_B_PIN_5_AF7_T1CCP1
    PORT_B_PIN_6_AF7_T0CCP0     = 7, //!< PORT_B_PIN_6_AF7_T0CCP0
    PORT_B_PIN_7_AF7_T0CCP1     = 7, //!< PORT_B_PIN_7_AF7_T0CCP1

    PORT_C_PIN_4_AF7_WT0CCP0    = 7, //!< PORT_C_PIN_4_AF7_WT0CCP0
    PORT_C_PIN_5_AF7_WT0CCP1    = 7, //!< PORT_C_PIN_5_AF7_WT0CCP1
    PORT_C_PIN_6_AF7_WT1CCP0    = 7, //!< PORT_C_PIN_6_AF7_WT1CCP0
    PORT_C_PIN_7_AF7_WT1CCP1    = 7, //!< PORT_C_PIN_7_AF7_WT1CCP1

    PORT_D_PIN_0_AF7_WT2CCP0    = 7, //!< PORT_D_PIN_0_AF7_WT2CCP0
    PORT_D_PIN_1_AF7_WT2CCP1    = 7, //!< PORT_D_PIN_1_AF7_WT2CCP1
    PORT_D_PIN_2_AF7_WT3CCP0    = 7, //!< PORT_D_PIN_2_AF7_WT3CCP0
    PORT_D_PIN_3_AF7_WT3CCP1    = 7, //!< PORT_D_PIN_3_AF7_WT3CCP1
    PORT_D_PIN_4_AF7_WT4CCP0    = 7, //!< PORT_D_PIN_4_AF7_WT4CCP0
    PORT_D_PIN_5_AF7_WT4CCP1    = 7, //!< PORT_D_PIN_5_AF7_WT4CCP1
    PORT_D_PIN_6_AF7_WT5CCP0    = 7, //!< PORT_D_PIN_6_AF7_WT5CCP0
    PORT_D_PIN_7_AF7_WT5CCP1    = 7, //!< PORT_D_PIN_7_AF7_WT5CCP1

    PORT_F_PIN_0_AF7_T0CCP0     = 7, //!< PORT_F_PIN_0_AF7_T0CCP0
    PORT_F_PIN_1_AF7_T0CCP1     = 7, //!< PORT_F_PIN_1_AF7_T0CCP1
    PORT_F_PIN_2_AF7_T1CCP0     = 7, //!< PORT_F_PIN_2_AF7_T1CCP0
    PORT_F_PIN_3_AF7_T1CCP1     = 7, //!< PORT_F_PIN_3_AF7_T1CCP1
    PORT_F_PIN_4_AF7_T2CCP0     = 7, //!< PORT_F_PIN_4_AF7_T2CCP0
/********************************************************************/

/******** Alternative Function  = 8 For all Pins that have it *******/
    PORT_A_PIN_0_AF8_CAN1RX     = 8, //!< PORT_A_PIN_0_AF8_CAN1RX
    PORT_A_PIN_1_AF8_CAN1TX     = 8, //!< PORT_A_PIN_1_AF8_CAN1TX

    PORT_B_PIN_4_AF8_CAN0RX     = 8, //!< PORT_B_PIN_4_AF8_CAN0RX
    PORT_B_PIN_5_AF8_CAN0TX     = 8, //!< PORT_B_PIN_5_AF8_CAN0TX

    PORT_C_PIN_4_AF8_U1RTS      = 8, //!< PORT_C_PIN_4_AF8_U1RTS
    PORT_C_PIN_5_AF8_U1CTS      = 8, //!< PORT_C_PIN_5_AF8_U1CTS
    PORT_C_PIN_6_AF8_USB0EPEN   = 8, //!< PORT_C_PIN_6_AF8_USB0EPEN
    PORT_C_PIN_7_AF8_USB0PFLT   = 8, //!< PORT_C_PIN_7_AF8_USB0PFLT

    PORT_D_PIN_2_AF8_USB0EPEN   = 8, //!< PORT_D_PIN_2_AF8_USB0EPEN
    PORT_D_PIN_3_AF8_USB0PFLT   = 8, //!< PORT_D_PIN_3_AF8_USB0PFLT
    PORT_D_PIN_7_AF8_NMI        = 8, //!< PORT_D_PIN_7_AF8_NMI

    PORT_E_PIN_4_AF8_CAN0RX     = 8, //!< PORT_E_PIN_4_AF8_CAN0RX
    PORT_E_PIN_5_AF8_CAN0TX     = 8, //!< PORT_E_PIN_5_AF8_CAN0TX

    PORT_F_PIN_0_AF8_NMI        = 8, //!< PORT_F_PIN_0_AF8_NMI
    PORT_F_PIN_4_AF8_USB0EPEN   = 8, //!< PORT_F_PIN_4_AF8_USB0EPEN
/*********************************************************************/

/******** Alternative Function  = 9 For all Pins that have it ********/
    PORT_F_PIN_0_AF9_C0O        = 9, //!< PORT_F_PIN_0_AF9_C0O
    PORT_F_PIN_1_AF9_C01        = 9, //!< PORT_F_PIN_1_AF9_C01
/*********************************************************************/

/************* There are NO Alternative Functions = 10 ***************/

/************* There are NO Alternative Functions = 11 ***************/

/************* There are NO Alternative Functions = 12 ***************/

/************* There are NO Alternative Functions = 13 ***************/

/******** Alternative Function  = 14 For all Pins that have it *******/
    PORT_F_PIN_1_AF14_TRD1      = 14,//!< PORT_F_PIN_1_AF14_TRD1
    PORT_F_PIN_2_AF14_TRD0      = 14,//!< PORT_F_PIN_2_AF14_TRD0
    PORT_F_PIN_3_AF14_TRCLK     = 14,//!< PORT_F_PIN_3_AF14_TRCLK
/*********************************************************************/

}Port_PinAltMode;
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    PORT_A_PIN_0                = 0, //!< PORT_A_PIN_0
    PORT_A_PIN_1                = 1, //!< PORT_A_PIN_1
    PORT_A_PIN_2                = 2, //!< PORT_A_PIN_2
    PORT_A_PIN_3                = 3, //!< PORT_A_PIN_3
    PORT_A_PIN_4                = 4, //!< PORT_A_PIN_4
    PORT_A_PIN_5                = 5, //!< PORT_A_PIN_5
    PORT_A_PIN_6                = 6, //!< PORT_A_PIN_6
    PORT_A_PIN_7                = 7, //!< PORT_A_PIN_7
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    PORT_B_PIN_0                = 0, //!< PORT_B_PIN_0
    PORT_B_PIN_1                = 1, //!< PORT_B_PIN_1
    PORT_B_PIN_2                = 2,//!< PORT_B_PIN_2
    PORT_B_PIN_3                = 3,//!< PORT_B_PIN_3
    PORT_B_PIN_4                = 4,//!< PORT_B_PIN_4
    PORT_B_PIN_5                = 5,//!< PORT_B_PIN_5
    PORT_B_PIN_6                = 6,//!< PORT_B_PIN_6
    PORT_B_PIN_7                = 7,//!< PORT_B_PIN_7
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
/*
 * Note: pins From PC0 -> PC3 used for JTAG, so that they removed
 * from the Enum to avoid using them by mistake
*/

    PORT_C_PIN_4                = 4,//!< PORT_C_PIN_4
    PORT_C_PIN_5                = 5,//!< PORT_C_PIN_5
    PORT_C_PIN_6                = 6,//!< PORT_C_PIN_6
    PORT_C_PIN_7                = 7,//!< PORT_C_PIN_7
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    PORT_D_PIN_0                = 0,//!< PORT_D_PIN_0
    PORT_D_PIN_1                = 1,//!< PORT_D_PIN_1
    PORT_D_PIN_2                = 2,//!< PORT_D_PIN_2
    PORT_D_PIN_3                = 3,//!< PORT_D_PIN_3
    PORT_D_PIN_4                = 4,//!< PORT_D_PIN_4
    PORT_D_PIN_5                = 5,//!< PORT_D_PIN_5
    PORT_D_PIN_6                = 6,//!< PORT_D_PIN_6
    PORT_D_PIN_7                = 7,//!< PORT_D_PIN_7
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/
/*
 * Note: There are no Physical pins From PE6 -> PE7 so that they're
 * removed from Enum
*/
    PORT_E_PIN_0                = 0,//!< PORT_E_PIN_0
    PORT_E_PIN_1                = 1,//!< PORT_E_PIN_1
    PORT_E_PIN_2                = 2,//!< PORT_E_PIN_2
    PORT_E_PIN_3                = 3,//!< PORT_E_PIN_3
    PORT_E_PIN_4                = 4,//!< PORT_E_PIN_4
    PORT_E_PIN_5                = 5,//!< PORT_E_PIN_5
/********************************************************************/

/*********************** PORT F Pin Numbering ***********************/
/*
 * Note: There are no Physical pins From PF5 -> PF7 so that they're
 * removed from Enum
*/
    PORT_F_PIN_0                = 0,//!< PORT_F_PIN_0
    PORT_F_PIN_1                = 1,//!< PORT_F_PIN_1
    PORT_F_PIN_2                = 2,//!< PORT_F_PIN_2
    PORT_F_PIN_3                = 3,//!< PORT_F_PIN_3
    PORT_F_PIN_4                = 4 //!< PORT_F_PIN_4
/********************************************************************/
}Port_PinNumber;
   /*Enum to indentify all PORTS numbers*/
   typedef enum
   {
     PORTA,
     PORTB,
     PORTC,
     PORTD,
     PORTE,
     PORTF
   }Port_Number;
#define DIRECTION_CHANGEABLE       STD_ON
#define DIRECTION_NOTCHANGEABLE    STD_OFF
#define MODE_CHANGEABLE            STD_ON
#define MODE_NOTCHANGEABLE         STD_OFF
#define INITIAL_VALUE_HIGH         STD_HIGH
#define INITIAL_VALUE_LOW          STD_LOW
#define ANALOG_MODE                101

   /*Structure defines every specific pin by its
   1-pin number
   2-Port number
   3-its direction
   4-its mode
   5-its resistor
   6-direction can be changed or not
   7-mode can be changed or not
   8-initial value (if output)
   */
   typedef struct
   {
     Port_PinType pinNum;
     Port_Number  portNum;
     Port_PinDirectionType direction;
     Port_PinModeType pinmode;
     Port_InternalResistor resistor;
     uint8  direction_Changeable;
     uint8  mode_Changeable;
     uint8  initial_value;  
   }Port_ConfigChannel;
   /*Type of the external data structure containing the initialization data for this module.
   Which contrains Array of Strucutres */
   typedef struct
   {
     Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
   }Port_ConfigType;
   
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
 /*Initializes the Port Driver module.*/
void Port_Init( const Port_ConfigType* ConfigPtr );  
 /*Sets the port pin direction.*/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ); 
/*Refreshes port direction.*/
void Port_RefreshPortDirection( void );  
/*Returns the version information of this module.*/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
/*Sets the port pin mode.*/
 void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );                    
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
 /* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

#endif
