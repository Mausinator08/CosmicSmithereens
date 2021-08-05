#pragma once

class CColor
{
public:

	float r, g, b, a;

	CColor();
	CColor(unsigned long argb);
	CColor(const float* value);
	CColor(float red, float green, float blue, float alpha);

	// casting
	operator unsigned long() const;

	operator float* ();
	operator const float* () const;

	// assignment operators
	CColor& operator += (const CColor& value);
	CColor& operator -= (const CColor& value);
	CColor& operator *= (float value);
	CColor& operator /= (float value);

	// unary operators
	CColor& operator + () const;
	CColor& operator - () const;

	// binary operators
	CColor& operator + (const CColor& value) const;
	CColor& operator - (const CColor& value) const;
	CColor& operator * (float value) const;
	CColor& operator / (float value) const;

	friend CColor& operator * (float value, const CColor& color);

	int operator == (const CColor& value) const;
	int operator != (const CColor& value) const;
};

extern CColor g_White;
extern CColor g_Black;
extern CColor g_Cyan;
extern CColor g_Red;
extern CColor g_Green;
extern CColor g_Blue;
extern CColor g_Yellow;
extern CColor g_Gray40;
extern CColor g_Gray25;
extern CColor g_Gray65;
extern CColor g_Transparent;
