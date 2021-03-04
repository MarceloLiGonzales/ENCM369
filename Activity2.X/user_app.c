/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------
 void TimeXus(INPUT_PARAMETER_)
  - Sets Timer0 to count u16Microseconds_
  - Requires:-Timer0 configured such that each timer tick is 1 microsecond
  - INPUT_PARAMETER_is the value in microseconds to time from 1 to 65535
 Promises:
  - Pre-loads TMR0H:L to clock out desired period
  - TMR0IF cleared-Timer0 enabled
 */

 void TimeXus(u16 u16Period)
 {
    /* OPTIONAL: range check and handle edge cases */
     
     
    /* Disable the timer during config */
     T0CON0 &= 0x7F;
     
    /* Preload TMR0H and TMR0L based on u16TimeXus */
     TMR0H = (u8)((0xFFFF - u16Period) >> 8);
     TMR0L = (u8)(0xFFFF - u16Period);
     
    /* Clear TMR0IF and enable Timer 0 */
     PIR3 &= 0x7F;
     T0CON0 |= 0x80;
     
 } /* end TimeXus () */

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    //Initialize Timer0 Module 
    T0CON0 = 0x90;  
    T0CON1 = 0x54;

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    //set up pattern and speed variables
    static u8 u8Pattern[22] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x21, 0x22, 0x24, 0x28, 0x30, 0x31, 0x32, 0x34, 0x38, 0x39, 0x3A, 0x3C, 0x3D, 0x3E, 0x3F};
    static u8 u8Counter = 0;
    static u8 u8Speed = 0;
    
    if(u8Speed < 1) // reduces LED update speed by a factor of 3
    {
        if (u8Counter < 22) //If not the last LED value, increment by 1
        {
            u8Counter++;
        } 
        else //If it is the last LED value in the pattern, restart
        {
            u8Counter = 0;
        }
        u8Speed++;
    }
    else
    {
        u8Speed = 0;
    }

    LATA = (LATA & 0xC0) | u8Pattern[u8Counter];  // Update LED values

} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
