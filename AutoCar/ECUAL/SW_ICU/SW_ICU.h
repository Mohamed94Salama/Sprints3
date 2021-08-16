/*****************************************************************************
* Task: Autonomous Car
* File Name: SW_ICU.h
* Description: Header file for Software ICU driver
* Author: Amr Mohamed
* Date: 12/8/2021
******************************************************************************/


#ifndef SW_ICU_H_
#define SW_ICU_H_

/*Includes -----------------------------------------------------------------*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"
#include "../../MCAL/Register.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/EX_INT/EXT_INT.h"
#include "../../MCAL/Timer/Timer.h"
#include "SW_ICU_Cfg.h"

/*ENUMS -----------------------------------------------------------------*/
typedef enum {SW_ICU_FALLING_EDGE=2,SW_ICU_RISING_EDGE=3}enuSW_ICU_TriggerMode_t;


/*API PROTOTYPES ---------------------------------------------------*/
/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t ... 1=E_OK - 0=E_ERROR
* Description     : A function to initialize the Software ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_Init(void);

/************************************************************************************
* Parameters (in) : enuSW_ICU_TriggerMode_t enuEdge
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set the detection edge of the SW_ICU
************************************************************************************/
enuErrorStatus_t SW_ICU_SetEdge(enuSW_ICU_TriggerMode_t enuEdge);

/************************************************************************************
* Parameters (in) : None
* Parameters (out): uint32_t *u32Buffer
* Return value    : enuErrorStatus_t
* Description     : A function to get the SW_ICU register reading
************************************************************************************/
enuErrorStatus_t SW_ICU_GetReading(uint32_t *u32Buffer);

/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to reset the SW_ICU logic
************************************************************************************/
enuErrorStatus_t SW_ICU_Reset_Reading(void);

/************************************************************************************
* Parameters (in) : void(*local_fptr)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to set callback function to be called in case of ICU event
************************************************************************************/
enuErrorStatus_t SW_ICU_SetCallback(void(*local_fptr)(void));

#endif /* SW_ICU_H_ */
