/*****************************************************************************
* Task       : Design Patterns
* File Name  : KEYPAD_Proxy.h
* Description: Header file for the Keypad Proxy in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#ifndef HW_PROXY_HANDLER_KEYPAD_PROXY_KEYPAD_PROXY_H_
#define HW_PROXY_HANDLER_KEYPAD_PROXY_KEYPAD_PROXY_H_

/* Includes */
#include "../../ECUAL/KEYPAD/KEYPAD.h"

/* Functions prototypes */
enuErrorStatus_t KEYPADProxy_Init(void);
enuErrorStatus_t KEYPADProxy_Read(uint8_t* ptr);

#endif /* HW_PROXY_HANDLER_KEYPAD_PROXY_KEYPAD_PROXY_H_ */
