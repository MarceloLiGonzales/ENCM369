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
    static u32 u32LEDCounter = 0;
    static u8 u8PreviousRB3State = 0x00;
    static u8 u8PreviousRB5State = 0x00;
    static u32 u32ContinuousIncrementDelay = 0;
    static u32 u32ContinuousDecrementDelay = 0;
    
    u32 u32Delay = 286400 / 25;
    for(; u32Delay > 0; u32Delay--); // 10ms delay to avoid bouncing
    
    //increment button checks
    if ((u8PreviousRB5State == 0) && ((PORTB & 0x20) == 0x20)) //check button was just pressed
    {
        u32LEDCounter += 1; //add one
        PORTA = (PORTA & 0xC0) | (u32LEDCounter & 0x3F); //write to bits RA5-RA0 while preserving RA7 and RA6
    }
    
    if ((u8PreviousRB5State == 0x20) && ((PORTB & 0x20) == 0x20)) //check button is being continously pressed
    {
        u32ContinuousIncrementDelay += 1; //decrease delay for continuous increment as button stays pressed
        
        if ((u32ContinuousIncrementDelay > 100) && (u32ContinuousIncrementDelay % 32 == 0)) // reduce continuous increment speed without adding unnecessary delays
        {
            u32LEDCounter += 1; //add one
            PORTA = (PORTA & 0xC0) | (u32LEDCounter & 0x3F); //write to bits RA5-RA0 while preserving RA7 and RA6
        }
    }
    else // ensure continuous increment delay is reset when button is not being pressed
    {
        u32ContinuousIncrementDelay = 0;
    }
    
    //decrement button checks
        if ((u8PreviousRB3State == 0) && ((PORTB & 0x08) == 0x08)) //check button was just pressed
    {
        u32LEDCounter -= 1; //add one
        PORTA = (PORTA & 0xC0) | (u32LEDCounter & 0x3F); //write to bits RA5-RA0 while preserving RA7 and RA6
    }
    
    if ((u8PreviousRB3State == 0x08) && ((PORTB & 0x08) == 0x08)) //check button is being continously pressed
    {
        u32ContinuousDecrementDelay += 1; //decrease delay for continuous increment as button stays pressed
        
        if ((u32ContinuousDecrementDelay > 100) && (u32ContinuousDecrementDelay % 32 == 0)) // reduce continuous increment speed without adding delays (same number of button checks per second)
        {
            u32LEDCounter -= 1; //add one
            PORTA = (PORTA & 0xC0) | (u32LEDCounter & 0x3F); //write to bits RA5-RA0 while preserving RA7 and RA6
        }
    }
    else // ensure continuous increment delay is reset when button is not being pressed
    {
        u32ContinuousDecrementDelay = 0;
    }
    
    //update previous RB states for next loop
    u8PreviousRB3State = PORTB & 0x08;
    u8PreviousRB5State = PORTB & 0x20;
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
