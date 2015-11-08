#include "usb_lib.h"
#include "usb_istr.h"
#include "Usb.h"

namespace
{
//uint8_t count = 0;
//uint8_t buff[64];
//
//uint16_t nFrames = 0;
}
//extern Usb usb;

void EP1_IN_Callback(void)
{
	//TODO
}

void EP2_OUT_Callback() {
	//usb.processData();
}

//void EP2_OUT_Callback() {
//	uint16_t length = USB_SIL_Read(EP2_OUT, buff);
//
//	if(length > 1) {
//		if(count == 0) {
//			nFrames = buff[0] | (buff[1] << 8);
//
//			//Skipping width and height
//			//width = buff[2] | (buff[3] << 8);
//			//height = buff[4] | (buff[5] << 8);
//
//
//		}
//	}
//}

//void EP2_OUT_Callback(void)
//{
//	uint16_t length = USB_SIL_Read(EP2_OUT, buff);
//
//	if(length > 1)
//	{
//		Display::getInstance()->Draw(count * Display::getInstance()->getResolution().x * 8, buff);
//		count++;
//	}
//	else
//	{
//		Display::getInstance()->Draw();
//		count = 0;
//	}
//
//	//send token
//	SetEPRxValid(2);
//}
