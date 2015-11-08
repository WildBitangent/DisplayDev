#include "Usb.h"
#include "usb_lib.h"
#include <stdlib.h>

Usb::Usb(functPrototype fun, uint16_t bufferSize)
	: mCallback(fun)
//	, mPacketToRecieve(20)
	, mPacketCount(0)
	, mDataPtr(0) {
	//TODO add protection if malloc fails
	mData = (uint8_t*)malloc(bufferSize);
}

Usb::~Usb() {
	if(mData)
		free(mData);
}

void Usb::processData() {
	uint8_t length = USB_SIL_Read(EP2_OUT, mData + mDataPtr);

	mDataPtr += length;
	if(++mPacketCount == 20/*mPacketToRecieve*/) {
		//mPacketToRecieve = mCallback(mData);
		mCallback(mData);
		mPacketCount = 0;
		mDataPtr = 0;
	} else if (length == 1) {
		//mPacketToRecieve = 20;
		mCallback(mData/*, mPacketCount*/);
		mPacketCount = 0;
		mDataPtr = 0;
	}
}
