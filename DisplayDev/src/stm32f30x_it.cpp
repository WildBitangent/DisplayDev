#include "stm32f30x_it.h"
#include "usb_istr.h"
#include "Display.h"
#include "usb_pwr.h"

//extern __IO uint32_t UserButtonPressed;
//extern __IO uint32_t USBConnectTimeOut;
//__IO uint32_t i =0;

void SysTick_Handler()
{
	Display::getInstance()->Update();
}

void USB_LP_CAN1_RX0_IRQHandler()
{
	USB_Istr();
}

void USBWakeUp_IRQHandler()
{
	/* Initiate external resume sequence (1 step) */
	Resume(RESUME_EXTERNAL);
	EXTI_ClearITPendingBit(EXTI_Line18);
}
