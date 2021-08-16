/*****************************************************************************
* Task       : TIMER_DRIVER
* File Name  : T_Delay.h
* Description: Heaer file for timer delay
* Author     : Kariman Karam
* Date       : 8/12/2021
******************************************************************************/

#ifndef T_DELAY_H_
#define T_DELAY_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/Register.h"

#define TIMER0	0
#define TIMER2	2


/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to initialize the delay function
************************************************************************************/
enuErrorStatus_t TDelay_Init(void);

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with ms
************************************************************************************/
enuErrorStatus_t TDelay_ms(uint8_t u8TimerNumber, uint64_t u64Time_ms, void(*pfCallback)(void));

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with us
************************************************************************************/
enuErrorStatus_t TDelay_us(uint8_t u8TimerNumber, uint64_t u64Time_us, void(*pfCallback)(void));

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with ms
************************************************************************************/
enuErrorStatus_t T2Delay_ms(uint64_t u64Time_ms, void(*pfCallback)(void));

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with us
************************************************************************************/
enuErrorStatus_t T2Delay_us(uint64_t u64Time_us, void(*pfCallback)(void));


#endif /* T_DELAY_H_ */
