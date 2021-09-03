/*****************************************************************************
* Task       : Design Patterns
* File Name  : Observer.c
* Description: Source file for the observer design pattern
* Author     : Amr Mohamed (Team 2)
* Date       : 23/8/2021
******************************************************************************/

/*- INCLUDES --------------------------------------------------*/
#include "Platform/Observer_Pattern/Observer.h"

/*- GLOBAL VARIABLES --------------------------------------------------*/
//A data base to store all sensor readings in the system
uint64_t Readings[15]={0};
//A data base to store the observer subscribers
ObserverSubscribeCard_t *subscribers[10]={NULLPTR};
//A counter to store the observer subscriber count
uint8_t subscriber_count=0;



/*- APIs IMPLEMENTATION-----------------------------------*/

/***********************************************************************************************
* Parameters (in) : ObserverSubscribeCard_t *CardPtr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to subscribe to the observer service
************************************************************************************************/
enuErrorStatus_t Obeserver_subscribe(ObserverSubscribeCard_t *CardPtr)
{
   //if the card pointer or struct elements are invalid
   if ((CardPtr == NULLPTR) || (CardPtr->Notify_fptr == NULLPTR) || (CardPtr->Data == NULLPTR)
   || (CardPtr->NotificationType >= INVALID) || (CardPtr->ReadingType >= INVALID) || subscriber_count==9)
   {
      //return error state
      return E_ERROR;
   }
   //add the subscriber card struct to the subscriber database 
   //increase the subscriber count
   subscribers[subscriber_count++]=CardPtr;
   //reset the subscriber notification flag
   CardPtr->NotificationFlag=0;
   //return an OK state
   return E_OK;
}



/***********************************************************************************************
* Parameters (in) : ObserverSubscribeCard_t *CardPtr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to unsubscribe from the observer service
************************************************************************************************/
enuErrorStatus_t Obeserver_unsubscribe(ObserverSubscribeCard_t *CardPtr)
{
   uint8_t index;
   //search the subscriber database for the subscriber card struct
   for (index=0;index<subscriber_count;index++)
   {
      //if user is found
      if(subscribers[index]==CardPtr)
      {
         //exit the search
         break;
      }
   }
   //if search was done and subscriber card struct has not been found
   if (index==subscriber_count)
   {
      //return a NOK state
      return E_ERROR;
   }
   //if card struct was found
   else
   {
      //shift all the other subscribers after this one to delete the 
      //required subscriber card pointer from the subscriber database
      //and prevent empty spaces in the database.
      for (;index<subscriber_count-1;index++)
      {
         
         subscribers[index]=subscribers[index+1];
      }
      // NULL the last subscriber element in the database as the subscriber has been shifted
      subscribers[index]=NULLPTR;
      //decrease the subscriber count
      subscriber_count--;
   }
   //return an OK state
   return E_OK;
}


/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to perform system monitoring and notify all the appropriate subscribers
************************************************************************************************/
enuErrorStatus_t Observer_notify(void)
{
   static enuErrorStatus_t Distance_Flag=0;
   static enuErrorStatus_t TEMP_Flag =0;
   static enuErrorStatus_t LIGHT_Flag =0;
   
   static enuErrorStatus_t UPDATE_Flag =0;
 
   //Get all system readings
   //if has not been obtained, get ultrasonic distance and store it in the readings database
   if (!Distance_Flag)    Distance_Flag=Ultrasonic_GetDistance(Readings+DISTANCE);
   //if has not been obtained, get the current temperature and store it in the readings database
   if (!TEMP_Flag)        TEMP_Flag = LM35_GetTemp(Readings+TEMPERATURE);
   //if has not been obtained, get the current light intensity and store it in the readings database
   if (!LIGHT_Flag)       LIGHT_Flag = LDR_GetLux (Readings+LIGHTING);;
   
   //if any readings have been obtained
   if (Distance_Flag || TEMP_Flag || LIGHT_Flag)
   {
      //check for all subscribers
      for (int i=0;i<subscriber_count;i++)
      {
         //reset the update flag for each subscriber
         UPDATE_Flag=E_ERROR;
         //which measurement object the subscriber needs?
         switch (subscribers[i]->ReadingType)
         {
            //if it's distance
            case DISTANCE:
               //if distance data has already been acquired
               if (Distance_Flag)
               {
                  //update the subscriber buffer with the new value
                  *(subscribers[i]->Data) = Readings[DISTANCE];
                  //change the update flag status for this subscriber
                  UPDATE_Flag=E_OK;
               }
               //else skip to the next subscriber
               else         continue;
               break;
              
            //if it's temperature   
            case TEMPERATURE:
               //if temperature data has already been acquired
               if (TEMP_Flag)
               {
                  //update the subscriber buffer with the new value
                  *(subscribers[i]->Data) = Readings[TEMPERATURE];
                  //change the update flag status for this subscriber
                  UPDATE_Flag=E_OK;
               }
               //else skip to the next subscriber
               else         continue;
               break;
            
            //if it's lighting  
            case LIGHTING:
               //if lighting data has already been acquired
               if (LIGHT_Flag)
               {
                  //update the subscriber buffer with the new value
                  *(subscribers[i]->Data) = Readings[LIGHTING];
                  //change the update flag status for this subscriber
                  UPDATE_Flag=E_OK;
               }
               //else skip to the next subscriber
               else         continue;
               break;
            
			//otherwise, just return an error message
            default:
               return E_ERROR;
               break;
         }
         
         //if the data buffer of current subscriber has been updated
         if (UPDATE_Flag==E_OK)
         {
            //determine the notification condition
            switch(subscribers[i]->NotificationType)
            {
               //if the subscriber demands notification on equality
               case EQUAL:
               //if the current value equals the reference value
               if (*(subscribers[i]->Data) == (subscribers[i]-> Data_Reference))
               {
                  //set the notification flag
                  subscribers[i]-> NotificationFlag = HIGH;
                  //call the notification callback function
                  subscribers[i]->Notify_fptr();
               }
               else
               {
                  //else, reset the notification flag
                  subscribers[i]-> NotificationFlag = LOW;
               }
               break;
               
               //if the subscriber demands notification on values higher than reference
               case GREATER:
               //if the current value is greater than the reference value
               if (*(subscribers[i]->Data) > (subscribers[i]-> Data_Reference))
               {
                  //set the notification flag
                  subscribers[i]-> NotificationFlag = HIGH;
                  //call the notification callback function
                  subscribers[i]->Notify_fptr();
               }
               else
               {
                  //else, reset the notification flag
                  subscribers[i]-> NotificationFlag = LOW;
               }
               break;
               
               //if the subscriber demands notification on values lower than reference
               case LOWER:
               //if the current value is lower than the reference value
               if (*(subscribers[i]->Data) < (subscribers[i]-> Data_Reference))
               {
                  //set the notification flag
                  subscribers[i]-> NotificationFlag = HIGH;
                  //call the notification callback function
                  subscribers[i]->Notify_fptr();
               }
               else
               {
                  //else, reset the notification flag
                  subscribers[i]-> NotificationFlag = LOW;
               }
               break;
               
               //if the subscriber demands notification on any value change
               case CHANGE:
               //if the current value is different than the reference value
               if (*(subscribers[i]->Data) != (subscribers[i]-> Data_Reference))
               {
                  //update the reference value
                  (subscribers[i]-> Data_Reference) = *(subscribers[i]->Data);
                  //set the notification flag
                  subscribers[i]-> NotificationFlag = HIGH;
                  //call the notification callback function
                  subscribers[i]->Notify_fptr();
               }
               else
               {
                  //else, reset the notification flag
                  subscribers[i]-> NotificationFlag = LOW;
               }
               break;
               
			   //otherwise, just return an error message
               default:
               return E_ERROR;
               break;
            }
         }
      }
      //reset all reading flags
      Distance_Flag=0;
      TEMP_Flag=0;
      LIGHT_Flag=0;
      return E_OK;
   }   
   return E_ERROR;
}


