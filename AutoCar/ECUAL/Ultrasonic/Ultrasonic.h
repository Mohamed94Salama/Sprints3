/*****************************************************************************
* Task: Autonomous Car
* File Name: Ultrasonic.h
* Description: Header file for Ultrasonic driver
* Author: Amr Mohamed
* Date: 9/8/2021
******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*Includes -----------------------------------------------------------------*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"
#include "../../ECUAL/SW_ICU/SW_ICU.h"
#include "Ultrasonic_Cfg.h"

/*ENUMS -----------------------------------------------------------------*/
typedef enum{US_CH1,US_INVALID}enuUltrasonicChannel_t;

/*API Prototypes -----------------------------------------------------------------*/
/************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return value    : enuErrorStatus_t ... 1=E_OK - 0=E_ERROR
* Description     : A function to initialize the Ultrasonic Module
************************************************************************************/
enuErrorStatus_t Ultrasonic_Init(void);

/************************************************************************************
* Parameters (in) : enuUltrasonicChannel_t Channel
* Parameters (out): None
* Return value    : enuErrorStatus_t
* Description     : A function to send a trigger pulse to the Ultrasonic Module
************************************************************************************/
enuErrorStatus_t Ultrasonic_Trigger(enuUltrasonicChannel_t Channel);

 /************************************************************************************
 * Parameters (in) : None
 * Parameters (out): uint16_t *Distance
 * Return value    : enuErrorStatus_t
 * Description     : A function to check if ultrasonic reading is complete and return distance
 ************************************************************************************/
enuErrorStatus_t Ultrasonic_GetDistance(uint16_t *Distance);

/************************************************************************************
 * Parameters (in) : enuUltrasonicChannel_t Channel
 * Parameters (out): uint16_t *Distance
 * Return value    : enuErrorStatus_t
 * Description     : A function to get ultrasonic reading using polling
 ************************************************************************************/
enuErrorStatus_t Ultrasonic_GetReading_Polling(enuUltrasonicChannel_t Channel,uint32_t *Distance);


#endif /* ULTRASONIC_H_ */
