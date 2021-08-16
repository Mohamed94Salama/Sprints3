#include "PWM.h"


typedef volatile uint8_t* const pu8PWMRegisterAddress_t;
typedef volatile uint16_t* const pu16PWMRegisterAddress_t;

#define ICR1_R																					*((pu16PWMRegisterAddress_t) 0x46)
#define ICR1L_R																					*((pu8PWMRegisterAddress_t) 0x46)
#define ICR1H_R																					*((pu8PWMRegisterAddress_t) 0x47)
#define OCR1B_R																					*((pu16PWMRegisterAddress_t) 0x48)
#define OCR1BL_R																				*((pu8PWMRegisterAddress_t) 0x48)
#define OCR1BH_R																				*((pu8PWMRegisterAddress_t) 0x49)
#define OCR1A_R																					*((pu16PWMRegisterAddress_t) 0x4A)
#define OCR1AL_R																				*((pu8PWMRegisterAddress_t) 0x4A)
#define OCR1AH_R																				*((pu8PWMRegisterAddress_t) 0x4B)
#define TCCR1B_R																				*((pu8PWMRegisterAddress_t) 0x4E)
#define TCCR1A_R																				*((pu8PWMRegisterAddress_t) 0x4F)


/* Internal Macros */
#define PWM_CLOCK_MIN_VALUE																		(-1l)
#define PWM_CLOCK_MAX_VALUE																		(8u)
#define PWM_TC1_WGM10_WGM11_START_BIT															(0u)
#define PWM_TC1_WGM10_WGM11_MASK																(0x03)
#define PWM_TC1_WGM12_WGM13_START_BIT															(3u)
#define PWM_TC1_WGM12_WGM13_MASK																(0x0C)
#define PWM_TC1A_COMPARE_OUTPUT_MODE_START_BIT													(6u)
#define PWM_TC1A_COMPARE_OUTPUT_MODE_MASK														(0x03)
#define PWM_TC1B_COMPARE_OUTPUT_MODE_START_BIT													(4u)
#define PWM_TC1B_COMPARE_OUTPUT_MODE_MASK														(0x03)
#define PWM_CLOCK_SELECT_START_BIT																(0u)
#define PWM_CLOCK_SELECT_MASK																	(0x07)
#define PWM_FREQUENCY_10K																		(10000ul)
#define PWM_CALCULATE_REGISTER_VALUE(FREQUENCY, DUTY_CYCLE)										((((uint32_t)FREQUENCY) * ((uint32_t)DUTY_CYCLE)) / 100)
#define PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT												(0u)
#define PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK													(0xFFFF)
#define PWM_DUTY_CYCLE_MIN_VALUE																(0u)
#define PWM_DUTY_CYCLE_MAX_VALUE																(100u)

typedef enum {PWM_INIT_UNDONE, PWM_INIT_DONE} enuPWMState_t;
static enuPWMState_t enuPWMState = PWM_INIT_UNDONE;

static enuPWMCompareOutputMode_t enuPWMCompareOutputModeState;


/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the PWM module according to the configuration
*************************************************************************************************/
enuErrorStatus_t PWM_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock)
{
	enuErrorStatus_t enuRetVar;
	
	if(((enuPWMCompareOutputMode == NORMAL_OPERATION)	|| (enuPWMCompareOutputMode == INVERTED_PWM) || (enuPWMCompareOutputMode == NON_INVERTED_PWM))	&&
		(enuPWMClock > PWM_CLOCK_MIN_VALUE)					&& (enuPWMClock < PWM_CLOCK_MAX_VALUE)) 
	{
		/* Initializing OCR1A as output pin */
		DIO_PinInit(PD4, OUTPUT, NO_CONNECTION);
		/* Initializing OCR1B as output pin */
		DIO_PinInit(PD5, OUTPUT, NO_CONNECTION);
		/* Selecting the PWM module mode */
		ASSIGN_BITS(TCCR1A_R, PWM_TC1_WGM10_WGM11_START_BIT, enuPWMMode, PWM_TC1_WGM10_WGM11_MASK);
		ASSIGN_BITS(TCCR1B_R, PWM_TC1_WGM12_WGM13_START_BIT, enuPWMMode, PWM_TC1_WGM12_WGM13_MASK);
		/* Selecting the behavior of the compare match mode output for channel A (Inverted or Non-inverted PWM) */
		ASSIGN_BITS(TCCR1A_R, PWM_TC1A_COMPARE_OUTPUT_MODE_START_BIT, enuPWMCompareOutputMode, PWM_TC1A_COMPARE_OUTPUT_MODE_MASK);
		/* Selecting the behavior of the compare match mode output for channel B (Inverted or Non-inverted PWM) */
		ASSIGN_BITS(TCCR1A_R, PWM_TC1B_COMPARE_OUTPUT_MODE_START_BIT, enuPWMCompareOutputMode, PWM_TC1B_COMPARE_OUTPUT_MODE_MASK);
		/* Selecting the pre-configured clock prescaler value */
		ASSIGN_BITS(TCCR1B_R, PWM_CLOCK_SELECT_START_BIT, enuPWMClock, PWM_CLOCK_SELECT_MASK);
		/* Stopping the PWM signal at the beginning of initialization phase */
		if(enuPWMCompareOutputMode == INVERTED_PWM)
		{
			CLEAR_BITS(OCR1A_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
			CLEAR_BITS(OCR1B_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
		}
		else if(enuPWMCompareOutputMode == NON_INVERTED_PWM)
		{
			SET_BITS(OCR1A_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
			SET_BITS(OCR1B_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
		}
		else
		{
		}
		/* Saving the value of the compare output mode value into a temporary variable */
		enuPWMCompareOutputModeState = enuPWMCompareOutputMode;
		enuPWMState = PWM_INIT_DONE;
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;	
}

/*************************************************************************************************
* Parameters	: u8DutyCycle
* Return Value	: enuErrorStatus_t
* Description  : Start the PWM signal with the specified duty cycle
*************************************************************************************************/
enuErrorStatus_t PWM_Start(uint8_t u8DutyCycle)
{
	enuErrorStatus_t enuRetVar = E_OK;
	uint16_t u16PWMRegisterValue;
	
	if((enuPWMState == PWM_INIT_DONE) && (u8DutyCycle >= PWM_DUTY_CYCLE_MIN_VALUE) && (u8DutyCycle <= PWM_DUTY_CYCLE_MAX_VALUE))
	{
		ICR1_R = PWM_FREQUENCY_10K;
		/* Calculating the PWM register value required according to the equation */
		u16PWMRegisterValue = PWM_CALCULATE_REGISTER_VALUE(ICR1_R, u8DutyCycle);
		/* Loading the PWM register value into OCR1 registers */
		OCR1A_R = u16PWMRegisterValue;
		OCR1B_R = u16PWMRegisterValue;
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
* Description  : Stop the PWM signal immediately
*************************************************************************************************/
enuErrorStatus_t PWM_Stop(void)
{
	enuErrorStatus_t enuRetVar = E_OK;
	
	if(enuPWMState == PWM_INIT_DONE)
	{
		/* Stopping the PWM signal at the beginning of initialization phase */
		if(enuPWMCompareOutputModeState == INVERTED_PWM)
		{
			CLEAR_BITS(OCR1A_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
			CLEAR_BITS(OCR1B_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
		}
		else if(enuPWMCompareOutputModeState == NON_INVERTED_PWM)
		{
			SET_BITS(OCR1A_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
			SET_BITS(OCR1B_R, PWM_TC1_COMPARE_OUTPUT_REGISTER_START_BIT, PWM_TC1_COMPARE_OUTPUT_REGISTER_MASK);
		}
		else
		{
		}
		enuRetVar = E_OK;
	}
	else
	{
		enuRetVar = E_ERROR;
	}
	return enuRetVar;	
}
