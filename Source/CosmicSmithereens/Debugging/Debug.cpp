#include "stdafx.h"

#include "Debug.h"

bool Debugging::IsDebugBuild()
{
#if defined(_DEBUG)

	return true;

#elif !defined(_DEBUG)

	return false;

#endif
}
