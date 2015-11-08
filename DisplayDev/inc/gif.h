#pragma once

class GifDecode
{
public:
					GifDecode();
					~GifDecode();
	void			decode(uint8_t* data, uint8_t length);

private:
	uint8_t			mPacketCount;
	uint16_t		mNumberOfFrames;
	uint16_t		mWidth;
	uint16_t		mHeight;
	uint16_t*		mDelay;
	uint8_t*		mData;

private:
	uint16_t		mDataCount;
	uint8_t			mLastPacketNumber;
};
