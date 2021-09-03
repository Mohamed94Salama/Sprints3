/*****************************************************************************
* Module     : Interrupt_Handler
* File Name  : Interrupt_Handler.h
* Description: Header file for the Interrupt_Handler Pattern
* Author     : Kariman Karam (Team 2)
* Date       : Aug 23, 2021
******************************************************************************/


#ifndef PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_H_
#define PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_H_

/* Includes */
#include "Interrupt_Handler_Cfg.h"
#include "../../LIB/Data_types.h"

/* Global Variable */
typedef void (*VectorPtr)(void);
extern VectorPtr aOldVectors[TABLE_SIZE];

/* Functions Prototypes */
/***********************************************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : void
* Description     : A function to initialize All Interrupts
************************************************************************************************/
void Interrupt_Handler_Init(void);
/***********************************************************************************************
* Parameters (in) : pCallBack, u8InterruptIndex
* Parameters (out): None
* Return Value    : void
* Description     : A function to set the callback function of the interrupt in ISRAddress array
************************************************************************************************/
void Install(void (*pCallBack)(void), uint8_t u8InterruptIndex);
/***********************************************************************************************
* Parameters (in) : u8InterruptIndex
* Parameters (out): None
* Return Value    : void
* Description     : A function to remove the interrupt callback function from ISRAddress array
************************************************************************************************/
void DeInstall(uint8_t u8InterruptIndex);


#endif /* PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_H_ */
