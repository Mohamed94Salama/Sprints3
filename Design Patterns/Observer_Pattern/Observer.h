/*****************************************************************************
* Task       : Design Patterns
* File Name  : Observer.h
* Description: Header file for the observer design pattern
* Author     : Amr Mohamed (Team 2)
* Date       : 23/8/2021
******************************************************************************/


#ifndef OBSERVER_H_
#define OBSERVER_H_

/*- INCLUDES --------------------------------------------------*/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MANIPULATE.h"
#include "ECUAL/Ultrasonic/Ultrasonic.h"
#include "ECUAL/Sensors/LM35.h"
#include "ECUAL/Sensors/LDR.h"

/*- ENUMS --------------------------------------------------*/
//Enum for the different notification conditions
typedef enum {EQUAL,GREATER,LOWER,CHANGE,INVALID}Notification_t;

//Enum for the different types of readings in the systems
typedef enum {DISTANCE,TEMPERATURE,LIGHTING,INVALID}Reading_t;

/*- STRUCTS --------------------------------------------------*/  
//Struct for the subscribe card to be used by the observer
typedef struct{
   void (*Notify_fptr)(void);          //pointer to function to be called on notification
   uint32_t *Data;                     //pointer to subscriber data buffer
   uint32_t Data_Reference;            //the reference new data will be compared to
   uint8_t NotificationFlag;           //subscriber notification flag
   Reading_t ReadingType;              //subscriber data source selection
   Notification_t NotificationType;    //observer notification 
   }ObserverSubscribeCard_t;


/*- APIs PROTOTYPES-----------------------------------*/

/***********************************************************************************************
* Parameters (in) : ObserverSubscribeCard_t *CardPtr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to subscribe to the observer service
************************************************************************************************/
enuErrorStatus_t Obeserver_subscribe(ObserverSubscribeCard_t *CardPtr);

/***********************************************************************************************
* Parameters (in) : ObserverSubscribeCard_t *CardPtr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to unsubscribe from the observer service
************************************************************************************************/
enuErrorStatus_t Obeserver_unsubscribe(ObserverSubscribeCard_t *CardPtr);


/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to perform system monitoring and notify all the appropriate subscribers
************************************************************************************************/
enuErrorStatus_t Observer_notify(void);


#endif /* OBSERVER_H_ */