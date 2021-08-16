/*****************************************************************************
* Task       : TIMER_DRIVER
* File Name  : T_Delay.h
* Description: Source file for timer delay
* Author     : Kariman Karam
* Date       : 8/12/2021
******************************************************************************/

/*Includes ---------------------------------------------------*/
#include "TDelay.h"

/*Preprocessor Macros ---------------------------------------------------*/
#define TDELAY_THOUSAND_MULTIPLIER										(1000)

/*Functions Declarations ---------------------------------------------------*/
#if 0
/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to initialize the delay function
************************************************************************************/
enuErrorStatus_t TDelay_Init(void)
{
	/*initialize timer0 to work on normal mode with prescaller 8, tick time = 1 us*/
	T0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_8);
	/*enable OVF interrupt*/
	T0_OV_InterruptEnable();
	return E_OK;
}//end TDelay_Init
#endif
/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with ms
************************************************************************************/
enuErrorStatus_t TDelay_ms(uint8_t u8TimerNumber, uint64_t u64Time_ms, void(*pfCallback)(void))
{
	enuErrorStatus_t enuStatus = E_ERROR;
	/*Convert ms to us*/
	u64Time_ms *= TDELAY_THOUSAND_MULTIPLIER;
	if(u8TimerNumber == TIMER0)
	{
		//turn on timer interrupts
		T0_OV_InterruptEnable();
		/*start timer to count in ms, send callBack function*/
		T0_Start(u64Time_ms, pfCallback);
		enuStatus = T0_GetStatus();
	}
	else if(u8TimerNumber == TIMER2)
	{
		//turn on timer interrupts
		T2_OV_InterruptEnable();
		/*start timer to count in ms, send callBack function*/
		T2_Start(u64Time_ms, pfCallback);
		enuStatus = T2_GetStatus();
	}
	return enuStatus;
}//end TDelay_ms

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with us
************************************************************************************/
enuErrorStatus_t TDelay_us(uint8_t u8TimerNumber, uint64_t u64Time_us, void(*pfCallback)(void))
{
	enuErrorStatus_t enuStatus = E_ERROR;

	if(u8TimerNumber == TIMER0)
	{
		//turn on timer interrupts
		T0_OV_InterruptEnable();
		/*start timer to count in ms, send callBack function*/
		T0_Start(u64Time_us, pfCallback);
		enuStatus = T0_GetStatus();
	}
	else if(u8TimerNumber == TIMER2)
	{
		//turn on timer interrupts
		T2_OV_InterruptEnable();
		/*start timer to count in ms, send callBack function*/
		T2_Start(u64Time_us, pfCallback);
		enuStatus = T2_GetStatus();
	}
	return enuStatus;
}//end TDelay_us

#if 0
/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with ms
************************************************************************************/
enuErrorStatus_t T2Delay_ms(uint64_t u64Time_ms, void(*pfCallback)(void))
{
	/*Convert ms to us*/
	u64Time_ms *= 1000;
	//turn on timer interrupts
	T2_OV_InterruptEnable();
	/*start timer to count in ms, send callBack function*/
	T2_Start(u64Time_ms, pfCallback);
	return T2_GetStatus();
}//end T2Delay_ms

/************************************************************************************
* Parameters (in) : uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to make delay with us
************************************************************************************/
enuErrorStatus_t T2Delay_us(uint64_t u64Time_us, void(*pfCallback)(void))
{
	//turn on timer interrupts
	T2_OV_InterruptEnable();
	/*start timer to count in us, send callBack function*/
	T2_Start(u64Time_us, pfCallback);
	return T0_GetStatus();
}//end T2Delay_us
#endif
