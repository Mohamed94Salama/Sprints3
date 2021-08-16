#ifndef APP_HBRIDGECONTROL_HBRIDGECONTROL_H_
#define APP_HBRIDGECONTROL_HBRIDGECONTROL_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../ECUAL/HBridge/HBridge.h"
#include "../../LIB/STD_TYPES.h"

/*- GLOBAL VARIABLES ---------------------------------------*/
uint16_t gu16Distance;

/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to initialize all APIs responsible for robot control
*************************************************************************************************/
enuErrorStatus_t HBridgeControl_Init(void);
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to control the movement of the robot
*************************************************************************************************/
enuErrorStatus_t HBridgeControl_Update(void);

#endif /* APP_HBRIDGECONTROL_HBRIDGECONTROL_H_ */
