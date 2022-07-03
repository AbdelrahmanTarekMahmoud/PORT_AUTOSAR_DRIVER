 /******************************************************************************
 *
 * Module: Port 
 * File Name: Port_PBcfg.c
 *
 * Description: Source file for Port Post Build configurations
 *              on TM4C123GH6PM Microcontroller
 *
 * Author: Abdelrahman  Tarek
 *
 *******************************************************************************/

#ifndef PORT_PBcfg_H
#define PORT_PBcfg_H

#include "PORT.h"
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif
   
   const Port_ConfigType Port_Configuration = {
                                               /*First we will write the used Pins in the project PF1(LED1) AND PF4(SW1)*/
                                                PortConf_LED1_CHANNEL_NUM,PortConf_LED1_PORT_NUM,PORT_PIN_OUT,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_HIGH, /*LED*/
                                               PortConf_SW1_CHANNEL_NUM ,PortConf_SW1_PORT_NUM,PORT_PIN_IN,DIO_PIN,PULL_UP,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW, /*SW*/
                                                                                                  /*PORT A*/
                                                PORT_A_PIN_0,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_1,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_2,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_3,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_4,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_5,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_6,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_A_PIN_7,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                                                              /*PORT B*/
                                                PORT_B_PIN_0,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_1,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_2,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_3,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_4,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_5,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_6,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_B_PIN_7,PORTB,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,                                              
                                                                                           /*PORT C (Excluded Jtag pins 0 > 3)*/
                                                PORT_C_PIN_4,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_C_PIN_5,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_C_PIN_6,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_C_PIN_7,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,   
                                                                                             /*PORT D*/
                                                PORT_D_PIN_0,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_1,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_2,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_3,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_4,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_5,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_6,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_D_PIN_7,PORTD,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,   
                                                                            /*PORT E (Excluded pin 6&7 Because they dont exist in Tiva C)*/
                                                PORT_E_PIN_0,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_E_PIN_1,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_E_PIN_2,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_E_PIN_3,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_E_PIN_4,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_E_PIN_5,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                                      /*PORT F (Excluded PF1 & PF4 WE CONFIGURED THEM BEFORE (5>>7 Dont exist in Tiva too))*/
                                                PORT_F_PIN_0,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_F_PIN_2,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                                PORT_F_PIN_3,PORTA,PORT_PIN_IN,DIO_PIN,OFF,DIRECTION_NOTCHANGEABLE,MODE_NOTCHANGEABLE,INITIAL_VALUE_LOW,
                                               
   
                                              };


#endif /*  PORT_PBcfg_H */
