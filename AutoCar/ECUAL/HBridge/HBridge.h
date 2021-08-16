#ifndef HBRIDGE_H_
#define HBRIDGE_H_

#include "HBridge_Cfg.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/PWM/PWM.h"
#include "../../LIB/STD_TYPES.h"

typedef enum {MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT} enuHBridgeMotorDirection_t;

#if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridge_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock);
/*************************************************************************************************
* Parameters	: u8HBridgeMotorSpeed
* Return Value	: enuErrorStatus_t
* Description  : Set the speed of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_SetSpeed(uint8_t u8HBridgeMotorSpeed);
#elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridge_Init(void);
#endif
/*************************************************************************************************
* Parameters	: enuHBridgeMotorDirection
* Return Value	: enuErrorStatus_t
* Description  : Set the direction of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_SetDirection(enuHBridgeMotorDirection_t enuHBridgeMotorDirection);
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Start the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_Start(void);
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Stop the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_Stop(void);

#endif /* HBRIDGE_H_ */