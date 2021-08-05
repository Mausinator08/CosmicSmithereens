#include "stdafx.h"

#include "Utilities/StringHelpers.h"

// Wide String and String Conversions

std::string WideStrToStr(const std::wstring& wstr)
{
	if (wstr.empty())
	{
		return std::string();
	}

	std::string l_ConvertedString;
	int l_iSizeNeeded = 0;

	if ((l_iSizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL) - 1) > 0)
	{
		l_ConvertedString = std::string(l_iSizeNeeded, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &l_ConvertedString[0], l_iSizeNeeded, NULL, NULL);
	}

	return l_ConvertedString;
}

std::wstring StrToWideStr(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	std::wstring l_ConvertedString;

	int l_iSizeNeeded = 0;

	if ((l_iSizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0) - 1) > 0)
	{
		l_ConvertedString = std::wstring(l_iSizeNeeded, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &l_ConvertedString[0], l_iSizeNeeded);
	}

	return l_ConvertedString;
}

const char*& TempStr(const char*& str)
{
	return str;
}

const wchar_t*& TempWideStr(const wchar_t*& wstr)
{
	return wstr;
}

void TrimLeft(std::wstring& strInOut)
{
	int i = 0;
	int len = (int)strInOut.length();
	while (i < len)
	{
		TCHAR ch = strInOut[i];
		int white =
#ifdef UNICODE
			iswspace(ch);
#else
			isspace(ch);
#endif
		if (!white)
			break;
		++i;
	}

	if (i < len)
		strInOut = strInOut.substr(i);
}

int WildcardMatch(const char* pat, const char* str)
{
	int i, star;

new_segment:

	star = 0;
	if (*pat == '*')
	{
		star = 1;
		do
		{
			pat++;
		} while (*pat == '*');
	}

test_match:

	for (i = 0; pat[i] && (pat[i] != '*'); i++)
	{
		if (str[i] != pat[i])
		{
			if (!str[i]) return 0;
			if ((pat[i] == '?') && (str[i] != '.')) continue;
			if (!star) return 0;
			str++;
			goto test_match;
		}
	}
	if (pat[i] == '*')
	{
		str += i;
		pat += i;
		goto new_segment;
	}
	if (!str[i]) return 1;
	if (i && pat[i - 1] == '*') return 1;
	if (!star) return 0;
	str++;
	goto test_match;
}

void Split(const std::string& str, StringVec& vec, const char* delimiter)
{
	vec.clear();
	size_t strLen = str.length();

	if (strLen == 0)
		return;

	size_t startIndex = 0;
	size_t indexOfDel = str.find_first_of(delimiter, startIndex);

	if (indexOfDel > strLen)
	{
		return;
	}

	std::string del = delimiter;

	size_t indexOfDelEnd = indexOfDel + (del.length() - 1);

	if (indexOfDelEnd > strLen)
	{
		return;
	}

	while ((indexOfDel < strLen && indexOfDelEnd < strLen))
	{
		vec.push_back(str.substr(startIndex, indexOfDel - startIndex));
		startIndex = indexOfDelEnd + 1;
		if (startIndex >= strLen)
			break;
		indexOfDel = str.find_first_of(delimiter, startIndex);

		if (indexOfDel > strLen)
			break;

		indexOfDelEnd = indexOfDel + (del.length() - 1);

		if (indexOfDelEnd > strLen)
			break;
	}
	if (startIndex < strLen)
		vec.push_back(str.substr(startIndex));
}

void Split(const std::wstring& str, StringVecW& vec, const wchar_t* delimiter)
{
	vec.clear();
	size_t strLen = str.length();
	if (strLen == 0)
		return;

	size_t startIndex = 0;
	size_t indexOfDel = str.find_first_of(delimiter, startIndex);

	if (indexOfDel > strLen)
	{
		return;
	}

	std::wstring del = delimiter;

	size_t indexOfDelEnd = indexOfDel + (del.length() - 1);

	if (indexOfDelEnd > strLen)
	{
		return;
	}

	while ((indexOfDel < strLen && indexOfDelEnd < strLen))
	{
		vec.push_back(str.substr(startIndex, indexOfDel - startIndex));
		startIndex = indexOfDelEnd + 1;
		if (startIndex >= strLen)
			break;
		indexOfDel = str.find_first_of(delimiter, startIndex);

		if (indexOfDel > strLen)
			break;

		indexOfDelEnd = indexOfDel + (del.length() - 1);

		if (indexOfDelEnd > strLen)
			break;
	}
	if (startIndex < strLen)
		vec.push_back(str.substr(startIndex));
}

size_t SplitAtNull(const char* str, StringVec& vec)
{
	std::string strBuf = StrCat(str, EOS);
	char* pCBuffer = NULL;
	long strSize = 0;
	long startIndex = 0;
	size_t dwSize = 0;
	bool done = false;

	for (size_t i = 0; done != true; ++i)
	{
		++strSize;

		if (strBuf[i] == '\0')
		{
			char b[5];
			for (size_t j = 0; j < 5; ++j)
			{
				b[j] = strBuf[i + j];
			}

			if (StrCmp(b, EOS))
			{
				done = true;
			}

			long bytes = 0;

			pCBuffer = new char[strSize]();

			for (long j = startIndex; j < startIndex + strSize; ++j)
			{
				pCBuffer[bytes] = strBuf[j];
				++bytes;
			}

			vec.push_back(pCBuffer);
			dwSize += strSize;
			startIndex = i + 1;
			bytes = 0;
			strSize = 0;
			SAFE_DELETE_ARRAY(pCBuffer);
		}
	}

	return dwSize;
}

size_t SplitAtNull(const wchar_t* str, StringVecW& vec)
{
	std::wstring strBuf = str;
	strBuf += EOSW;
	wchar_t* sb = const_cast<wchar_t*>(strBuf.c_str());
	wchar_t* pCBuffer = NULL;
	long strSize = 0;
	long startIndex = 0;
	size_t dwSize = 0;
	bool done = false;

	for (size_t i = 0; done != true; ++i)
	{
		++strSize;

		if (sb[i] == L'\0')
		{
			wchar_t b[5];
			for (size_t j = 0; j < 5; ++j)
			{
				b[j] = sb[i + j];
			}

			if (StrCmp(b, EOSW))
			{
				done = true;
			}

			long bytes = 0;

			pCBuffer = new wchar_t[strSize]();

			for (long j = startIndex; j < startIndex + strSize; ++j)
			{
				pCBuffer[bytes] = sb[j];
				++bytes;
			}

			vec.push_back(pCBuffer);
			dwSize += strSize;
			startIndex = i + 1;
			bytes = 0;
			strSize = 0;
			SAFE_DELETE_ARRAY(pCBuffer);
		}
	}

	return dwSize;
}

bool StrCmp(const char* str1, const char* str2)
{
	if (strcmp(str1, str2) == 0)
	{
		return true;
	}

	return false;
}

bool StrCmp(const wchar_t* str1, const wchar_t* str2)
{
	if (strcmp(WideStrToStr(str1).c_str(), WideStrToStr(str2).c_str()) == 0)
	{
		return true;
	}

	return false;
}

bool StrCmp(std::string str1, std::string str2)
{
	if (strcmp(str1.c_str(), str2.c_str()) == 0)
	{
		return true;
	}

	return false;
}

bool StrCmp(std::wstring str1, std::wstring str2)
{
	if (strcmp(WideStrToStr(str1).c_str(), WideStrToStr(str2).c_str()) == 0)
	{
		return true;
	}

	return false;
}

std::string StrCat(std::string left, std::string right)
{
	std::string l_Result = "";

	l_Result += left;
	l_Result += right;

	return l_Result;
}

std::wstring StrCat(std::wstring left, std::wstring right)
{
	std::wstring l_Result = L"";

	l_Result += left;
	l_Result += right;

	return l_Result;
}

long AnsiToWideCch(wchar_t* dest, const char* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
		return 2;

	int nResult = mbstowcs(dest, src, charCount);
	dest[charCount - 1] = 0;

	if (nResult == 0)
		return 1;
	return 0;
}

long WideToAnsiCch(char* dest, const wchar_t* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
		return 2;

	int nResult = wcstombs(dest, src, charCount);
	dest[charCount - 1] = 0;

	if (nResult == 0)
		return 1;
	return 0;
}

long GenericToAnsiCch(char* dest, const TCHAR* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
	{
		return 2;
	}

#ifdef _UNICODE
	return WideToAnsiCch(dest, src, charCount);
#else
	strncpy(dest, src, charCount);
	dest[charCount - 1] = '\0';

	return 0;

#endif   
}

long GenericToWideCch(wchar_t* dest, const TCHAR* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
	{
		return 2;
	}

#ifdef _UNICODE
	wcsncpy(dest, src, charCount);
	dest[charCount - 1] = L'\0';

	return 0;

#else
	return AnsiToWideCch(dest, src, charCount);
#endif    
}

long AnsiToGenericCch(TCHAR* dest, char* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
	{
		return 2;
	}

#ifdef _UNICODE
	return AnsiToWideCch(dest, src, charCount);
#else
	strncpy(dest, src, charCount);
	dest[charCount - 1] = '\0';

	return 0;

#endif
}

long WideToGenericCch(TCHAR* dest, wchar_t* src, int charCount)
{
	if (dest == NULL || src == NULL || charCount < 1)
	{
		return 2;
	}

#ifdef _UNICODE
	wcsncpy(dest, src, charCount);
	dest[charCount - 1] = L'\0';

	return 0;

#else
	return WideToAnsiCch(dest, src, charCount);
#endif
}

// Number to String Conversions

std::string ToStr(int num, int base)
{
	char str[MAX_DIGITS_IN_INT];
	memset(str, 0, MAX_DIGITS_IN_INT);
	_itoa_s(num, str, MAX_DIGITS_IN_INT, base);

	return (std::string(str));
}

std::string ToStr(unsigned int num, int base)
{
	char str[MAX_DIGITS_IN_INT];
	memset(str, 0, MAX_DIGITS_IN_INT);
	_ultoa_s((unsigned long)num, str, MAX_DIGITS_IN_INT, base);

	return (std::string(str));
}

std::string ToStr(long num, int base)
{
	char str[MAX_DIGITS_IN_INT];
	memset(str, 0, MAX_DIGITS_IN_INT);
	_ltoa_s(num, str, MAX_DIGITS_IN_INT, base);

	return (std::string(str));
}

std::string ToStr(unsigned long num, int base)
{
	char str[MAX_DIGITS_IN_INT];
	memset(str, 0, MAX_DIGITS_IN_INT);
	_ultoa_s(num, str, MAX_DIGITS_IN_INT, base);

	return (std::string(str));
}

std::string ToStr(long long num)
{
	char str[64];
	memset(str, 0, 64);
	_sprintf_p(str, 64, "%lld", num);

	return (std::string(str));
}

std::string ToStr(unsigned long long num)
{
	char str[64];
	memset(str, 0, 64);
	_sprintf_p(str, 64, "%llu", num);

	return (std::string(str));
}

std::string ToStr(float num)
{
	char str[64];
	memset(str, 0, 64);
	_sprintf_p(str, 64, "%f", num);

	return (std::string(str));
}

std::string ToStr(double num)
{
	char str[64];
	memset(str, 0, 64);
	_sprintf_p(str, 64, "%fL", num);

	return (std::string(str));
}

std::string ToStr(bool val)
{
	return (std::string((val == true ? "true" : "false")));
}

int ToINT(std::string str)
{
	return atoi(str.c_str());
}

unsigned int ToUINT(std::string str)
{
	return static_cast<unsigned int>(atoi(str.c_str()));
}

long ToLONG(std::string str)
{
	return atol(str.c_str());
}

unsigned long ToULONG(std::string str)
{
	return static_cast<unsigned long>(atol(str.c_str()));
}

long long ToLONGLONG(std::string str)
{
	return atoll(str.c_str());
}

unsigned long long ToULONGLONG(std::string str)
{
	return static_cast<unsigned long long>(atoll(str.c_str()));
}

float ToFLOAT(std::string str)
{
	return (float)atof(str.c_str());
}

double ToDOUBLE(std::string str)
{
	return atof(str.c_str());
}

bool ToBOOL(std::string str)
{
	if (str == "true")
	{
		return true;
	}

	return false;
}

void* HashedString::hash_name(char const* pIdentStr)
{
	// largest prime smaller than 65536
	unsigned long BASE = 65521L;

	// NMAX is the largest n such that 255n(n+1)/2 +
	// (n+1)(BASE-1) <= 2^32-1
	unsigned long NMAX = 5552;

#define DO1(buf,i)  {s1 += tolower(buf[i]); s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

	if (pIdentStr == NULL)
		return NULL;

	unsigned long s1 = 0;
	unsigned long s2 = 0;

	for (size_t len = strlen(pIdentStr); len > 0; )
	{
		unsigned long k = len < NMAX ? len : NMAX;

		len -= k;

		while (k >= 16)
		{
			DO16(pIdentStr);
			pIdentStr += 16;
			k -= 16;
		}

		if (k != 0) do
		{
			s1 += tolower(*pIdentStr++);
			s2 += s1;
		} while (--k);

		s1 %= BASE;
		s2 %= BASE;
	}

#pragma warning(push)
#pragma warning(disable : 4312)

	return reinterpret_cast<void*>((s2 << 16) | s1);

#pragma warning(pop)
#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
}
