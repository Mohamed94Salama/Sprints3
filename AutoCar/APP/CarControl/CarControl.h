#ifndef APP_H_
#define APP_CARCONTROL_CARCONTROL_H_

/*- INCLUDES -----------------------------------------------*/
#include "../DisplayDistance/DisplayDistance.h"
#include "../GetDistance/GetDistance.h"
#include "../HBridgeControl/HBridgeControl.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): void
* Return Value    : void
* Description     : A function to initialize all APIs responsible for controlling the car
*************************************************************************************************/
void CarControl_Init(void);
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): void
* Return Value    : void
* Description     : A function to control the movement of the car based on the obstacle distance
*************************************************************************************************/
void CarControl_Update(void);

#endif /* APP_CARCONTROL_CARCONTROL_H_ */
