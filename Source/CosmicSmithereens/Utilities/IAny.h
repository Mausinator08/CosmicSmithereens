#pragma once

class IAny
{
public:

	/**
	 *  Pure Virtual Destructor.
	 */
	virtual ~IAny() = 0;
};

/**
 *  Inline definition of Destructor.
 */
inline IAny::~IAny() {}
