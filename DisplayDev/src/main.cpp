#include "main.h"
#include "Display.h"
//#include "gif.h"
#include "Usb.h"

//GifDecode gif;
//Usb usb = Usb(&gif.decode);


int main(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
//	Display::getInstance()->setResolution(8, 5);

	Set_System();
	Set_USBClock();
	USB_Interrupts_Config();

	USB_Init();
	//while (bDeviceState != CONFIGURED);

	/* GPIOE Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |
									GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	disp.shiftRow(0);
//	disp.shiftCol(0xAA);
//	disp.shiftCol(0x55);
//	disp.shiftRow(255);

	if(SysTick_Config(SystemCoreClock / (16 * 65)))
	{
		// Capture error
		while(1);
	}

	for(;;);
}
