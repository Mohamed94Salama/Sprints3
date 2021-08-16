/*****************************************************************************
* Task       : External Interrupt driver
* File Name  : EXT_INT.h
* Description: header file for External Interrupt driver
* Author     : Kariman Karam
* Date       : 3/8/2021
******************************************************************************/

#ifndef MCAL_EXTERNAL_INTERRUPT_EXT_INT_H_
#define MCAL_EXTERNAL_INTERRUPT_EXT_INT_H_

/*- INCLUDES --------------------------------------------------*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"
#include "../Register.h"

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	EXT_LOW_MODE =0,
	EXT_CHANGE_MODE,
	EXT_FAILLING_MODE,
	EXT_RAISING_MODE

}enuEXTINTSenseControl;

typedef enum
{
	EXTINT_INT0=0,
	EXTINT_INT1,
	EXTINT_INT2
}enuEXTINTNum;


/*- FUNCTION PROTOTYPES ----------------------------------*/

/***********************************************************************************************
* Parameters (in) : enuInterruptNum
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to initialize External Interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_Init( enuEXTINTNum enuInterruptNum);

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, enuSenseMode
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_SetSenseMode(enuEXTINTSenseControl enuSenseMode, enuEXTINTNum enuInterruptNum);

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, pCallBack
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_SetCallBack(void(*pCallBack)(void), enuEXTINTNum enuInterruptNum);

#endif
