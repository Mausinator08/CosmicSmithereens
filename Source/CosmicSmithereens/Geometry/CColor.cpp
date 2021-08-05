#include "stdafx.h"

#include "CColor.h"

// Assigned color/vector values
CColor g_White(1.0f, 1.0f, 1.0f, fOPAQUE);
CColor g_Black(0.0f, 0.0f, 0.0f, fOPAQUE);
CColor g_Cyan(0.0f, 1.0f, 1.0f, fOPAQUE);
CColor g_Red(1.0f, 0.0f, 0.0f, fOPAQUE);
CColor g_Green(0.0f, 1.0f, 0.0f, fOPAQUE);
CColor g_Blue(0.0f, 0.0f, 1.0f, fOPAQUE);
CColor g_Yellow(1.0f, 1.0f, 0.0f, fOPAQUE);
CColor g_Gray40(0.4f, 0.4f, 0.4f, fOPAQUE);
CColor g_Gray25(0.25f, 0.25f, 0.25f, fOPAQUE);
CColor g_Gray65(0.65f, 0.65f, 0.65f, fOPAQUE);
CColor g_Transparent(1.0f, 0.0f, 1.0f, fTRANSPARENT);

CColor::CColor()
{
	r = g = b = a = 0.0f;
}

CColor::CColor(unsigned long argb)
{
	BYTE red, green, blue, alpha;

	DWORD_TO_RGBA(argb, red, green, blue, alpha);

	r = (float)(red / 255.0f);
	g = (float)(green / 255.0f);
	b = (float)(blue / 255.0f);
	a = (float)(alpha / 255.0f);
}

CColor::CColor(const float* value)
{
	r = *value;
	g = *value;
	b = *value;
	a = *value;
}

CColor::CColor(float red, float green, float blue, float alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

CColor::operator unsigned long() const
{
	DWORD color = 0;
	BYTE red = r * 255;
	BYTE green = g * 255;
	BYTE blue = b * 255;
	BYTE alpha = a * 255;

	RGBA_TO_DWORD(color, red, green, blue, alpha);

	return color;
}

CColor::operator float* ()
{
	float color[4];

	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	return color;
}

CColor::operator CONST float* () const
{
	float color[4];

	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	return (const float*)color;
}

CColor& CColor::operator+=(CONST CColor& value)
{
	r += value.r;
	g += value.g;
	b += value.b;
	a += value.a;

	return *this;
}

CColor& CColor::operator-=(CONST CColor& value)
{
	r -= value.r;
	g -= value.g;
	b -= value.b;
	a -= value.a;

	return *this;
}

CColor& CColor::operator*=(float value)
{
	r *= value;
	g *= value;
	b *= value;
	a *= value;

	return *this;
}

CColor& CColor::operator/=(float value)
{
	r /= value;
	g /= value;
	b /= value;
	a /= value;

	return *this;
}

CColor& CColor::operator+() const
{
	CColor color;
	color.r = +r;
	color.g = +g;
	color.b = +b;
	color.a = +a;

	return color;
}

CColor& CColor::operator-() const
{
	CColor color;
	color.r = -r;
	color.g = -g;
	color.b = -b;
	color.a = -a;

	return color;
}

CColor& CColor::operator+(CONST CColor& value) const
{
	CColor color;
	color.r = r + value.r;
	color.g = g + value.g;
	color.b = b + value.b;
	color.a = a + value.a;

	return color;
}

CColor& CColor::operator-(CONST CColor& value) const
{
	CColor color;
	color.r = r - value.r;
	color.g = g - value.g;
	color.b = b - value.b;
	color.a = a - value.a;

	return color;
}

CColor& CColor::operator*(float value) const
{
	CColor color;
	color.r = r * value;
	color.g = g * value;
	color.b = b * value;
	color.a = a * value;

	return color;
}

CColor& CColor::operator/(float value) const
{
	CColor color;
	color.r = r / value;
	color.g = g / value;
	color.b = b / value;
	color.a = a / value;

	return color;
}

BOOL CColor::operator==(CONST CColor& value) const
{
	if (r == value.r && g == value.g && b == value.b && a == value.a)
	{
		return 1;
	}

	return 0;
}

BOOL CColor::operator!=(CONST CColor& value) const
{
	if (r != value.r && g != value.g && b != value.b && a != value.a)
	{
		return 1;
	}

	return 0;
}

CColor& operator*(float value, CONST CColor& color)
{
	CColor c;

	c.r = value * color.r;
	c.g = value * color.g;
	c.b = value * color.b;
	c.a = value * color.a;

	return c;
}
