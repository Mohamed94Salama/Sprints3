/*****************************************************************************
* Task       : Design Patterns
* File Name  : Ultrasonic_Proxy.c
* Description: Proxy file for the Ultrasonic in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#include "Ultrasonic_Proxy.h"

/*MACROS -------------------------------------------------------------------*/
//duration of the trigger pulse
#define  TRIGGER_DURATION_US              10u
//Factor to be used when converting reading time into distance in cm
#define  US_CM_FACTOR                     58u

/*ENUMS -----------------------------------------------------------------*/
typedef enum{GETTING_RISING_EDGE,GETTING_FALLING_EDGE}enuReadingState_t;
typedef enum{Reading_Not_Complete,Reading_Complete}enuReadingFlagState_t;

/*GLOBAL VARIABLES -----------------------------------------------------------------*/
extern uint32_t Reading1,Reading2;
extern volatile enuReadingFlagState_t Reading_Flag;


/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : void
* Description     : A function to record ICU readings - Callback function
************************************************************************************/
static void Get_Readings(void)
{
   //create a state flag
   static enuReadingState_t u8Flag=GETTING_RISING_EDGE;
   //check on the flag condition
   switch (u8Flag)
   {
      //if the flag is set to detecting a rising edge
      case GETTING_RISING_EDGE:
      //get the rising edge timing
      SW_ICU_GetReading(&Reading1);
      //switch SW ICU to detect a falling edge
      SW_ICU_SetEdge(SW_ICU_FALLING_EDGE);
      //switch the flag state
      u8Flag=GETTING_FALLING_EDGE;
      break;

      //if the flag is set to detecting a rising edge
      case GETTING_FALLING_EDGE:
      SW_ICU_GetReading(&Reading2);
      SW_ICU_SetEdge(SW_ICU_RISING_EDGE);
      //switch the flag state
      u8Flag=GETTING_RISING_EDGE;
      //switch the Reading Flag state to indecate reading completion
      Reading_Flag=Reading_Complete;
      break;
   }
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t ... 1=E_OK - 0=E_ERROR
* Description     : A function to initialize the Ultrasonic Module
************************************************************************************/
enuErrorStatus_t UltrasonicProxy_Init(void)
{
	enuErrorStatus_t RetVal = Ultrasonic_Init();
	return RetVal;
}

/************************************************************************************
* Parameters (in) : enuUltrasonicChannel_t Channel
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to send a trigger pulse to the Ultrasonic Module
************************************************************************************/
enuErrorStatus_t UltrasonicProxy_Trigger(enuUltrasonicChannel_t Channel)
{
	enuErrorStatus_t RetVal = Ultrasonic_Trigger(Channel);
	return RetVal;
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): uint16_t *Distance
* Return value    : enuErrorStatus_t
* Description     : A function to check if ultrasonic reading is complete and return distance
************************************************************************************/
enuErrorStatus_t UltrasonicProxy_GetDistance(uint16_t *Distance)
{
	enuErrorStatus_t RetVal = Ultrasonic_GetDistance(Distance);
	return RetVal;
}

/************************************************************************************
 * Parameters (in) : enuUltrasonicChannel_t Channel
 * Parameters (out): uint16_t *Distance
 * Return value    : enuErrorStatus_t
 * Description     : A function to get ultrasonic reading using polling
 ************************************************************************************/
enuErrorStatus_t UltrasonicProxy_GetReading_Polling(enuUltrasonicChannel_t Channel,uint32_t *Distance)
{
	enuErrorStatus_t RetVal = Ultrasonic_GetReading_Polling(Channel,Distance);
	return RetVal;
}
