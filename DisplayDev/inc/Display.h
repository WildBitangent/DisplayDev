#pragma once
#include <stdint.h>
#include "Util.h"

namespace
{
using namespace util;
}

class Display
{
public:
	static Display* 		getInstance();
	void					setResolution(uint8_t width, uint8_t height);
	Vector2u				getResolution();

	void 					Update();

	void					Draw();
	void					Draw(uint16_t offset, uint8_t* buffer);

							~Display();

protected:
							Display(uint8_t width, uint8_t height);

private:
	void 					shiftRow(uint8_t number);
	void 					shiftCol();

private:
	Vector2u				mResolution;		//resolution of displayNic
	uint16_t				mOffset;			//matrix group offset
	static Display* 		mInstance;

	bool 					mChangeBufferFlag;	//flag when buffer flips
	uint8_t					mCurrentRow;		//row being drawn
	uint8_t* 				mFrontBuffer;
	uint8_t*				mBackBuffer;
};
