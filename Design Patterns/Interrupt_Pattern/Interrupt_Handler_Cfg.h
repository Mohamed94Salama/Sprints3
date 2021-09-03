/*****************************************************************************
* Module     : Interrupt_Handler
* File Name  : Interrupt_Handler_Cfg.h
* Description: Configuration file for the Interrupt_Handler Pattern
* Author     : Kariman Karam
* Date       : Aug 23, 2021
******************************************************************************/

#ifndef PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_CFG_H_
#define PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_CFG_H_

/* Preprocessor */
#define TABLE_SIZE			5

/* Enums */
typedef enum {INT0_VECTOR_IDX,
	          INT1_VECTOR_IDX,
			  INT2_VECTOR_IDX,
			  UART_VECTOR_IDX,
			  SPI_VECTOR_IDX}ISRResponse_t;


#endif /* PLATFORM_INTERRUPT_PATTERN_INTERRUPT_HANDLER_CFG_H_ */
