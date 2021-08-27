/*****************************************************************************
* Task       : Design Patterns
* File Name  : HBridge_Proxy.h
* Description: Header file for the HBridge Proxy in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#ifndef HW_PROXY_HANDLER_HBRIDGE_PROXY_HBRIDGE_PROXY_H_
#define HW_PROXY_HANDLER_HBRIDGE_PROXY_HBRIDGE_PROXY_H_

#include "../../ECUAL/HBridge/HBridge.h"

#if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock);
/*************************************************************************************************
* Parameters	: u8HBridgeMotorSpeed
* Return Value	: enuErrorStatus_t
* Description  : Set the speed of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_SetSpeed(uint8_t u8HBridgeMotorSpeed);
#elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Init(void);
#endif
/*************************************************************************************************
* Parameters	: enuHBridgeMotorDirection
* Return Value	: enuErrorStatus_t
* Description  : Set the direction of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_SetDirection(enuHBridgeMotorDirection_t enuHBridgeMotorDirection);
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Start the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Start(void);
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Stop the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridgeProxy_Stop(void);

#endif /* HW_PROXY_HANDLER_HBRIDGE_PROXY_HBRIDGE_PROXY_H_ */
