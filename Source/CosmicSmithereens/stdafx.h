// std
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <list>
#include <deque>
#include <queue>
#include <regex>

// Math header
#include <cmath>

// Smart Pointers
#include <memory>

// cwalk
#include <cwalk.h>

// Macros for commonly and frequently used pointer delete/release code.
#ifndef SAFE_DELETE

#define SAFE_DELETE(x) \
    if (x)             \
        delete x;      \
    x = nullptr;

#endif

#ifndef CONST_SAFE_DELETE

#define CONST_SAFE_DELETE(x) \
    if (x)                   \
        delete x;

#endif

#ifndef SAFE_DELETE_ARRAY

#define SAFE_DELETE_ARRAY(x) \
    if (x)                   \
        delete[] x;          \
    x = nullptr;

#endif

#ifndef CONST_SAFE_DELETE_ARRAY

#define CONST_SAFE_DELETE_ARRAY(x) \
    if (x)                         \
        delete[] x;

#endif

#ifndef SAFE_RELEASE

#define SAFE_RELEASE(x)           \
    {                             \
        if (x)                    \
        {                         \
            x->AddRef();          \
            if (x->Release() > 0) \
                x->Release();     \
            x = NULL;             \
        }                         \
    }

#endif

#ifndef CONST_SAFE_RELEASE

#define CONST_SAFE_RELEASE(x)     \
    {                             \
        if (x)                    \
        {                         \
            x->AddRef();          \
            if (x->Release() > 0) \
                x->Release();     \
        }                         \
    }

#endif

// Color Opacity
extern const float fOPAQUE;
extern const int iOPAQUE;
extern const float fTRANSPARENT;
extern const int iTRANSPARENT;

// Color Conversions
// Convert DWORD to independant r, g, b, and a values ranging from 0 to 255 each.
#define DWORD_TO_RGBA(color_in, r, g, b, a) \
    {                                       \
        a = ((color_in >> 24) & 0xff);      \
        r = ((color_in >> 16) & 0xff);      \
        g = ((color_in >> 8) & 0xff);       \
        b = (color_in & 0xff);              \
    }
// Convert RGBA independant values to a single DWORD inputing values for r, g, b, and a from 0 to 255.
#define RGBA_TO_DWORD(color_out, r, g, b, a)              \
    {                                                     \
        color_out = (a << 24) | (r << 16) | (g << 8) | b; \
    }

// Data measurements
extern const int MEGABYTE;
extern const float ONEFOURTYFOUR_HERTZ;
extern const float ONETWENTY_HERTZ;
extern const float NINTY_HERTZ;
extern const float SIXTY_HERTZ;
extern const float THIRTY_HERTZ;

// Smart pointer manipulation
template <class T>
std::shared_ptr<T> MakeStrongPtr(std::weak_ptr<T> weakPtr);
