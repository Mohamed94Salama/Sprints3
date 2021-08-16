
/*****************************************************************************
* Module     : LCD
* File Name  : LCD.h
* Description: Header file for the LCD driver
* Author     : Mohamed Ehab
* Date       : 24/7/2021
******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../LIB/BIT_MANIPULATE.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include <stdlib.h>
#include "../../Services/TDelay/TDelay.h"


/*- Preprocessor Macros -----------------------------------------------*/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS 
#endif

/* LCD HW Pins */
#define RS PA1
#define RW PA2
#define E  PA3
#define LCD_CTRL_PORT     PORTA_R
#define LCD_CTRL_PORT_DIR DDRA_R

#define LCD_DATA_PORT     PORTA_R
#define LCD_DATA_PORT_DIR DDRA_R


/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************************************************
* Parameters (in) : uint8_t u8Data
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR , E_OK
* Description     : A function to display a character on the LCD
*************************************************************************************************/
enuErrorStatus_t LCD_displayCharacter(uint8_t u8Data);

/*************************************************************************************************
* Parameters (in) : const uint8_t *pu8Str
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to display a string on the LCD
*************************************************************************************************/
enuErrorStatus_t LCD_displayString(const uint8_t *pu8Str);

/*************************************************************************************************
* Parameters (in) : enuErrorStatus_t
* Parameters (out): None
* Return Value    : E_ERROR , E_OK
* Description     : A function to initialize the LCD
*************************************************************************************************/
enuErrorStatus_t LCD_Init(void);
/*************************************************************************************************
* Parameters (in) : enuErrorStatus_t
* Parameters (out): None
* Return Value    : E_ERROR , E_OK
* Description     : A function to clear the screen of the LCD
*************************************************************************************************/
enuErrorStatus_t LCD_clearScreen(void);

/*************************************************************************************************
* Parameters (in) : uint8_t u8Row, uint8_t u8Col,const uint8_t *pu8Str
* Parameters (out): None
* Return Value    : void
* Description     : A function to display a string with particular row and column
*************************************************************************************************/
void LCD_displayStringRowColumn(uint8_t u8Row, uint8_t u8Col,const uint8_t *pu8Str);

/*************************************************************************************************
* Parameters (in) : uint8_t u8Row, uint8_t u8Col
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR , E_OK
* Description     : A function to set the cursor in a particular row and column
*************************************************************************************************/
enuErrorStatus_t LCD_goToRowColumn(uint8_t u8Row, uint8_t u8Col);

/*************************************************************************************************
* Parameters (in) : u16Data
* Parameters (out): None
* Return Value    : void
* Description     : A function to display integer
*************************************************************************************************/
enuErrorStatus_t LCD_intgerToString(uint16_t u16Data);

#endif /* LCD_H_ */
