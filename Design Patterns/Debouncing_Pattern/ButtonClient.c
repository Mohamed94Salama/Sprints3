/*****************************************************************************
* Task       : Design Patterns
* File Name  : ButtonClient.c
* Description: Source file for the button debouncing design pattern
* Author     : Mohamed Samy (Team 2)
* Date       : 23/8/2021
******************************************************************************/

#include "ButtonClient.h"


/* Internal Macros */
#define BUTTONCLIENT_CALLBACK_FLAG_STATE0													(0u)
#define BUTTONCLIENT_CALLBACK_FLAG_STATE1													(1u)
#define BUTTONCLIENT_CALLBACK_FLAG_STATE2													(2u)
#define BUTTONCLIENT_TIMER_DELAY_VALUE														(1000u)

static enuButtonStates_t genuOldState = BUTTON_OFF;
static enuTimerSelect_t genuTimerSelect;
static uint8_t gu8CallbackFlag = BUTTONCLIENT_CALLBACK_FLAG_STATE0;

static void ButtonClient_Callback(void);


/*************************************************************************************************
* Parameters	: enuDIOPinNo, enuButtonConnectionType, enuTimerSelect
* Return Value	: enuErrorStatus_t
* Description  : Initialize the button client according to the configurations
*************************************************************************************************/
void ButtonClient_Init(enuDIOPinNo_t enuDIOPinNo, enuButtonConnectionType_t enuButtonConnectionType, enuTimerSelect_t enuTimerSelect)
{
	/* Initializing the button driver according to the selected configurations */
	Button_Init(enuDIOPinNo, enuButtonConnectionType);
	/* Enabling the interrupt of the selected timer */
	if(enuTimerSelect == TIMER0)
	{
		T0_OV_InterruptEnable();	
	}
	else if(enuTimerSelect == TIMER1)
	{
		Timer1_OVF_InterruptEnable();
	}
	else
	{
		T2_OV_InterruptEnable();
	}
	genuTimerSelect = enuTimerSelect;
	/* Enabling the global interrupt */
	sei();
}

/*************************************************************************************************
* Parameters	: enuDIOPinNo, pfButtonClient_AppFunction
* Return Value	: enuErrorStatus_t
* Description  : Handle the debouncing of the selected button
*************************************************************************************************/
void ButtonClient_EventReceive(enuDIOPinNo_t enuDIOPinNo, void (*pfButtonClient_AppFunction)(enuButtonStates_t))
{
	enuButtonStates_t enuCurrentState;
	
	/* Checking if the timer is configured or not */
	if(gu8CallbackFlag == BUTTONCLIENT_CALLBACK_FLAG_STATE0)
	{
		/* Starting the timer with 1ms interval */
		if(genuTimerSelect == TIMER0)
		{
			T0_Start(BUTTONCLIENT_TIMER_DELAY_VALUE, ButtonClient_Callback);
		}
		else if(genuTimerSelect == TIMER1)
		{
			/**/
			/* Start timer 1 */
			/**/
		}
		else
		{
			T2_Start(BUTTONCLIENT_TIMER_DELAY_VALUE, ButtonClient_Callback);
		}
		gu8CallbackFlag = BUTTONCLIENT_CALLBACK_FLAG_STATE1;		
	}
	else if(gu8CallbackFlag == BUTTONCLIENT_CALLBACK_FLAG_STATE2)
	{
		/* Reading the current state of the button */
		Button_GetState(enuDIOPinNo, &enuCurrentState);
		/* Checking if the button state is changed or not */ 
		if(enuCurrentState != genuOldState)
		{
			/* Calling the application function with the current state of the button */
			pfButtonClient_AppFunction(enuCurrentState);
			/* Updating the old state of the button with the value of the current state */
			genuOldState = enuCurrentState;
		}
		else
		{
		}
		gu8CallbackFlag = BUTTONCLIENT_CALLBACK_FLAG_STATE1;
	}
	else
	{
	}
}


static void ButtonClient_Callback(void)
{
	gu8CallbackFlag = BUTTONCLIENT_CALLBACK_FLAG_STATE2;
}