#include "HBridge.h"


/* Internal Macros */
#define HBRIDGE_CLOCK_MIN_VALUE																				(-1l)
#define HBRIDGE_CLOCK_MAX_VALUE																				(8u)
#define HBRIDGE_MOTOR_SPEED_MIN_VALUE																		(0u)
#define HBRIDGE_MOTOR_SPEED_MAX_VALUE																		(100u)
#define HBRIDGE_MOTOR_DIRECTION_MIN_VALUE																	(-1l)
#define HBRIDGE_MOTOR_DIRECTION_MAX_VALUE																	(4u)

typedef enum {HBRIDGE_INIT_UNDONE, HBRIDGE_INIT_DONE} enuHBridgeState_t;
static enuHBridgeState_t enuHBridgeState = HBRIDGE_INIT_UNDONE;

static uint8_t gu8HBridgeMotorSpeed = 0;


#if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridge_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock)
{
   enuErrorStatus_t enuRetVar;
   
   if(((enuPWMCompareOutputMode == NORMAL_OPERATION)	|| (enuPWMCompareOutputMode == INVERTED_PWM) || (enuPWMCompareOutputMode == NON_INVERTED_PWM))	&&
		(enuPWMClock > HBRIDGE_CLOCK_MIN_VALUE)			&& (enuPWMClock < HBRIDGE_CLOCK_MAX_VALUE))
   {
	   /* Initializing the DIO pin for motor 1 enable pin */
	   DIO_PinInit(HBRIDGE_MOTOR_1_ENABLE_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the DIO pin for motor 2 enable pin */
	   DIO_PinInit(HBRIDGE_MOTOR_2_ENABLE_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the DIO pin for motor 1A direction pin */
	   DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the DIO pin for motor 1B direction pin */
	   DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the DIO pin for motor 2A direction pin */
	   DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the DIO pin for motor 2B direction pin */
	   DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, OUTPUT, NO_CONNECTION);
	   /* Initializing the PWM signal used for the HBridge module */
	   PWM_Init(enuPWMMode, enuPWMCompareOutputMode, enuPWMClock);
		enuHBridgeState = HBRIDGE_INIT_DONE;
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;	
}

/*************************************************************************************************
* Parameters	: u8HBridgeMotorSpeed
* Return Value	: enuErrorStatus_t
* Description  : Set the speed of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_SetSpeed(uint8_t u8HBridgeMotorSpeed)
{
   enuErrorStatus_t enuRetVar;
   
   if((enuHBridgeState == HBRIDGE_INIT_DONE) && (u8HBridgeMotorSpeed >= HBRIDGE_MOTOR_SPEED_MIN_VALUE) && (u8HBridgeMotorSpeed <= HBRIDGE_MOTOR_SPEED_MAX_VALUE))
   {
		gu8HBridgeMotorSpeed = u8HBridgeMotorSpeed;
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;
}

#elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Initialize the H Bridge module according to the configuration
*************************************************************************************************/
enuErrorStatus_t HBridge_Init(void)
{
	enuErrorStatus_t enuRetVar = E_ERROR;
	
	/* Initializing the DIO pin for motor 1 enable pin */
	DIO_PinInit(HBRIDGE_MOTOR_1_ENABLE_PIN_NO, OUTPUT, NO_CONNECTION);
	/* Initializing the DIO pin for motor 2 enable pin */
	DIO_PinInit(HBRIDGE_MOTOR_2_ENABLE_PIN_NO, OUTPUT, NO_CONNECTION);
	/* Initializing the DIO pin for motor 1A direction pin */
	DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, OUTPUT, NO_CONNECTION);
	/* Initializing the DIO pin for motor 1B direction pin */
	DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, OUTPUT, NO_CONNECTION);
	/* Initializing the DIO pin for motor 2A direction pin */
	DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, OUTPUT, NO_CONNECTION);
	/* Initializing the DIO pin for motor 2B direction pin */
	DIO_PinInit(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, OUTPUT, NO_CONNECTION);
	enuHBridgeState = HBRIDGE_INIT_DONE;
	enuRetVar = E_OK;
	return enuRetVar;	
}
#endif

/*************************************************************************************************
* Parameters	: enuHBridgeMotorDirection
* Return Value	: enuErrorStatus_t
* Description  : Set the direction of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_SetDirection(enuHBridgeMotorDirection_t enuHBridgeMotorDirection)
{
   enuErrorStatus_t enuRetVar;
   
   if((enuHBridgeState == HBRIDGE_INIT_DONE) && (enuHBridgeMotorDirection > HBRIDGE_MOTOR_DIRECTION_MIN_VALUE) && (enuHBridgeMotorDirection < HBRIDGE_MOTOR_DIRECTION_MAX_VALUE))
   {
	   /* Checking if the motor is moving forward or backward */
	   if(enuHBridgeMotorDirection == MOVE_FORWARD)
	   {
		   /* Setting the value of 1A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, HIGH);
		   /* Clearing the value of 1B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, LOW);
		   /* Setting the value of 2A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, HIGH);
		   /* Clearing the value of 2B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, LOW);
	   }
	   else if(enuHBridgeMotorDirection == MOVE_BACKWARD)
	   {
		   /* Clearing the value of 1A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, LOW);
		   /* Setting the value of 1B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, HIGH);
		   /* Clearing the value of 2A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, LOW);
		   /* Setting the value of 2B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, HIGH);
	   }
	   else if(enuHBridgeMotorDirection == TURN_LEFT)
	   {
		   /* Clearing the value of 1A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, LOW);
		   /* Setting the value of 1B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, HIGH);
		   /* Setting the value of 2A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, HIGH);
		   /* Clearing the value of 2B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, LOW);
	   }
	   else
	   {
		   /* Setting the value of 1A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1A_PIN_NO, HIGH);
		   /* Clearing the value of 1B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_1B_PIN_NO, LOW);
		   /* Clearing the value of 2A direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2A_PIN_NO, LOW);
		   /* Setting the value of 2B direction pin */
		   DIO_PinWrite(HBRIDGE_MOTOR_DIRECTION_2B_PIN_NO, HIGH);
	   }
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;	
}

/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Start the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_Start(void)
{
   enuErrorStatus_t enuRetVar;
   
   if(enuHBridgeState == HBRIDGE_INIT_DONE)
   {
	   #if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
	   /* Stopping both motors */
	   PWM_Start(gu8HBridgeMotorSpeed);
	   #elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
		/* Starting motor 1 to move */
		DIO_PinWrite(HBRIDGE_MOTOR_1_ENABLE_PIN_NO, HIGH);
		/* Starting motor 2 to move */
		DIO_PinWrite(HBRIDGE_MOTOR_2_ENABLE_PIN_NO, HIGH);
	   #endif
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;	
}

/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Stop the rotation of motors
*************************************************************************************************/
enuErrorStatus_t HBridge_Stop(void)
{
   enuErrorStatus_t enuRetVar;
   
   if(enuHBridgeState == HBRIDGE_INIT_DONE)
   {
	   #if HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_ENABLE_PWM_ON_ENABLE_PINS
	   /* Stopping both motors */
	   PWM_Stop();
	   #elif HBRIDGE_PWM_CONTROL_ON_ENABLE_PINS == HBRIDGE_DISABLE_PWM_ON_ENABLE_PINS
	   /* Stopping motor 1 */
	   DIO_PinWrite(HBRIDGE_MOTOR_1_ENABLE_PIN_NO, LOW);
	   /* Stopping motor 2 */
	   DIO_PinWrite(HBRIDGE_MOTOR_2_ENABLE_PIN_NO, LOW);
	   #endif
	   enuRetVar = E_OK;
   }
   else
   {
	   enuRetVar = E_ERROR;
   }
   return enuRetVar;	
}
