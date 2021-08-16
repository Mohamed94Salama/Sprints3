/*****************************************************************************
* Task: Autonomous Car
* File Name: SW_ICU.c
* Description: File for Software ICU driver functions
* Author: Amr Mohamed
* Date: 12/8/2021
******************************************************************************/

/*Includes -----------------------------------------------------------------*/
#include "SW_ICU.h"

/*Preprocessor Macros ---------------------------------------------------*/
#define SW_ICU_THOUSAND_MULTIPLIER										(1000)
#define SW_ICU_TWO_DIVISOR												(2)
#define SW_ICU_TIMER_RESET_VALUE										(0)

/*API Implementation ---------------------------------------------------*/

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t ... 1=E_OK - 0=E_ERROR
* Description     : A function to initialize the Software ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_Init(void)
{
   //initialize the software ICU
   EXTINT_Init(SW_ICU_EX_INT_CH);
   //Set external interrupt channel to detect rising edge 
   EXTINT_SetSenseMode(EXT_RAISING_MODE,SW_ICU_EX_INT_CH);
   //initialize timer1 
   Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
   //reset timer 1 overflow counter
   Timer1_ResetOVFCount();
   //enable timer1 overflow interrupt
   Timer1_OVF_InterruptEnable();
   //update the ICR register value to apply the new frequency
   ICR1_R=(TIMER1_FREQ_KHZ*SW_ICU_THOUSAND_MULTIPLIER)/SW_ICU_TWO_DIVISOR;
   //reset timer register
   TCNT1_R=SW_ICU_TIMER_RESET_VALUE;
   //return OK status
   return E_OK;
}

/************************************************************************************
* Parameters (in) : enuSW_ICU_TriggerMode_t enuEdge
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set the detection edge of the SW_ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_SetEdge(enuSW_ICU_TriggerMode_t enuEdge)
{
   //Set external interrupt channel to detect the specified edge
   EXTINT_SetSenseMode(enuEdge,SW_ICU_EX_INT_CH);
   //return OK status
   return E_OK;
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to reset the SW_ICU logic
************************************************************************************/
enuErrorStatus_t SW_ICU_Reset_Reading(void)
{
   //reset timer 1 overflow counter
   Timer1_ResetOVFCount();
   //return OK status
   return E_OK;
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): uint32_t *u32Buffer
* Return value    : enuErrorStatus_t
* Description     : A function to get the SW_ICU register reading
************************************************************************************/
enuErrorStatus_t SW_ICU_GetReading(uint32_t *u32Buffer)
{
   //check if sent pointer points to a valid location
   if (u32Buffer==NULLPTR)
   {
      //return a NOK status
      return E_ERROR;
   }
   //get a snapshot of the timer register
   uint16_t Buffer=TCNT1_R;
   uint32_t overflows=0;
   //get the overflow counter value
   Timer1_GetOVFCount(&overflows);
   //calculate actual timer value based on overflows number
   *u32Buffer=Buffer+(overflows*TIMER_MAX);
   //return OK status
   return E_OK;   
}

/************************************************************************************
* Parameters (in) : void(*local_fptr)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set callback function to be called in case of ICU event
************************************************************************************/
enuErrorStatus_t SW_ICU_SetCallback(void(*local_fptr)(void))
{
   //check if sent pointer points to a valid location
   if (local_fptr == NULLPTR)
   {
      //return a NOK status
      return E_ERROR;
   }
   //set the external interrupt callback to call the sent function
   EXTINT_SetCallBack(local_fptr, SW_ICU_EX_INT_CH);
   //return OK status
   return E_OK;
}
