#ifndef APP_DISPLAYDISTANCE_DISPLAYDISTANCE_H_
#define APP_DISPLAYDISTANCE_DISPLAYDISTANCE_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../ECUAL/LCD/LCD.h"
#include "../../ECUAL/Ultrasonic/Ultrasonic.h"
#include "../../LIB/STD_TYPES.h"

/*- GLOBAL VARIABLES ---------------------------------------*/
uint16_t gu16Distance;
uint8_t gu8UltrasonicFlag;

/*- FUNCTION DECLARATIONS ----------------------------------*/
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to initialize all APIs responsible for displaying distance
*************************************************************************************************/
enuErrorStatus_t DisplayDistance_Init(void);
/*************************************************************************************************
* Parameters (in) : void
* Parameters (out): enuErrorStatus_t
* Return Value    : E_ERROR, E_OK
* Description     : A function to display the current distance of the robot from any obstacle
*************************************************************************************************/
enuErrorStatus_t DisplayDistance_Update(void);

#endif /* APP_DISPLAYDISTANCE_DISPLAYDISTANCE_H_ */
