#pragma once

#include "PixelTransform.h"
#include "StackingTasks.h"
#include "BackgroundCalibration.h"
#include "BitmapExt.h"


#if defined(AVX_INTRINSICS) && defined(_M_X64)
class AvxAccumulation
{
	int resultWidth, resultHeight;
	C48BitColorBitmap* const pTempBitmap;
	C96BitFloatColorBitmap* const pOutput;
	const CTaskInfo& taskInfo;
public:
	AvxAccumulation() = delete;
	AvxAccumulation(const CRect& resultRect, const CTaskInfo& tInfo, C48BitColorBitmap* pTempBitmap, C96BitFloatColorBitmap* pOutput);
	AvxAccumulation(const AvxAccumulation&) = delete;
	AvxAccumulation(AvxAccumulation&&) = delete;
	AvxAccumulation& AvxAccumulation::operator=(const AvxAccumulation&) = delete;

	int accumulate(const int nrStackedBitmaps);
private:
	template <typename T>
	static bool checkBitmap(CColorBitmapT<T>* const pBitmap, const int nrBits);
};

#else

class AvxAccumulation
{
public:
	AvxAccumulation(const CRect&, const CTaskInfo&, C48BitColorBitmap*, C96BitFloatColorBitmap*) {}
	int accumulate(const int)
	{
		return 1;
	}
};

#endif