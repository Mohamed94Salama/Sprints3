#include "APP/CarControl/CarControl.h"


int main(void)
{
   CarControl_Init();
   while (1) 
   {
      CarControl_Update();
   }
}
