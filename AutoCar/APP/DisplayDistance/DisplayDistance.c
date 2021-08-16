/*- INCLUDES -----------------------------------------------*/
#include "DisplayDistance.h"

/*- PREPROCESSOR MACROS ------------------------------------*/
#define DISPLAYDISTANCE_LCD_POSITION_ROW0					(0u)
#define DISPLAYDISTANCE_LCD_POSITION_ROW1					(1u)
#define DISPLAYDISTANCE_LCD_POSITION_COL0					(0u)

/*- ENUMS --------------------------------------------------*/
typedef enum {LCD_START, LCD_INIT_DONE, LCD_SET_POSITION_0_0_DONE, LCD_DISPLAY_STRING_DONE,
			  LCD_SET_POSITION_1_0_DONE, LCD_DISPLAY_DISTANCE_DONE} enuLCDFlagStates_t;

/*- GLOBAL VARIABLES ---------------------------------------*/
static enuLCDFlagStates_t genuLCDFlagStates = LCD_START;

/*- FUNCTION DEFINITIONS -----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to initialize all APIs responsible for displaying distance
*************************************************************************************************/
enuErrorStatus_t DisplayDistance_Init(void)
{
	enuErrorStatus_t enuRetVar;

	switch(genuLCDFlagStates)
	{
		case LCD_START:
			/* Initializing the LCD module to start displaying on it */
			enuRetVar = LCD_Init();
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_INIT_DONE;
				enuRetVar = E_ERROR;
			}
			else
			{
			}
		break;

		case LCD_INIT_DONE:
			/* Setting the position on the cursor at row 0 and column 0 */
			enuRetVar = LCD_goToRowColumn(DISPLAYDISTANCE_LCD_POSITION_ROW0, DISPLAYDISTANCE_LCD_POSITION_COL0);
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_SET_POSITION_0_0_DONE;
				enuRetVar = E_ERROR;
			}
			else
			{
			}
		break;

		case LCD_SET_POSITION_0_0_DONE:
			/* Displaying the string "Distance:" on the LCD screen */
			enuRetVar = LCD_displayString((uint8_t*)"Distance:");
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_DISPLAY_STRING_DONE;
			}
			else
			{
			}
		break;

		default:
			enuRetVar = E_ERROR;
		break;
	}
	return enuRetVar;
}

/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to display the current distance of the robot from any obstacle
*************************************************************************************************/
enuErrorStatus_t DisplayDistance_Update(void)
{
	enuErrorStatus_t enuRetVar;

	switch(genuLCDFlagStates)
	{
		case LCD_DISPLAY_STRING_DONE:
			/* Setting the position on the cursor at row 1 and column 0 */
			enuRetVar = LCD_goToRowColumn(DISPLAYDISTANCE_LCD_POSITION_ROW1, DISPLAYDISTANCE_LCD_POSITION_COL0);
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_SET_POSITION_1_0_DONE;
				enuRetVar = E_ERROR;
			}
			else
			{
			}
		break;

		case LCD_SET_POSITION_1_0_DONE:
			/* Displaying the distance of the obstacle on the LCD screen */
			enuRetVar = LCD_intgerToString(gu16Distance);
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_DISPLAY_DISTANCE_DONE;
				Ultrasonic_Trigger(US_CH1);
				gu8UltrasonicFlag = HIGH;
				enuRetVar = E_ERROR;
			}
			else
			{
			}
		break;

		case LCD_DISPLAY_DISTANCE_DONE:
			/* Displaying spaces on LCD screen to clear any extra numbers */
			enuRetVar = LCD_displayString((uint8_t*)"          ");
			if(enuRetVar == E_OK)
			{
				genuLCDFlagStates = LCD_DISPLAY_STRING_DONE;
			}
			else
			{
			}
		break;

		default:
			enuRetVar = E_ERROR;
		break;
	}
	return enuRetVar;
}

