/*****************************************************************************
* Task       : Design Patterns
* File Name  : SW_ICU_Proxy.h
* Description: Header file for the SW_ICU Proxy in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#ifndef HW_PROXY_HANDLER_SW_ICU_PROXY_SW_ICU_PROXY_H_
#define HW_PROXY_HANDLER_SW_ICU_PROXY_SW_ICU_PROXY_H_

/*Includes*/
#include "../../ECUAL/SW_ICU/SW_ICU.h"

/*Functions Prototypes*/
enuErrorStatus_t SW_ICU_InitProxy(void);
enuErrorStatus_t SW_ICU_SetEdgeProxy(enuSW_ICU_TriggerMode_t enuEdge);
enuErrorStatus_t SW_ICU_GetReadingProxy(uint32_t *u32Buffer);
enuErrorStatus_t SW_ICU_Reset_ReadingProxy(void);
enuErrorStatus_t SW_ICU_SetCallbackProxy(void(*local_fptr)(void));

#endif /* HW_PROXY_HANDLER_SW_ICU_PROXY_SW_ICU_PROXY_H_ */
