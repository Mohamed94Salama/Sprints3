/*****************************************************************************
* Task       : Design Patterns
* File Name  : Ultrasonic_Proxy.h
* Description: Header file for the Ultrasonic Proxy in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/

#ifndef HW_PROXY_HANDLER_ULTRASONIC_PROXY_ULTRASONIC_PROXY_H_
#define HW_PROXY_HANDLER_ULTRASONIC_PROXY_ULTRASONIC_PROXY_H_

/*Includes*/
#include "../../ECUAL/Ultrasonic/Ultrasonic.h"

/*Functions Prototypes*/
enuErrorStatus_t UltrasonicProxy_Init(void);
enuErrorStatus_t UltrasonicProxy_Trigger(enuUltrasonicChannel_t Channel);
enuErrorStatus_t UltrasonicProxy_GetDistance(uint16_t *Distance);
enuErrorStatus_t UltrasonicProxy_GetReading_Polling(enuUltrasonicChannel_t Channel,uint32_t *Distance);

#endif /* HW_PROXY_HANDLER_ULTRASONIC_PROXY_ULTRASONIC_PROXY_H_ */
