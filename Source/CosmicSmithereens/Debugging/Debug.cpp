#include "stdafx.h"

#include "Debug.h"

bool Debugging::IsDebugBuild()
{
#if !defined(NDEBUG)

	return true;

#elif defined(NDEBUG)

	return false;

#endif
}
