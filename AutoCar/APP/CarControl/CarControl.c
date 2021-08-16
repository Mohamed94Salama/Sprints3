/*- INCLUDES -----------------------------------------------*/
#include "CarControl.h"

/*- FUNCTION DEFINITIONS -----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): void
* Return Value    : void
* Description     : A function to initialize all APIs responsible for controlling the car
*************************************************************************************************/
void CarControl_Init(void)
{
	enuErrorStatus_t enuRetVar;

	/* Initializing the H-bridge Control component */
	enuRetVar = HBridgeControl_Init();
	if(enuRetVar == E_OK)
	{
		/* Initializing the Get Distance component */
		enuRetVar = GetDistance_Init();
		if(enuRetVar == E_OK)
		{
			/* Enabling the global interrupt */
			sei();
		}
		else
		{
		}
	}
	else
	{
	}
}

/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): void
* Return Value    : void
* Description     : A function to control the movement of the car based on the obstacle distance
*************************************************************************************************/
void CarControl_Update(void)
{
	static uint8_t u8LCDInitFlag = LOW;
	enuErrorStatus_t enuRetVar;

	/* Initializing the Display Distance component */
	enuRetVar = DisplayDistance_Init();
	if((u8LCDInitFlag == HIGH) || (enuRetVar == E_OK))
	{
		u8LCDInitFlag = HIGH;
		/* Getting the current distance from the Get Distance component */
		GetDistance_Update();
		/* Displaying the current distance from the Display Distance component */
		DisplayDistance_Update();
		/* Controlling the H-bridge module from the H-bridge Control component */
		HBridgeControl_Update();
	}
	else
	{
	}
}


