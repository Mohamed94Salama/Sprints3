/*****************************************************************************
* Task       : External Interrupt driver
* File Name  : EXT_INT.c
* Description: Source file for External Interrupt driver
* Author     : Kariman Karam
* Date       : 3/8/2021
******************************************************************************/

/*- INCLUDES --------------------------------------------------*/
#include "EXT_INT.h"

/*- PREPROCESSOR MACROS --------------------------------------------------*/
#define EXT_INT_MCUCR_R_BIT0											(0)
#define EXT_INT_MCUCR_R_BIT1											(1)
#define EXT_INT_MCUCR_R_BIT2											(2)
#define EXT_INT_MCUCR_R_BIT3											(3)

/*- GLOBAL VARIABLES --------------------------------------------------*/
void(*pEXTINT0CallBack)(void);
void(*pEXTINT1CallBack)(void);
void(*pEXTINT2CallBack)(void);


/*- APIs IMPLEMENTATION-----------------------------------*/

/***********************************************************************************************
* Parameters (in) : enuInterruptNum
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to initialize External Interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_Init( enuEXTINTNum enuInterruptNum)
{
	enuErrorStatus_t enuStatus = E_ERROR;

	//Enable peripheral interrupt enable
	switch(enuInterruptNum)
	{
	case EXTINT_INT0:
		SET_BIT(GICR_R, INT0_B);
		break;
	case EXTINT_INT1:
		SET_BIT(GICR_R, INT1_B);
		break;
	case EXTINT_INT2:
		SET_BIT(GICR_R, INT2_B);
		break;
	default:
		break;
	}
    //Enable GIE
	SET_BIT(SREG_R, SREG_I_B);

	enuStatus = E_OK;

	return enuStatus;
}

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, enuSenseMode
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_SetSenseMode(enuEXTINTSenseControl enuSenseMode, enuEXTINTNum enuInterruptNum)
{
	enuErrorStatus_t enuStatus = E_ERROR;

    if (enuInterruptNum==EXTINT_INT0)
    {
		switch(enuSenseMode)
		{
		case EXT_LOW_MODE :
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT0);
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT1);
		  break;
		case EXT_RAISING_MODE :
		 SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT0);
		 SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT1);
		  break;
		case EXT_FAILLING_MODE :
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT0);
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT1);
		  break;
		case EXT_CHANGE_MODE :
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT0);
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT1);
		  break;
		default:
			break;
		}
    }
    else if (enuInterruptNum==EXTINT_INT1)
    {
		switch(enuSenseMode)
		{
		case EXT_LOW_MODE :
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT2);
	      CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT3);
		  break;
		case EXT_RAISING_MODE :
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT2);
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT3);
		  break;
		case EXT_FAILLING_MODE :
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT2);
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT3);
		  break;
		case EXT_CHANGE_MODE :
		  SET_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT2);
		  CLEAR_BIT(MCUCR_R,EXT_INT_MCUCR_R_BIT3);
		  break;
		default:
			break;
		}
    }
    else if (enuInterruptNum==EXTINT_INT2)
    {
		switch(enuSenseMode)
		{
		case EXT_RAISING_MODE :
			SET_BIT(MCUCSR_R,ISC2_B);
			break;
		case EXT_FAILLING_MODE :
			CLEAR_BIT(MCUCSR_R,ISC2_B);
			break;
		default:
			break;
		}
    }

	enuStatus = E_OK;

	return enuStatus;
}

/***********************************************************************************************
* Parameters (in) : enuInterruptNum, pCallBack
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling if the user input an invalid parameter
* Description     : A function to set the sense mode of the External interrupt
************************************************************************************************/
enuErrorStatus_t EXTINT_SetCallBack(void(*pCallBack)(void), enuEXTINTNum enuInterruptNum)
{
	if(enuInterruptNum==EXTINT_INT0)
		pEXTINT0CallBack = pCallBack;
	else if(enuInterruptNum==EXTINT_INT1)
		pEXTINT1CallBack = pCallBack;
	else if(enuInterruptNum==EXTINT_INT2)
		pEXTINT2CallBack = pCallBack;

	return E_OK;
}


/* ISR to handle the External Interrupt Request 0 */
void __vector_1(void) __attribute__ ((signal,used));
/* ISR to handle the External Interrupt Request 1 */
void __vector_2(void) __attribute__ ((signal,used));
/* ISR to handle the External Interrupt Request 2 */
void __vector_3(void) __attribute__ ((signal,used));

/* ISR to handle the External Interrupt Request 0 */
void __vector_1(void)
{
	pEXTINT0CallBack();
}

/* ISR to handle the External Interrupt Request 1 */
void __vector_2(void)
{
	pEXTINT1CallBack();
}

/* ISR to handle the External Interrupt Request 2 */
void __vector_3(void)
{
	pEXTINT2CallBack();
}
