#pragma once

extern "C"
{
/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler();
void EXTI0_IRQHandler(void);

void USB_LP_CAN1_RX0_IRQHandler(void);
void USB_LP_IRQHandler(void);
void USBWakeUp_IRQHandler();
void USBWakeUp_RMP_IRQHandler(void);

}
