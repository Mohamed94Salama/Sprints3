/*****************************************************************************
* Task       : Design Patterns
* File Name  : SW_ICU_Proxy.c
* Description: Proxy file for the SW_ICU in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/

#include "SW_ICU_Proxy.h"

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t ... 1=E_OK - 0=E_ERROR
* Description     : A function to initialize the Software ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_InitProxy(void)
{
	enuErrorStatus_t RetVal = SW_ICU_Init();
	return RetVal;
}

/************************************************************************************
* Parameters (in) : enuSW_ICU_TriggerMode_t enuEdge
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set the detection edge of the SW_ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_SetEdgeProxy(enuSW_ICU_TriggerMode_t enuEdge)
{
	enuErrorStatus_t RetVal = SW_ICU_SetEdge(enuEdge);
	return RetVal;
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): uint32_t *u32Buffer
* Return value    : enuErrorStatus_t
* Description     : A function to get the SW_ICU register reading
************************************************************************************/
enuErrorStatus_t SW_ICU_GetReadingProxy(uint32_t *u32Buffer)
{
	enuErrorStatus_t RetVal = SW_ICU_GetReading(u32Buffer);
	return RetVal;
}

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to reset the SW_ICU logic
************************************************************************************/
enuErrorStatus_t SW_ICU_Reset_ReadingProxy(void)
{
	enuErrorStatus_t RetVal = SW_ICU_Reset_Reading();
	return RetVal;
}

/************************************************************************************
* Parameters (in) : void(*local_fptr)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set callback function to be called in case of ICU event
************************************************************************************/
enuErrorStatus_t SW_ICU_SetCallbackProxy(void(*local_fptr)(void))
{
	enuErrorStatus_t RetVal = SW_ICU_SetCallback(local_fptr);
	return RetVal;
}
