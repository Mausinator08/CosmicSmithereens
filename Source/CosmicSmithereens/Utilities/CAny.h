#pragma once

#include "IAny.h"

template<class T>
class CAny : public IAny
{
public:

	/**
	 *  Copy Constructor (Explicit).
	 *
	 *      @param [in] data 
	 */
	explicit CAny(const T& data) : m_data(data)
	{

	}

	/**
	 *  Constructor.
	 */
	CAny() {}

	/**
	 *  Operator=s the any.
	 *
	 *      @param [in] any 
	 *
	 *      @return the dynamic casted object to the needed type
	 */
	T operator=(const std::unique_ptr<IAny> any)
	{
		return dynamic_cast<CAny<T>&>(*any).m_data;
	}

	/**
	 *  Operator=s the any.
	 *
	 *      @param [in] data 
	 *
	 *      @return the needed type to the base type
	 */
	std::unique_ptr<IAny> operator=(T data)
	{
		return std::make_unique<IAny>().reset(new CAny<T>(data));
	}

	/**
	 *  The value of the templated type.
	 */
	T m_data;
};

template<class T>
bool operator==(T lhs, const std::unique_ptr<IAny> rhs)
{
	return lhs == dynamic_cast<CAny<T>&>(*rhs).m_data ? true : false;
}

template<class T>
bool operator==(const std::unique_ptr<IAny> lhs, T rhs)
{
	return rhs == dynamic_cast<CAny<T>&>(*lhs).m_data ? true : false;
}
