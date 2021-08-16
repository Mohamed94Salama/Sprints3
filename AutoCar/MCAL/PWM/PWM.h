#ifndef PWM_H_
#define PWM_H_

#include "../DIO/DIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"

typedef enum {PC_PWM_8_BITS = 1, PC_PWM_9_BITS, PC_PWM_10_BITS, 
			  FAST_PWM_8_BITS = 5, FAST_PWM_9_BITS, FAST_PWM_10_BITS,
			  PFC_PWM_ICR1, PFC_PWM_OCR1A, PC_PWM_ICR1, PC_PWM_OCR1A,
			  FAST_PWM_ICR1 = 14, FAST_PWM_OCR1A = 15} enuPWMMode_t;
typedef enum {NORMAL_OPERATION, NON_INVERTED_PWM = 2, INVERTED_PWM} enuPWMCompareOutputMode_t;
typedef enum {PWM_NO_CLOCK, PWM_NO_PRESCALER, PWM_PRESCALER_8, 
				  PWM_PRESCALER_64, PWM_PRESCALER_256, PWM_PRESCALER_1024} enuPWMClock_t;

/*************************************************************************************************
* Parameters	: enuPWMMode, enuPWMCompareOutputMode, enuPWMClock
* Return Value	: enuErrorStatus_t
* Description  : Initialize the PWM module according to the configuration
*************************************************************************************************/
enuErrorStatus_t PWM_Init(enuPWMMode_t enuPWMMode, enuPWMCompareOutputMode_t enuPWMCompareOutputMode, enuPWMClock_t enuPWMClock);
/*************************************************************************************************
* Parameters	: u8DutyCycle
* Return Value	: enuErrorStatus_t
* Description  : Start the PWM signal with the specified duty cycle
*************************************************************************************************/
enuErrorStatus_t PWM_Start(uint8_t u8DutyCycle);
/*************************************************************************************************
* Parameters	: void
* Return Value	: enuErrorStatus_t
* Description  : Stop the PWM signal immediately
*************************************************************************************************/
enuErrorStatus_t PWM_Stop(void);

#endif /* PWM_H_ */
