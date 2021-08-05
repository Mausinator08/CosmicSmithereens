#include "stdafx.h"

const float fOPAQUE = 1.0f;
const int iOPAQUE = 1;
const float fTRANSPARENT = 0.0f;
const int iTRANSPARENT = 0;

const int MEGABYTE = 1024 * 1024;
const float NINTY_HERTZ = 11.11f;
const float SIXTY_HERTZ = 16.66f;
const float THIRTY_HERTZ = 33.33f;

float ConvertFPSToHertz(float fps)
{
	return (float)(1000.00f / fps);
}

float ConvertHertzToFPS(float hertz)
{
	return (float)(1000.00f * hertz);
}

// Smart pointer manipulation
template<class T>
std::shared_ptr<T> MakeStrongPtr(std::weak_ptr<T> weakPtr)
{
	std::shared_ptr<T> strongPtr = weakPtr.lock();

	if (!strongPtr)
	{
		return std::shared_ptr<T>(nullptr);
	}

	return strongPtr;
}
