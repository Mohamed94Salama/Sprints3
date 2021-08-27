/*****************************************************************************
* Task       : Design Patterns
* File Name  : HBridge_Proxy.c
* Description: Proxy file for the HBridge in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#include "HBridge_Proxy.h"

#if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock)
{
	enuErrorStatus_t RetVal = HBridge_Init(enuPWMMode,enuPWMCompareOutputMode,enuPWMClock);
	return RetVal;
}
/*************************************************************************************************
* Parameters	: u8HBridgeMotorSpeed
* Return Value	: enuErrorStatus_t
* Description  : Set the speed of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_SetSpeed(uint8_t u8HBridgeMotorSpeed)
{
	enuErrorStatus_t RetVal = HBridge_SetSpeed(u8HBridgeMotorSpeed);
	return RetVal;
}
#elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Init(void)
{
	enuErrorStatus_t RetVal = HBridge_Init();
	return RetVal;
}
#endif

/*************************************************************************************************
* Parameters	: enuHBridgeMotorDirection
* Return Value	: enuErrorStatus_t
* Description  : Set the direction of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_SetDirection(enuHBridgeMotorDirection_t enuHBridgeMotorDirection)
{
	enuErrorStatus_t RetVal = HBridge_SetDirection(enuHBridgeMotorDirection);
	return RetVal;
}
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Start the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Start(void)
{
	enuErrorStatus_t RetVal = HBridge_Start();
	return RetVal;
}
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Stop the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Stop(void)
{
	enuErrorStatus_t RetVal = HBridge_Stop();
	return RetVal;
}
