/*****************************************************************************
* Task: Autonomous Car
* File Name: Ultrasonic.c
* Description: File for Ultrasonic driver functions
* Author: Amr Mohamed
* Date: 9/8/2021
******************************************************************************/

/*Includes -----------------------------------------------------------------*/
#include "Ultrasonic.h"
#include <util/delay.h>

/*MACROS -------------------------------------------------------------------*/
//duration of the trigger pulse
#define  TRIGGER_DURATION_US              10u
//Factor to be used when converting reading time into distance in cm
#define  US_CM_FACTOR                     58u

/*ENUMS -----------------------------------------------------------------*/
typedef enum{GETTING_RISING_EDGE,GETTING_FALLING_EDGE}enuReadingState_t;
typedef enum{Reading_Not_Complete,Reading_Complete}enuReadingFlagState_t;

/*GLOBAL VARIABLES -----------------------------------------------------------------*/
uint32_t Reading1=0,Reading2=0;
volatile enuReadingFlagState_t Reading_Flag=Reading_Not_Complete;


/*API Implementation ---------------------------------------------------*/

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
enuErrorStatus_t Ultrasonic_Init(void)
{
   //initialize Trigger pin
   DIO_PinInit(US_CH0_TRIGGER,OUTPUT,NO_CONNECTION);
   //initialize Echo pin
   DIO_PinInit(US_CH0_ECHO,INPUT,NO_CONNECTION);
   //initialize software ICU
   SW_ICU_Init();
   //set callback function to be executed in case of ICU event
   SW_ICU_SetCallback(Get_Readings); 
   //return OK status
   return E_OK;
}

/************************************************************************************
* Parameters (in) : enuUltrasonicChannel_t Channel
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to send a trigger pulse to the Ultrasonic Module
************************************************************************************/
 enuErrorStatus_t Ultrasonic_Trigger(enuUltrasonicChannel_t Channel)
 {
      //reset the reading completion flag
      Reading_Flag=Reading_Not_Complete;
      //set the ICU to detect a rising edge
      SW_ICU_SetEdge(SW_ICU_RISING_EDGE);
      //generate the trigger pulse
      DIO_PinWrite(PC0,HIGH);
      _delay_us(TRIGGER_DURATION_US);
      DIO_PinWrite(PC0,LOW);
      //reset the ICU unit
      SW_ICU_Reset_Reading();
      //return an OK status
      return E_OK;
 }
 
 /************************************************************************************
 * Parameters (in) : None
 * Parameters (out): uint16_t *Distance
 * Return value    : enuErrorStatus_t
 * Description     : A function to check if ultrasonic reading is complete and return distance
 ************************************************************************************/
 enuErrorStatus_t Ultrasonic_GetDistance(uint16_t *Distance)
 {
    //check for reading completion condition
   if (Reading_Flag)
   {
      //when echo signal has been received, calculate the distance
      *Distance=((Reading2-Reading1))/US_CM_FACTOR;
      //return an OK status
      return E_OK;
   }
   //return a NOK status
   return E_ERROR;
 }

/************************************************************************************
 * Parameters (in) : enuUltrasonicChannel_t Channel
 * Parameters (out): uint16_t *Distance
 * Return value    : enuErrorStatus_t
 * Description     : A function to get ultrasonic reading using polling
 ************************************************************************************/
enuErrorStatus_t Ultrasonic_GetReading_Polling(enuUltrasonicChannel_t Channel,uint32_t *Distance)
{
   //reset the reading completion flag
   Reading_Flag=Reading_Not_Complete;
   //set the ICU to detect a rising edge
   SW_ICU_SetEdge(SW_ICU_RISING_EDGE);
   //generate the trigger pulse
   DIO_PinWrite(PC0,HIGH);
   _delay_us(TRIGGER_DURATION_US);
   DIO_PinWrite(PC0,LOW);
   //wait for echo detection to complete
   while (!Reading_Flag);
   //calculate the distance
   *Distance=((Reading2-Reading1))/US_CM_FACTOR;
   //return an OK state
   return E_OK;
}
