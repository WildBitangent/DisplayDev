#include "gif.h"
#include <algorithm>

GifDecode::GifDecode()
	: mPacketCount(0)
	, mNumberOfFrames(0)
	, mWidth(0)
	, mHeight(0)
	, mDelay(nullptr)
	, mData(nullptr)
	, mDataCount(0)
	, mLastPacketNumber(0) {

}

GifDecode::~GifDecode() {
	if(mDelay)
		free(mDelay);
	if(mData)
		free(mData);
}

void GifDecode::decode(uint8_t* data, uint8_t length) {
	if(mPacketCount++ == 0) {
		mNumberOfFrames = data[0] | (data[1] << 8);
		mWidth = data[2] | (data[3] << 8);
		mHeight = data[4] | (data[5] << 8);
		uint16_t dataSize = (mWidth * mHeight * mNumberOfFrames) / 8;
		mLastPacketNumber = dataSize / 64 + (dataSize % 64) ? 1 : 0;

		mDelay = (uint16_t*)malloc(mNumberOfFrames * 2);
		mData = (uint8_t*)malloc((mWidth * mHeight * mNumberOfFrames) / 8);

//		if(mNumberOfFrames > 29)
//			std::copy(data + 6, data + 64, mDelay);
//		else {

		uint8_t dataPointer = 6 + (mNumberOfFrames * 2);
		std::copy(data + 6, data + dataPointer, mDelay);

		if(dataPointer < 64) {
			std::copy(data + dataPointer, data + 64, mData);
			mDataCount = 64 - dataPointer;
		}
	}
	else {
		if(mPacketCount++ != mLastPacketNumber) {
			std::copy(data, data + 64, mData + mDataCount);
			mDataCount += 64;
		}
		else {

		}


	}
}
