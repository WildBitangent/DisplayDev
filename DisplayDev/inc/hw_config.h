#pragma once
extern "C"
{
#include "stm32f30x.h"

void Set_System();
void Set_USBClock();
void Enter_LowPowerMode();
void Leave_LowPowerMode();
void USB_Interrupts_Config();
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum();

}
