#ifndef APP_GETDISTANCE_GETDISTANCE_H_
#define APP_GETDISTANCE_GETDISTANCE_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../ECUAL/Ultrasonic/Ultrasonic.h"
#include "../../LIB/STD_TYPES.h"

/*- GLOBAL VARIABLES ---------------------------------------*/
extern uint16_t gu16Distance;
extern uint8_t gu8UltrasonicFlag;

/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to initialize all APIs responsible for getting distance
*************************************************************************************************/
enuErrorStatus_t GetDistance_Init(void);
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to get the current distance of the robot from any obstacle
*************************************************************************************************/
enuErrorStatus_t GetDistance_Update(void);

#endif /* APP_GETDISTANCE_GETDISTANCE_H_ */
