/*****************************************************************************
* Task       : Design Patterns
* File Name  : LCD_Proxy.h
* Description: Header file for the LCD Proxy in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#ifndef HW_PROXY_HANDLER_HW_PROXY_H_
#define HW_PROXY_HANDLER_HW_PROXY_H_

/* Includes */
#include "../../ECUAL/LCD/LCD.h"

/* Functions prototypes */
enuErrorStatus_t LCDProxy_Init(void);
enuErrorStatus_t LCDProxy_SendCMD(uint8_t cmd);
enuErrorStatus_t LCDProxy_SendChar(uint8_t c);
enuErrorStatus_t LCDProxy_SendString(uint8_t* pu8string);
enuErrorStatus_t LCDProxy_writeNum(uint32_t num);
enuErrorStatus_t LCDProxy_GOTOXY(uint8_t X,uint8_t Y);



#endif /* HW_PROXY_HANDLER_HW_PROXY_H_ */
