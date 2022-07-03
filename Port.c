 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Abdelrahman Tarek
 ******************************************************************************/
#include"PORT.h"
#include"PORT_REG.h"
#include "tm4c123gh6pm_registers.h" 

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigChannel * PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
/************************************************************************************
* Service Name:         Port_Init
* Service ID[hex]:      0x00
* Sync/Async:           Synchronous
* Reentrancy:           Non-Reentrant
* Parameters (in):      ConfigPtr - Pointer to configuration set
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function to initialize the port driver Module
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    uint8 counter = 0;
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_SID,
		PORT_E_PARAM_CONFIG);
               
	}
	else
     #endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		
		PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
	
                for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
  {
                      switch(PortChannels[counter].portNum)
    {
        case  PORTA: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
    
    /* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<PortChannels[counter].portNum);
    delay = SYSCTL_REGCGC2_REG;
    
     if( ((PortChannels[counter].portNum == 3) && (PortChannels[counter].pinNum == 7)) || ((PortChannels[counter].portNum == 5) && (PortChannels[counter].pinNum == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[counter].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PortChannels[counter].portNum == 2) && (PortChannels[counter].pinNum <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
              /* Do Nothing ... No need to unlock the commit register for this pin */

    }
    if(PortChannels[counter].pinmode==DIO_PIN)
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pinNum);
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortChannels[counter].pinNum * 4));
        }
    else
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pinNum);
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PortChannels[counter].pinmode << (PortChannels[counter].pinNum * 4));
        }   
    
    if( PortChannels[counter].direction ==PORT_PIN_IN )
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pinNum);
      if(PortChannels[counter].pinmode == ANALOG_MODE)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pinNum);
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[counter].pinNum);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[counter].pinNum);
      }
      else
      {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[counter].pinNum);
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[counter].pinNum);
                }
                
                if(PortChannels[counter].resistor == PULL_UP)
                {
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[counter].pinNum);
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[counter].pinNum);
                }
                else if(PortChannels[counter].resistor == PULL_DOWN)
                {
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[counter].pinNum);
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[counter].pinNum);
                }
                else
                {
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[counter].pinNum);
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[counter].pinNum);

                }
      }
   if( PortChannels[counter].direction ==PORT_PIN_OUT )
     {
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pinNum);
       if(PortChannels[counter].initial_value == INITIAL_VALUE_HIGH)
       {
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[counter].pinNum);
       }
       else
       {
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[counter].pinNum);
       }
     }
      
    }
    

Port_Status = PORT_INITIALIZED;
    
  }
 }

/************************************************************************************
* Service Name:         Port_SetPinDirection
* Service ID[hex]:      0x02
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      Pin       - Port Pin ID Number
*                       Direction - Port Pin Direction
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function that sets the port pin direction
* Note:                 This function can be deleted if
*                       PORT_SET_PIN_DIRECTION_API != STD_ON
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ) 
{
  	volatile uint32 * PortGpio_Ptr = NULL_PTR;
	boolean error = FALSE;
        uint8 NUM;
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinDirection_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNLES <= pin)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinDirection_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
            /* Check if this Pin is unchangeable */
        if( PortChannels[NUM].direction_Changeable == DIRECTION_NOTCHANGEABLE)
    {
        /* Pin is Unchangeable, report an PORT_E_DIRECTON_UNCHANGEABLE DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID, PORT_E_DIRECTION_UNCHANGEABLE);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing, Pin direction is changeable */
    }
#endif
for(uint8 i = 0; i < PORT_CONFIGURED_CHANNLES; i++)
    {
        if(PortChannels[i].pinNum == Pin)
        {
            /* Save the Array index */
             NUM = i;

            /* Get out of the Loop */
            break;
        }
    }

if(error == FALSE)
{
switch(PortChannels[NUM].portNum)
{
          case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
}
 if( ((PortChannels[NUM].portNum == 3) && (PortChannels[NUM].pinNum == 7)) || ((PortChannels[NUM].portNum == 5) && (PortChannels[NUM].pinNum == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[NUM].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PortChannels[NUM].portNum == 2) && (PortChannels[NUM].pinNum <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
              /* Do Nothing ... No need to unlock the commit register for this pin */

    }
if(Direction == PORT_PIN_OUT)
{
  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[NUM].pinNum);
}
else
{
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[NUM].pinNum);
}
 }
}
#endif
/************************************************************************************
* Service Name:          Port_RefreshPortDirection
* Service ID[hex]:       0x02
* Sync/Async:            Synchronous
* Reentrancy:            Non-Reentrant
* Parameters (in):       None
* Parameters (inout):    None
* Parameters (out):      None
* Return value:          None
* Description:           Function used to refresh the direction of all
*                        configured ports to configured direction
************************************************************************************/
void Port_RefreshPortDirection( void )
{
    	volatile uint32 * PortGpio_Ptr = NULL_PTR;
	boolean error = FALSE;
        uint8 counter=0;
        #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinDirection_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        #endif

        
 
     for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
      {
         #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PortChannels[counter].direction_Changeable == DIRECTION_NOTCHANGEABLE)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinDirection_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        #endif
         if(error == FALSE)
  {
       switch(PortChannels[counter].portNum)
    {
        case  PORTA: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
     if( ((PortChannels[counter].portNum == 3) && (PortChannels[counter].pinNum == 7)) || ((PortChannels[counter].portNum == 5) && (PortChannels[counter].pinNum == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[counter].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PortChannels[counter].portNum == 2) && (PortChannels[counter].pinNum <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
              /* Do Nothing ... No need to unlock the commit register for this pin */

    }
    if(PortChannels[counter].direction == PORT_PIN_OUT)
{
  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pinNum);
}
else
{
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pinNum);
}
    
     }
      }
}
/************************************************************************************
* Service Name:         Port_GetVersionInfo
* Service ID[hex]:      0x03
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      None
* Parameters (inout):   None
* Parameters (out):     VersionInfo - Pointer to where to store the version information of this module.
* Return value:         None
* Description:          Function to get the version information of this module.
* Note:                 This function can be deleted if
*                       PORT_VERSION_INFO_API != STD_ON
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                Port_GetVersionInfo_SID, PORT_E_PARAM_POINTER);

    }
    else
    {
    }
   if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_GetVersionInfo_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
  #endif
          {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software 4Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
    
}
#endif
/************************************************************************************
* Service Name:         Port_SetPinMode
* Service ID[hex]:      0x04
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      Pin     - Port Pin ID Number
*                       Mode    - New Port pin Mode to be set in port pin
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function used to set port pin mode during run time
************************************************************************************/
 void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
 {
       	volatile uint32 * PortGpio_Ptr = NULL_PTR;
	boolean error = FALSE;
        uint8 NUM;
        #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinMode_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        #endif
for(uint8 i = 0; i < PORT_CONFIGURED_CHANNLES; i++)
    {
        if(PortChannels[i].pinNum == Pin)
        {
            /* Save the Array index */
             NUM = i;

            /* Get out of the Loop */
            break;
        }
    }   
        #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PortChannels[NUM].mode_Changeable == MODE_NOTCHANGEABLE)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SetPinMode_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
       if(NUM > 39)
         {
        /* Incorrect Pin ID passed after looping all the array, report a PORT_E_PARAM_PIN DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_PARAM_PIN);

        /* Set error variable to True */
        error = TRUE;
         }
       else
        {
        /* Do nothing */
        }
        if(PortChannels[NUM].pinmode > 14)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID, PORT_E_PARAM_INVALID_MODE);
        }
        else
        {
          /*Do nothing*/
        }
        #endif
if(error == FALSE)
 {
          switch(PortChannels[NUM].portNum)
{
          case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
}
    if( ((PortChannels[NUM].portNum == 3) && (PortChannels[NUM].pinNum == 7)) || ((PortChannels[NUM].portNum == 5) && (PortChannels[NUM].pinNum == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[NUM].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PortChannels[NUM].portNum == 2) && (PortChannels[NUM].pinNum <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
       /* Do Nothing ... No need to unlock the commit register for this pin */

     }
 if(PortChannels[NUM].pinmode == ANALOG_MODE)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[NUM].pinNum);
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[NUM].pinNum);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[NUM].pinNum);
      }
 if(PortChannels[NUM].pinmode==DIO_PIN)
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[NUM].pinNum);
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortChannels[NUM].pinNum * 4));
        }
 else
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[NUM].pinNum);
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PortChannels[NUM].pinmode << (PortChannels[NUM].pinNum * 4));
        }  
 }
       
 }
