/*****************************************************************************
* Task       : Design Patterns
* File Name  : KEYPAD_Proxy.c
* Description: Proxy file for the Keypad in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#include "KEYPAD_Proxy.h"

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Keypad initialization
*************************************************************/
enuErrorStatus_t KEYPADProxy_Init(void)
{
	enuErrorStatus_t RetVal = KEYPAD_Init();
	return RetVal;
}

/************************************************************
* Parameters (in) : ptr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Reading the Keypad buttons
*************************************************************/
enuErrorStatus_t KEYPADProxy_Read(uint8_t* ptr)
{
	enuErrorStatus_t RetVal = KEYPAD_Read(ptr);
	return RetVal;
}
