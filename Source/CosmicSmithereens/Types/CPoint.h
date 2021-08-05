#pragma once

// 2D Point
class CPoint
{
public:

	// Member Variables
	// x and y axes for a single point.
	long x, y;

	// Constructors
	CPoint()
	{
		x = y = 0;
	}
	CPoint(const long newX, const long newY)
	{
		x = newX; y = newY;
	}
	CPoint(const CPoint& newPoint)
	{
		x = newPoint.x; y = newPoint.y;
	}
	CPoint(const CPoint* pnewPoint)
	{
		x = pnewPoint->x; y = pnewPoint->y;
	}

	// Member Functions
	// Assignment Operations
	CPoint& operator=(const CPoint& newPoint)
	{
		x = newPoint.x; y = newPoint.y; return (*this);
	}
	CPoint& operator=(const CPoint* pnewPoint)
	{
		x = pnewPoint->x; y = pnewPoint->y; return (*this);
	}

	// Addition and Subtraction Operations
	CPoint& operator+=(const CPoint& newPoint)
	{
		x += newPoint.x; y += newPoint.y; return (*this);
	}
	CPoint& operator-=(const CPoint& newPoint)
	{
		x -= newPoint.x; y -= newPoint.y; return (*this);
	}
	CPoint& operator+=(const CPoint* pnewPoint)
	{
		x += pnewPoint->x; y += pnewPoint->y; return (*this);
	}
	CPoint& operator-=(const CPoint* pnewPoint)
	{
		x -= pnewPoint->x; y -= pnewPoint->y; return (*this);
	}
	CPoint operator+(const CPoint& other)
	{
		CPoint temp(this); temp += other; return temp;
	}
	CPoint operator-(const CPoint& other)
	{
		CPoint temp(this); temp -= other; return temp;
	}

	// Comparison Operations
	bool operator==(const CPoint& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
	bool operator!=(const CPoint& other) const
	{
		return (!((x == other.x) && (y == other.y)));
	}

	// Accessor Member Functions for Lua
	long GetX() const
	{
		return x;
	}
	long GetY() const
	{
		return y;
	}
	void SetX(const long newX)
	{
		x = newX;
	}
	void SetY(const long newY)
	{
		y = newY;
	}
	void Set(const long newX, const long newY)
	{
		x = newX; y = newY;
	}

	// Vector manipulations
	float Length() const
	{
		return sqrtf((float)((x * x) + (y * y)));
	}
};
