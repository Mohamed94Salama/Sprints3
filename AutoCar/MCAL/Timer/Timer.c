
/*****************************************************************************
* Task: TIMER_DRIVER
* File Name: Timer.c
* Description: File containing timer driver functions
* Author: Amr Mohamed
* Date: 10/7/2021
******************************************************************************/



#include "Timer.h"

#define T0_TICKS     256
#define USEC_TO_SEC  1000000

void (*G_fptr)(void)=NULLPTR;
uint64_t Gu32_T0MaxOVCount=0;
uint64_t Gu32_T0CurrentOVCount=0;
uint8_t  Gu32_T0LastOVTicks=0;
uint16_t Gu16_T0Prescaler=0;

/************************************************************************************
* Parameters (in): enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize timer 0 according to the sent parameters
************************************************************************************/
enuErrorStatus_t T0_Init(enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler)
{
   //set the timer mode by setting the correct configuration of the WGM bits for the mode the user has selected 
   switch (enuMode)
   {
      case TIMER0_NORMAL_MODE:
      CLEAR_BIT(TCCR0_R,WGM00_B);
      CLEAR_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_PHASECORRECT_MODE:
      SET_BIT(TCCR0_R,WGM00_B);
      CLEAR_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_CTC_MODE:
      CLEAR_BIT(TCCR0_R,WGM00_B);
      SET_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_FASTPWM_MODE:
      SET_BIT(TCCR0_R,WGM00_B);
      SET_BIT(TCCR0_R,WGM01_B);
      break;
      default:
      return E_ERROR;
      break;
   }
   
   //clear the CS bits in the Timer control register and set the prescaler value
   TCCR0_R &= 0xF8;
   TCCR0_R |= enuScaler;
   
   //set the prescaler value in a global variable for other functions to use
   switch(enuScaler)
   {
      case TIMER0_STOP:          Gu16_T0Prescaler=0;       break;
      case TIMER0_SCALER_1:      Gu16_T0Prescaler=1;       break;
      case TIMER0_SCALER_8:      Gu16_T0Prescaler=8;       break;
      case TIMER0_SCALER_64:     Gu16_T0Prescaler=64;      break;
      case TIMER0_SCALER_256:    Gu16_T0Prescaler=256;     break;
      case TIMER0_SCALER_1024:   Gu16_T0Prescaler=1024;    break;
      default:                                             break;
   }
   //return E_OK state
   return E_OK;
}


/************************************************************************************
* Parameters (in): enuOC0Mode_t enuMode
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize the OCR0 pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t T0_OC0Mode(enuOC0Mode_t enuMode)
{
   //set the OC0 pin mode by setting the correct configuration of the COM bits for the mode the user has selected 
   switch (enuMode)
   {
      case OC0_DISCONNECTED:
      CLEAR_BIT(TCCR0_R,COM00_B);
      CLEAR_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_TOGGLE:
      SET_BIT(TCCR0_R,COM00_B);
      CLEAR_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_NON_INVERTING:
      CLEAR_BIT(TCCR0_R,COM00_B);
      SET_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_INVERTING:
      SET_BIT(TCCR0_R,COM00_B);
      SET_BIT(TCCR0_R,COM01_B);
      break;
      
      default:
      return E_ERROR;
      break;
   }
   //return E_OK state
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptEnable(void)
{
   //set the TOIE bit to enable the overflow interrupt
   SET_BIT(TIMSK_R,TOIE0_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptDisable(void)
{
   //clear the TOIE bit to disable the overflow interrupt
   CLEAR_BIT(TIMSK_R,TOIE0_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptEnable(void)
{
   //set the TOIE bit to enable output compare interrupt
   SET_BIT(TIMSK_R,OCIE0_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptDisable(void)
{
   //clear the TOIE bit to disable output compare interrupt
   CLEAR_BIT(TIMSK_R,OCIE0_B);
   return E_OK;
}



//Timer Ctrl Functions
/************************************************************************************
* Parameters (in): uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to start the timer and set a callback function to be called when time runs up
************************************************************************************/
enuErrorStatus_t T0_Start(uint64_t u64TimerValue, void(*pfCallback)(void))
{
   enuTimer0Scaler_t enuScaler=TIMER0_STOP;
   
   //check if the timer interrupts are enabled
   if (GET_BIT(TIMSK_R,TOIE0_B) || GET_BIT(TIMSK_R,OCIE0_B))
   {
      //check if the user has not sent a pointer to function to execute 
      if (pfCallback == NULLPTR)
      {
         //return error
         return E_ERROR;
      }
      else
      {
         //else store this pointer to function in the global pointer to function for the ISR to be able to execute
         G_fptr=pfCallback;
      }
   }
   
    //if the user sent a 0 time delay
    if (u64TimerValue==0)
    {
       //return an error
       return E_ERROR;
    }
    
    //else select the appropriate timer prescaler depending on the time sent for the least number of overflows
    else if (u64TimerValue<=256)
    {
       enuScaler=TIMER0_SCALER_8;
    }                                   
    else if (u64TimerValue>256 && u64TimerValue<=2048)
    {
       enuScaler=TIMER0_SCALER_64;
    }        
    else if (u64TimerValue>2048 && u64TimerValue<=8192)       
    {
       enuScaler=TIMER0_SCALER_256;   
    }
    else                                                      
    {
       enuScaler=TIMER0_SCALER_1024;
    }
    
   //initialize the timer in normal mode with the new prescaler 
   T0_Init(TIMER0_NORMAL_MODE,enuScaler);
    
    
    
   //calculate tick time of the selected prescaler
   uint32_t u32TimerFreq=F_CPU/Gu16_T0Prescaler;
   
   //calculate the number of overflows required to reach the selected time
   Gu32_T0MaxOVCount=((u64TimerValue*u32TimerFreq)/(T0_TICKS*USEC_TO_SEC));
   
   //calculate the time required to setup  the last overflow iteration
   Gu32_T0LastOVTicks=((u64TimerValue*u32TimerFreq)/USEC_TO_SEC)-(Gu32_T0MaxOVCount*T0_TICKS);

   
   //if the time can be achieved without overflows
   if (Gu32_T0MaxOVCount==0)
   {
      //set the timer value to overflow on the exact timing
      TCNT0_R= (T0_TICKS-Gu32_T0LastOVTicks);
   }
   else
   {
      //else, set the overflow to 0
      TCNT0_R=0;
   }
   
   
   
   //return E_OK state
   return E_OK;
}



/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to stop the timer if running
************************************************************************************/
enuErrorStatus_t T0_Stop(void)
{
   //turn off all timer interrupts
   T0_OV_InterruptDisable();
   T0_OC_InterruptDisable();
   //initialize the timer with no clock to stop it
   T0_Init(TIMER0_NORMAL_MODE,TIMER0_STOP);
   //clear the timer overflow flag
   SET_BIT(TIFR_R,TOV0_B);
   
   //reset all global variables
   Gu32_T0MaxOVCount=0;
   Gu32_T0LastOVTicks=0;
   Gu32_T0CurrentOVCount=0;
   
   //return E_OK state
   return E_OK;
}


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=time's up or 0=timer is still running
* Description: A function to check if a previously set up timer is still running or not
************************************************************************************/
enuErrorStatus_t T0_GetStatus(void)
{
      //if the current overflow value is less than the total overflows value
      if (Gu32_T0CurrentOVCount < Gu32_T0MaxOVCount)
      {
         //check the over flow flag
         if (GET_BIT(TIFR_R,TOV0_B))
         {
            //if set, clear it
            SET_BIT(TIFR_R,TOV0_B);
            //and increase the overflow counter
            Gu32_T0CurrentOVCount++;
         }
      }
      //if the current overflow value equals the calculated total overflows value
      else if (Gu32_T0CurrentOVCount == Gu32_T0MaxOVCount)
      {
         //set the timer value to the remaining timing
         TCNT0_R=((T0_TICKS-1)-Gu32_T0LastOVTicks);
         //clear the overflow flag
         SET_BIT(TIFR_R,TOV0_B);
         //increase the overflow counter
         Gu32_T0CurrentOVCount++;
      }
      
      //if the time is up
      else
      {
         //check if the global pointer to function holds a valid function address
         if (G_fptr != NULLPTR)
         {
            //if so, call the function
            G_fptr();
         }
         //stop the timer
         T0_Stop();
         //return a E_OK state
         return E_OK;
         
      }
      // if all failed, return an error state
   return E_ERROR;
}





/******************** ISR FUNCTIONS ****************************************/

//ISR function to run in case  of a timer overflow interrupt
ISR(TIMER0_OVF_vect)
{
   //if the current overflow value is less than the total overflows value
   if (Gu32_T0CurrentOVCount < Gu32_T0MaxOVCount)
   {
      //increase the overflow counter
      Gu32_T0CurrentOVCount++;
   }
   //if the current overflow value equals the calculated total overflows value
   else if (Gu32_T0CurrentOVCount == Gu32_T0MaxOVCount)
   {
      //set the timer value to the remaining timing
      TCNT0_R=((T0_TICKS-1)-Gu32_T0LastOVTicks);
      //increase the overflow counter
      Gu32_T0CurrentOVCount++;
   }
   //if the time is up
   else
   {
      //reset the overflow counter
      Gu32_T0CurrentOVCount=0;
      //check if the global pointer to function holds a valid function address
      if (G_fptr != NULLPTR)
      {
         //call the function
         G_fptr();
      }
   }      
}

/*******************************************************************************************/


/******************************** Timer 1 Functions ****************************************/



/************************************************************************************
* Parameters (in): enuTimer1Mode_t enuMode,enuTimer1Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize timer 1 according to the sent parameters
************************************************************************************/
enuErrorStatus_t Timer1_Init( enuTimer1Mode_t enuMode,enuTimer1Scaler_t enuScaler)
{
   //select the appropriate mode the user has selected by selecting 
   //and clearing the appropriate bits in the TCCR1A & TCCR1B Registers
   //Values are demonstrated in the datasheet
   switch (enuMode)
   {
      case TIMER1_NORMAL_MODE:
      case TIMER1_PWM_PHASE_8BIT_MODE:
      case TIMER1_PWM_PHASE_9BIT_MODE:
      case TIMER1_PWM_PHASE_10BIT_MODE:
      case TIMER1_CTC_OCRA_TOP_MODE:
      case TIMER1_FASTPWM_8BIT_MODE:
      case TIMER1_FASTPWM_9BIT_MODE:
      case TIMER1_FASTPWM_10BIT_MODE:
      case TIMER1_PWM_PHASE_FREQ_ICR_TOP_MODE:
      case TIMER1_PWM_PHASE_FREQ_OCRA_TOP_MODE:
      case TIMER1_PWM_PHASE_ICR_TOP_MODE:
      case TIMER1_PWM_PHASE_OCRA_TOP_MODE:
      case TIMER1_CTC_ICR_TOP_MODE:
      case TIMER1_FASTPWM_ICR_TOP_MODE:
      case TIMER1_FASTPWM_OCRA_TOP_MODE:
         
         TCCR1A_R &= 0b11111100;
         TCCR1A_R |= (enuMode & 0x03);
         
         TCCR1B_R &= 0b11100111;
         TCCR1B_R |= ((enuMode & 0b00001100)<<1);
         break;
      
      default:
         return E_ERROR;
         break;
      
   }
   
   //clear the prescaler bits in the TCCR1B
   TCCR1B_R &=0XF8;
   //enter the prescaler number the user has selected
   TCCR1B_R|=enuScaler;
   return E_OK;
}


/************************************************************************************
* Parameters (in): enuOC1A_Mode_t enu_oc1a_mode
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize the OCR1A pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t Timer1_OCRA1Mode(enuOC1A_Mode_t enu_oc1a_mode)
{
      //select the appropriate mode for the OCR1A Pin the user has selected
      //and clearing the appropriate bits in the TCCR1A Register, Values are
      //demonstrated in the datasheet
   switch (enu_oc1a_mode)
   {
      case OCRA_DISCONNECTED:
      CLEAR_BIT(TCCR1A_R,COM1A0_B);
      CLEAR_BIT(TCCR1A_R,COM1A1_B);
      break;
      case OCRA_TOGGLE:
      SET_BIT(TCCR1A_R,COM1A0_B);
      CLEAR_BIT(TCCR1A_R,COM1A1_B);
      break;
      case OCRA_NON_INVERTING:
      CLEAR_BIT(TCCR1A_R,COM1A0_B);
      SET_BIT(TCCR1A_R,COM1A1_B);
      break;
      case OCRA_INVERTING:
      SET_BIT(TCCR1A_R,COM1A0_B);
      SET_BIT(TCCR1A_R,COM1A1_B);
      break;
      
      default:
      return E_ERROR;
      break;
   }
   return E_OK;
}


/************************************************************************************
* Parameters (in): enuOC1B_Mode_t enu_oc1b_mode
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize the OCR1B pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t Timer1_OCRB1Mode(enuOC1B_Mode_t enu_oc1b_mode)
{
   //select the appropriate mode for the OCR1B Pin the user has selected
   //and clearing the appropriate bits in the TCCR1A Register, Values are
   //demonstrated in the datasheet
   switch (enu_oc1b_mode)
   {
      case OCRB_DISCONNECTED:
      CLEAR_BIT(TCCR1A_R,COM1B0_B);
      CLEAR_BIT(TCCR1A_R,COM1B1_B);
      break;
      case OCRB_TOGGLE:
      SET_BIT(TCCR1A_R,COM1B0_B);
      CLEAR_BIT(TCCR1A_R,COM1B1_B);
      break;
      case OCRB_NON_INVERTING:
      CLEAR_BIT(TCCR1A_R,COM1B0_B);
      SET_BIT(TCCR1A_R,COM1B1_B);
      break;
      case OCRB_INVERTING:
      SET_BIT(TCCR1A_R,COM1B0_B);
      SET_BIT(TCCR1A_R,COM1B1_B);
      break;
      
      default:
      return E_ERROR;
      break;
   }
   return E_OK;
}


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable over flow interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OVF_InterruptEnable(void)
{
   //set the appropriate pin in the TIMSK register to enable overflow interrupt
   SET_BIT(TIMSK_R,TOIE1_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable over flow interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OVF_InterruptDisable(void)
{
   //clear the appropriate pin in the TIMSK register to disable overflow interrupt
   CLEAR_BIT(TIMSK_R,TOIE1_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable output compare A interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCA_InterruptEnable(void)
{
   //set the appropriate pin in the TIMSK register to enable output compare A interrupt
   SET_BIT(TIMSK_R,OCIE1A_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable output compare A interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCA_InterruptDisable(void)
{
   //Clear the appropriate pin in the TIMSK register to disable output compare B interrupt
   CLEAR_BIT(TIMSK_R,OCIE1A_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable output compare B interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCB_InterruptEnable(void)
{
   //set the appropriate pin in the TIMSK register to enable output compare B interrupt
   SET_BIT(TIMSK_R,OCIE1B_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable output compare B interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCB_InterruptDisable(void)
{
   //Clear the appropriate pin in the TIMSK register to disable output compare A interrupt
   CLEAR_BIT(TIMSK_R,OCIE1B_B);
   return E_OK;
}

void (*Timer1_OVF_Callback)(void)=NULLPTR;
enuErrorStatus_t Timer1_OVF_SetCallback(void (*local_Fptr)(void))
{
   if (local_Fptr == NULLPTR)
   {
      return E_ERROR;
   }
   Timer1_OVF_Callback=local_Fptr;
   return E_OK;
}


uint32_t Timer1_OVF_Counter=0;
enuErrorStatus_t Timer1_GetOVFCount(uint32_t *buffer)
{
   if (buffer == NULLPTR)
   {
      return E_ERROR;
   }
   *buffer=Timer1_OVF_Counter;
   return E_OK;
}

enuErrorStatus_t Timer1_ResetOVFCount(void)
{
   Timer1_OVF_Counter=0;
   return E_OK;
}

ISR(TIMER1_OVF_vect)
{
   Timer1_OVF_Counter++;
   if (Timer1_OVF_Callback != NULLPTR)
   {
      Timer1_OVF_Callback();
   }
}




#define T2_TICKS     256

void (*G_fptr2)(void)=NULLPTR;
uint64_t Gu32_T2MaxOVCount=0;
uint64_t Gu32_T2CurrentOVCount=0;
uint8_t  Gu32_T2LastOVTicks=0;
uint16_t Gu16_T2Prescaler=0;

/************************************************************************************
* Parameters (in): enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize timer 0 according to the sent parameters
************************************************************************************/
enuErrorStatus_t T2_Init(enuTimer2Mode_t enuMode,enuTimer2Scaler_t enuScaler)
{
   //set the timer mode by setting the correct configuration of the WGM bits for the mode the user has selected
   switch (enuMode)
   {
      case TIMER2_NORMAL_MODE:
      CLEAR_BIT(TCCR2_R,WGM20_B);
      CLEAR_BIT(TCCR2_R,WGM21_B);
      break;
      case TIMER2_PHASECORRECT_MODE:
      SET_BIT(TCCR2_R,WGM20_B);
      CLEAR_BIT(TCCR2_R,WGM21_B);
      break;
      case TIMER2_CTC_MODE:
      CLEAR_BIT(TCCR2_R,WGM20_B);
      SET_BIT(TCCR2_R,WGM21_B);
      break;
      case TIMER2_FASTPWM_MODE:
      SET_BIT(TCCR2_R,WGM20_B);
      SET_BIT(TCCR2_R,WGM21_B);
      break;
      default:
      return E_ERROR;
      break;
   }

   //clear the CS bits in the Timer control register and set the prescaler value
   TCCR2_R &= 0xF8;
   TCCR2_R |= enuScaler;

   //set the prescaler value in a global variable for other functions to use
   switch(enuScaler)
   {
      case TIMER2_STOP:          Gu16_T2Prescaler=0;       break;
      case TIMER2_SCALER_1:      Gu16_T2Prescaler=1;       break;
      case TIMER2_SCALER_8:      Gu16_T2Prescaler=8;       break;
      case TIMER2_SCALER_64:     Gu16_T2Prescaler=64;      break;
      case TIMER2_SCALER_256:    Gu16_T2Prescaler=256;     break;
      case TIMER2_SCALER_1024:   Gu16_T2Prescaler=1024;    break;
      default:                                             break;
   }
   //return E_OK state
   return E_OK;
}


/************************************************************************************
* Parameters (in): enuOC0Mode_t enuMode
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to initialize the OCR0 pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t T2_OC2Mode(enuOC2Mode_t enuMode)
{
   //set the OC0 pin mode by setting the correct configuration of the COM bits for the mode the user has selected
   switch (enuMode)
   {
      case OC2_DISCONNECTED:
      CLEAR_BIT(TCCR2_R,COM20_B);
      CLEAR_BIT(TCCR2_R,COM21_B);
      break;
      case OC2_TOGGLE:
      SET_BIT(TCCR2_R,COM20_B);
      CLEAR_BIT(TCCR2_R,COM21_B);
      break;
      case OC2_NON_INVERTING:
      CLEAR_BIT(TCCR2_R,COM20_B);
      SET_BIT(TCCR2_R,COM21_B);
      break;
      case OC2_INVERTING:
      SET_BIT(TCCR2_R,COM20_B);
      SET_BIT(TCCR2_R,COM21_B);
      break;

      default:
      return E_ERROR;
      break;
   }
   //return E_OK state
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable overflow interrupt
************************************************************************************/
enuErrorStatus_t T2_OV_InterruptEnable(void)
{
   //set the TOIE bit to enable the overflow interrupt
   SET_BIT(TIMSK_R,TOIE2_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable overflow interrupt
************************************************************************************/
enuErrorStatus_t T2_OV_InterruptDisable(void)
{
   //clear the TOIE bit to disable the overflow interrupt
   CLEAR_BIT(TIMSK_R,TOIE2_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to enable output compare interrupt
************************************************************************************/
enuErrorStatus_t T2_OC_InterruptEnable(void)
{
   //set the TOIE bit to enable output compare interrupt
   SET_BIT(TIMSK_R,OCIE2_B);
   return E_OK;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to disable output compare interrupt
************************************************************************************/
enuErrorStatus_t T2_OC_InterruptDisable(void)
{
   //clear the TOIE bit to disable output compare interrupt
   CLEAR_BIT(TIMSK_R,OCIE2_B);
   return E_OK;
}



//Timer Ctrl Functions
/************************************************************************************
* Parameters (in): uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to start the timer and set a callback function to be called when time runs up
************************************************************************************/
enuErrorStatus_t T2_Start(uint64_t u64TimerValue, void(*pfCallback)(void))
{
   enuTimer2Scaler_t enuScaler=TIMER2_STOP;

   //check if the timer interrupts are enabled
   if (GET_BIT(TIMSK_R,TOIE2_B) || GET_BIT(TIMSK_R,OCIE2_B))
   {
      //check if the user has not sent a pointer to function to execute
      if (pfCallback == NULLPTR)
      {
         //return error
         return E_ERROR;
      }
      else
      {
         //else store this pointer to function in the global pointer to function for the ISR to be able to execute
         G_fptr2=pfCallback;
      }
   }

    //if the user sent a 0 time delay
    if (u64TimerValue==0)
    {
       //return an error
       return E_ERROR;
    }

    //else select the appropriate timer prescaler depending on the time sent for the least number of overflows
    else if (u64TimerValue<=256)
    {
       enuScaler=TIMER2_SCALER_8;
    }
    else if (u64TimerValue>256 && u64TimerValue<=2048)
    {
       enuScaler=TIMER2_SCALER_64;
    }
    else if (u64TimerValue>2048 && u64TimerValue<=8192)
    {
       enuScaler=TIMER2_SCALER_256;
    }
    else
    {
       enuScaler=TIMER2_SCALER_1024;
    }

   //initialize the timer in normal mode with the new prescaler
   T2_Init(TIMER2_NORMAL_MODE,enuScaler);



   //calculate tick time of the selected prescaler
   uint32_t u32TimerFreq=F_CPU/Gu16_T2Prescaler;

   //calculate the number of overflows required to reach the selected time
   Gu32_T2MaxOVCount=((u64TimerValue*u32TimerFreq)/(T2_TICKS*USEC_TO_SEC));

   //calculate the time required to setup  the last overflow iteration
   Gu32_T2LastOVTicks=((u64TimerValue*u32TimerFreq)/USEC_TO_SEC)-(Gu32_T2MaxOVCount*T2_TICKS);


   //if the time can be achieved without overflows
   if (Gu32_T2MaxOVCount==0)
   {
      //set the timer value to overflow on the exact timing
      TCNT2_R= (T2_TICKS-Gu32_T2LastOVTicks);
   }
   else
   {
      //else, set the overflow to 0
      TCNT2_R=0;
   }

   //return E_OK state
   return E_OK;
}



/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=E_OK or 0=FAIL
* Description: A function to stop the timer if running
************************************************************************************/
enuErrorStatus_t T2_Stop(void)
{
   //turn off all timer interrupts
   T2_OV_InterruptDisable();
   T2_OC_InterruptDisable();
   //initialize the timer with no clock to stop it
   T2_Init(TIMER2_NORMAL_MODE,TIMER2_STOP);
   //clear the timer overflow flag
   SET_BIT(TIFR_R,TOV2_B);

   //reset all global variables
   Gu32_T2MaxOVCount=0;
   Gu32_T2LastOVTicks=0;
   Gu32_T2CurrentOVCount=0;

   //return E_OK state
   return E_OK;
}


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=time's up or 0=timer is still running
* Description: A function to check if a previously set up timer is still running or not
************************************************************************************/
enuErrorStatus_t T2_GetStatus(void)
{
      //if the current overflow value is less than the total overflows value
      if (Gu32_T2CurrentOVCount < Gu32_T2MaxOVCount)
      {
         //check the over flow flag
         if (GET_BIT(TIFR_R,TOV2_B))
         {
            //if set, clear it
            SET_BIT(TIFR_R,TOV2_B);
            //and increase the overflow counter
            Gu32_T2CurrentOVCount++;
         }
      }
      //if the current overflow value equals the calculated total overflows value
      else if (Gu32_T2CurrentOVCount == Gu32_T2MaxOVCount)
      {
         //set the timer value to the remaining timing
         TCNT2_R=((T2_TICKS-1)-Gu32_T2LastOVTicks);
         //clear the overflow flag
         SET_BIT(TIFR_R,TOV2_B);
         //increase the overflow counter
         Gu32_T2CurrentOVCount++;
      }

      //if the time is up
      else
      {
         //check if the global pointer to function holds a valid function address
         if (G_fptr2 != NULLPTR)
         {
            //if so, call the function
            G_fptr2();
         }
         //stop the timer
         T2_Stop();
         //return a E_OK state
         return E_OK;

      }
      // if all failed, return an error state
   return E_ERROR;
}





/******************** ISR FUNCTIONS ****************************************/

//ISR function to run in case  of a timer overflow interrupt
ISR(TIMER2_OVF_vect)
{
   //if the current overflow value is less than the total overflows value
   if (Gu32_T2CurrentOVCount < Gu32_T2MaxOVCount)
   {
      //increase the overflow counter
      Gu32_T2CurrentOVCount++;
   }
   //if the current overflow value equals the calculated total overflows value
   else if (Gu32_T2CurrentOVCount == Gu32_T2MaxOVCount)
   {
      //set the timer value to the remaining timing
      TCNT2_R=((T2_TICKS-1)-Gu32_T2LastOVTicks);
      //increase the overflow counter
      Gu32_T2CurrentOVCount++;
   }
   //if the time is up
   else
   {
      //reset the overflow counter
      Gu32_T2CurrentOVCount=0;
      //check if the global pointer to function holds a valid function address
      if (G_fptr2 != NULLPTR)
      {
         //call the function
         G_fptr2();
      }
   }
}
