 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Abdelrahman  Tarek
 *
 *******************************************************************************/

#ifndef PORT_Cfg_H
#define PORT_Cfg_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES                (39U)
 /* Channel Index in the array of structures in Port_PBcfg.c */
#define PortConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define PortConf_SW1_CHANNEL_ID_INDEX         (uint8)0x01

/* DIO Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                (Port_Number)PORTF /* PORTF */
#define PortConf_SW1_PORT_NUM                 (Port_Number)PORTF /* PORTF */

/* DIO Configured Channel ID's */
#define PortConf_LED1_CHANNEL_NUM             (Port_PinType)1 /* Pin 1 in PORTF */
#define PortConf_SW1_CHANNEL_NUM              (Port_PinType)4 /* Pin 4 in PORTF */

#endif /* PORT_Cfg_H */
