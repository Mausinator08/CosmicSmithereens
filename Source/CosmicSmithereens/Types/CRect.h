#pragma once

#include "CPoint.h"

// 2D Rectangle
class CRect
{
public:

	// Member Variables
	// Top, left, right, and bottom corners for the rectangle
	long top, left, right, bottom;
	enum RectCorner
	{
		INVALID_CORNER = 0, TOPLEFT_CORNER, TOPRIGHT_CORNER, BOTTOMLEFT_CORNER, BOTTOMRIGHT_CORNER
	};

	// Constructors
	CRect(void)
	{
		left = top = right = bottom = 0;
	}
	CRect(long newLeft, long newTop, long newRight, long newBottom)
	{
		Set(newLeft, newTop, newRight, newBottom);
	}
	CRect(const CRect& newRect)
	{
		left = newRect.left; top = newRect.top; right = newRect.right; bottom = newRect.bottom;
	}
	CRect(CRect* pnewRect)
	{
		left = pnewRect->left; top = pnewRect->top; right = pnewRect->right; bottom = pnewRect->bottom;
	}
	CRect(const CPoint& topLeft, const CPoint& bottomRight)
	{
		top = topLeft.y; left = topLeft.x; right = bottomRight.x; bottom = bottomRight.y;
	}

	// Assignment Operations
	CRect& operator=(const CRect& newRect)
	{
		left = newRect.left; top = newRect.top; right = newRect.right; bottom = newRect.bottom; return (*this);
	}
	CRect& operator=(const CRect* pnewRect)
	{
		left = pnewRect->left; top = pnewRect->top; right = pnewRect->right; bottom = pnewRect->bottom; return (*this);
	}

	// Addition and Subtraction Operations
	CRect& operator+=(const CRect& newRect)
	{
		left += newRect.left; top += newRect.top; right += newRect.right; bottom += newRect.bottom; return (*this);
	}
	CRect& operator-=(const CRect& newRect)
	{
		left -= newRect.left; top -= newRect.top; right -= newRect.right; bottom -= newRect.bottom; return (*this);
	}
	CRect& operator+=(const CRect* pnewRect)
	{
		left += pnewRect->left; top += pnewRect->top; right += pnewRect->right; bottom += pnewRect->bottom; return (*this);
	}
	CRect& operator-=(const CRect* pnewRect)
	{
		left -= pnewRect->left; top -= pnewRect->top; right -= pnewRect->right; bottom -= pnewRect->bottom; return (*this);
	}
	CRect operator+(CRect& other)
	{
		CRect temp(this); temp += other; return temp;
	}
	CRect operator-(CRect& other)
	{
		CRect temp(this); temp -= other; return temp;
	}

	// Use CPoint class from above for moving Rectangles around.
	CRect& operator+=(const CPoint& delta)
	{
		left += delta.x; top += delta.y; right += delta.x; bottom += delta.y; return (*this);
	}
	CRect& operator-=(const CPoint& delta)
	{
		left -= delta.x; top -= delta.y; right -= delta.x; bottom -= delta.y; return (*this);
	}
	CRect& operator+=(const CPoint* pDelta)
	{
		left += pDelta->x; top += pDelta->y; right += pDelta->x; bottom += pDelta->y; return (*this);
	}
	CRect& operator-=(const CPoint* pDelta)
	{
		left -= pDelta->x; top -= pDelta->y; right -= pDelta->x; bottom -= pDelta->y; return (*this);
	}
	CRect operator+(CPoint& delta)
	{
		CRect temp(this); temp += delta; return temp;
	}
	CRect operator-(CPoint& delta)
	{
		CRect temp(this); temp -= delta; return temp;
	}

	// Comparison Operations
	bool operator==(const CRect& other) const
	{
		return ((left == other.left) && (top == other.top) && (right == other.right) && (bottom == other.bottom));
	}
	bool operator!=(const CRect& other) const
	{
		return (!((left == other.left) && (top == other.top) && (right == other.right) && (bottom == other.bottom)));
	}

	// Member Functions
	// Collision Functions
	bool Collide(const CRect& other) const
	{
		if (other.bottom < top || other.right < left || other.left > right || other.top > bottom)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool Collide(const CPoint& p) const
	{
		if (p.x > left && p.x < right && p.y < bottom && p.y > top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsWithin(const CRect& other) const
	{
		return ((left >= other.left && top >= other.top && right <= other.right && bottom <= other.bottom) || (other.left >= left && other.top >= top && other.right <= right && other.bottom <= bottom));
	}
	bool IsWithin(const CPoint& other) const
	{
		return (other.x >= left && other.x <= right && other.y >= top && other.y <= bottom);
	}
	bool IsValid(void) const
	{
		return (left <= right && top <= bottom);
	}
	bool IsNull(void) const
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}

	// Usefull Functions
	void ShiftX(int dx)
	{
		left += dx; right += dx;
	}
	void ShiftY(int dy)
	{
		top += dy; bottom += dy;
	}
	void SetX(int x)
	{
		int dx = x - left; ShiftX(dx);
	}
	void SetY(int y)
	{
		int dy = y - top; ShiftY(dy);
	}

	// Accessor Member Functions for Lua
	long GetTop(void) const
	{
		return top;
	}
	long GetLeft(void) const
	{
		return left;
	}
	long GetRight(void) const
	{
		return right;
	}
	long GetBottom(void) const
	{
		return bottom;
	}
	CPoint GetCenter(void) const
	{
		if (IsValid())
			return (CPoint(left + ((right - left) / 2), top + ((bottom - top) / 2)));
		// TODO: Add MGK_ERROR macro after creating Logging.h
		return CPoint();
	}
	CPoint TopLeft(void) const
	{
		return CPoint(left, top);
	}
	CPoint TopRight(void) const
	{
		return CPoint(right, top);
	}
	CPoint BottomLeft(void) const
	{
		return CPoint(left, bottom);
	}
	CPoint BottomRight(void) const
	{
		return CPoint(right, bottom);
	}
	long GetWidth(void) const
	{
		return right - left;
	}
	long GetHeight(void) const
	{
		return bottom - top;
	}
	void Set(long newLeft, long newTop, long newRight, long newBottom)
	{
		left = newLeft; top = newTop; right = newRight; bottom = newBottom;
	}
	void MoveDelta(long dx, long dy)
	{
		left += dx; top += dy; right += dx; bottom += dy;
	}
	void MoveDelta(const CPoint deltaPoint)
	{
		MoveDelta(deltaPoint.x, deltaPoint.y);
	}
	void MoveTo(long x, long y)
	{
		long width = right - left;
		long height = bottom - top;
		left = x;
		right = left + width;
		top = y;
		bottom = top + height;
	}
	void MoveTo(const CPoint& point)
	{
		MoveTo(point.x, point.y);
	}
};
