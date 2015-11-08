#pragma once
#include <stdint.h>
#include <functional>

class Usb
{
public:
	typedef std::function<void(uint8_t*/* data, uint16_t length*/)> functPrototype;
public:
						Usb(functPrototype fun, uint16_t bufferSize = 1280);
						Usb() = delete;
						~Usb();

	void				processData();

private:
	uint8_t* 			mData;
	functPrototype		mCallback;

private:
	//uint8_t				mPacketToRecieve; //Can't be higher than buffSize / 64 ~
	uint8_t 			mPacketCount;
	uint16_t			mDataPtr;
};
