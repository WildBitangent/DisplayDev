#include "Display.h"
#include "stm32f30x.h"
#include <algorithm>

using namespace util;

Display* Display::mInstance = nullptr;

Display* Display::getInstance()
{
	if(!mInstance)
		mInstance = new Display(8, 5);

	return mInstance;
}

void Display::setResolution(uint8_t width, uint8_t height)
{
	mResolution = { width, height };
	mOffset = width * 16;
	delete mFrontBuffer;
	delete mBackBuffer;

	mFrontBuffer = new uint8_t[width * height * 8];
	mBackBuffer = new uint8_t[width * height * 8];
}

Vector2u Display::getResolution()
{
	return mResolution;
}

Display::Display(uint8_t width, uint8_t height)
	: mResolution(width, height)
	, mOffset(width * 16)
	, mChangeBufferFlag(false)
	, mCurrentRow(0)
{
	mFrontBuffer = new uint8_t[width * height * 8];
	mBackBuffer = new uint8_t[width * height * 8];

	const uint8_t temp[7] { 0b00001110, 0b00011111, 0b00111111, 0b01111110, 0b00111111, 0b00011111, 0b00001110 };
	for(uint8_t i = 0; i < 7; i++)
	{
		mFrontBuffer[i * 8] = temp[i];
		mFrontBuffer[i * 8 + 4] = temp[i];
	}
	mFrontBuffer[60] = 0;

	mFrontBuffer[64] = 0xFF;
	for(uint8_t i = 0; i < 7; i++)
	{
		mFrontBuffer[129 + i * 8] = temp[i];
	}
	for(uint8_t i = 0; i < 8; i++)
	{
		mFrontBuffer[128 + i * 8] = (1 << i);
	}
}

Display::~Display()
{
	if(mInstance)
	{
		delete[] mFrontBuffer;
		delete[] mBackBuffer;
		mInstance = nullptr;
	}
}

void Display::Update()
{
	shiftRow(0xFF); 			//turn off rows
	shiftCol();					//write a row
	shiftRow(mCurrentRow++);	//turn on the row

	//if(mCurrentRow > mResolution.y * 8)
	if(mCurrentRow > 16)
	{
		mCurrentRow = 0;

		if(mChangeBufferFlag)
		{
			mChangeBufferFlag = false;

			uint8_t* temp = mFrontBuffer;
			mFrontBuffer = mBackBuffer;
			mBackBuffer = temp;
		}
	}
}

void Display::Draw()
{
	mChangeBufferFlag = true;
}

void Display::Write(uint16_t offset, uint8_t* buffer)
{
	if(offset < mResolution.x * mResolution.y * 8)
		std::copy(buffer, buffer + 64, mBackBuffer + offset);
}

void Display::shiftRow(uint8_t number)
{
	GPIOD->BRR = GPIO_Pin_1 | GPIO_Pin_2;

	for (int i = mResolution.y * 8; i >= 0; --i)
	{
		if(i % 16 == number)
			GPIOD->BSRR = GPIO_Pin_0;
		else
			GPIOD->BRR = GPIO_Pin_0;

		GPIOD->BSRR = GPIO_Pin_2;
		GPIOD->BRR = GPIO_Pin_2;
	}

	GPIOD->BSRR = GPIO_Pin_1;
}

void Display::shiftCol() //optimize
{
	GPIOD->BRR = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11;

	uint16_t n0 = mResolution.x * mCurrentRow;
	uint16_t n1 = mResolution.x * mCurrentRow + mOffset;
	uint16_t n2 = mResolution.x * mCurrentRow + 2 * mOffset;

	for(int x = mResolution.x; x >= 0; x--) //number of matrixes
	{
		for(int i = 7; i >= 0; i--)
		{
			//first group
			if(mFrontBuffer[n0 + x] & (1 << i))
				GPIOD->BRR = GPIO_Pin_3;
			else
				GPIOD->BSRR = GPIO_Pin_3;

			GPIOD->BSRR = GPIO_Pin_5;
			GPIOD->BRR = GPIO_Pin_5;

			//second group
			if(mFrontBuffer[n1 + x] & (1 << i))
				GPIOD->BRR = GPIO_Pin_6;
			else
				GPIOD->BSRR = GPIO_Pin_6;

			GPIOD->BSRR = GPIO_Pin_8;
			GPIOD->BRR = GPIO_Pin_8;

			//third group
			if(mFrontBuffer[n2 + x] & (1 << i))
				GPIOD->BRR = GPIO_Pin_9;
			else
				GPIOD->BSRR = GPIO_Pin_9;

			GPIOD->BSRR = GPIO_Pin_11;
			GPIOD->BRR = GPIO_Pin_11;
		}
	}

	GPIOD->BSRR = GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_10;
}

//void Display::shiftCol()
//{
//	GPIOD->BRR = GPIO_Pin_4 | GPIO_Pin_5;
//
//	for(int x = mResolution.x; x >= 0; x--)
//	{
//		uint16_t n = mResolution.x * mCurrentRow + x;
//		//uint8_t buf = mFrontBuffer[n];
//		for(int i = 7; i >= 0; i--)
//		{
//			if(mFrontBuffer[n] & (1 << i)) 	//Optimize
//				GPIOD->BRR = GPIO_Pin_3;
//			else
//				GPIOD->BSRR = GPIO_Pin_3;
//
//			GPIOD->BSRR = GPIO_Pin_5;
//			GPIOD->BRR = GPIO_Pin_5;
//		}
//	}
//
////	for (int i = mResolution.x * 8; i >= 0; --i)
////	{
////		if(mFrontBuffer[mCurrentRow * 8 + (i / 8) * 8] & (1 << (i % 8))) 	//Optimize
////			GPIOD->BSRR = GPIO_Pin_3;
////		else
////			GPIOD->BRR = GPIO_Pin_3;
////
////		GPIOD->BSRR = GPIO_Pin_5;
////		GPIOD->BRR = GPIO_Pin_5;
////	}
//
//	GPIOD->BSRR = GPIO_Pin_4;
//}

