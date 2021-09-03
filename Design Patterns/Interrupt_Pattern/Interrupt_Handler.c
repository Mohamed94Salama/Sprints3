/*****************************************************************************
* Module     : Interrupt_Handler
* File Name  : Interrupt_Handler.c
* Description: Source file for the Interrupt_Handler Pattern
* Author     : Kariman Karam (Team 2)
* Date       : Aug 23, 2021
******************************************************************************/

/* Includes */
#include "Interrupt_Handler.h"
#include "../../MCAL/External_interrupt/EXT_INT.h"

/* Global Variable */
VectorPtr aOldVectors[TABLE_SIZE]={NULL_PTR};

/* Functions Declarations */
/***********************************************************************************************
* Parameters (in) : pCallBack, u8InterruptIndex
* Parameters (out): None
* Return Value    : void
* Description     : A function to set the callback function of the interrupt in aOldVectors array
************************************************************************************************/
void Install(void (*pCallBack)(void), ISRResponse_t InterruptIndex)
{
	/*Update the aOldVectors with the new addresses of callback functions*/
	aOldVectors[InterruptIndex] = pCallBack;
}

/***********************************************************************************************
* Parameters (in) : u8InterruptIndex
* Parameters (out): None
* Return Value    : void
* Description     : A function to remove the interrupt callback function from aOldVectors array
************************************************************************************************/
void DeInstall(ISRResponse_t InterruptIndex)
{
	/*Restore the old ISRs from oldVectors*/
	aOldVectors[InterruptIndex] = NULL_PTR;
}

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : ISR to handle the External Interrupt Request 0
************************************************************************************************/
void __vector_1(void)
{
	if(aOldVectors[INT0_VECTOR_IDX]!=NULL_PTR)
	{
		aOldVectors[INT0_VECTOR_IDX]();
	}
}

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : ISR to handle the External Interrupt Request 1
************************************************************************************************/
void __vector_2(void)
{
	if(aOldVectors[INT1_VECTOR_IDX]!=NULL_PTR)
	{
		aOldVectors[INT1_VECTOR_IDX]();
	}
}

/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : ISR to handle the External Interrupt Request 2
************************************************************************************************/
void __vector_3(void)
{
	if(aOldVectors[INT2_VECTOR_IDX]!=NULL_PTR)
	{
		aOldVectors[INT2_VECTOR_IDX]();
	}
}
