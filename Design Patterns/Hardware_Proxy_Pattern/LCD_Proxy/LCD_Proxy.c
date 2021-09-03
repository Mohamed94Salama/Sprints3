/*****************************************************************************
* Task       : Design Patterns
* File Name  : LCD_Proxy.c
* Description: Proxy file for the LCD in the HW proxy design pattern
* Author     : Mohamed Ehab (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#include "LCD_Proxy.h"

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : LCD initialization
*************************************************************/
enuErrorStatus_t LCDProxy_Init(void)
{
	enuErrorStatus_t RetVal = LCD_Init();
	return RetVal;
}

/************************************************************
* Parameters (in) : cmd
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Sending a command to the LCD
*************************************************************/
enuErrorStatus_t LCDProxy_SendCMD(uint8_t cmd)
{
	enuErrorStatus_t RetVal = LCD_SendCMD(cmd);
	return RetVal;
}

/************************************************************
* Parameters (in) : c
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Sending data to the LCD
*************************************************************/
enuErrorStatus_t LCDProxy_SendChar(uint8_t c)
{
	enuErrorStatus_t RetVal = LCD_SendChar(c);
	return RetVal;
}

/************************************************************
* Parameters (in) : ptr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Sending a string to the LCD
*************************************************************/
enuErrorStatus_t LCDProxy_SendString(uint8_t* pu8string)
{
	enuErrorStatus_t RetVal = LCD_SendString(pu8string);
	return RetVal;
}

/************************************************************
* Parameters (in) : num
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Writing a number on the LCD
*************************************************************/
enuErrorStatus_t LCDProxy_writeNum(uint32_t num)
{
	enuErrorStatus_t RetVal = LCD_writeNum(num);
	return RetVal;
}

/************************************************************
* Parameters (in) : X , Y
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Change the coordinate of the cursor
*************************************************************/
enuErrorStatus_t LCDProxy_GOTOXY(uint8_t X,uint8_t Y)
{
	enuErrorStatus_t RetVal = LCD_GOTOXY(X,Y);
	return RetVal;
}
