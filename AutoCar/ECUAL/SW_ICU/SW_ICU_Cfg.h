/*****************************************************************************
* Task: Autonomous Car
* File Name: SW_ICU_Cfg.h
* Description: Configuration file for Software ICU driver
* Author: Amr Mohamed
* Date: 12/8/2021
******************************************************************************/ 


#ifndef SW_ICU_CFG_H_
#define SW_ICU_CFG_H_

/*MACROS -----------------------------------------------------------------*/
//External Interrupt channel
#define SW_ICU_EX_INT_CH   										EXTINT_INT2
//maximum value of timer register
#define TIMER_MAX          										10001UL
//timer frequency in KHz
#define TIMER1_FREQ_KHZ       									20UL

#endif /* SW_ICU_CFG_H_ */
