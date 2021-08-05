#pragma once

#define MAX_DIGITS_IN_INT 12

#define EOS "\0\\EOS\0"
#define EOSW L"\0\\EOS\0"

typedef std::vector<std::string> StringVec;
typedef std::vector<std::wstring> StringVecW;

// Wide String and String Conversions

std::string WideStrToStr(const std::wstring& wstr);
std::wstring StrToWideStr(const std::string& str);

// Temporary string buffer functions for c_str()

const char*& TempStr(const char*& str);
const wchar_t*& TempWideStr(const wchar_t*& wstr);

// Misc String Functions
// Trim leading white space.
void TrimLeft(std::wstring& strInOut);
int WildcardMatch(const char* pat, const char* str);
void Split(const std::string& str, StringVec& vec, const char* delimiter);
void Split(const std::wstring& str, StringVecW& vec, const wchar_t* delimiter);
size_t SplitAtNull(const char* str, StringVec& vec);
size_t SplitAtNull(const wchar_t* str, StringVecW& vec);
bool StrCmp(const char* str1, const char* str2);
bool StrCmp(const wchar_t* str1, const wchar_t* str2);
bool StrCmp(std::string str1, std::string str2);
bool StrCmp(std::wstring str1, std::wstring str2);
std::string StrCat(std::string left, std::string right);
std::wstring StrCat(std::wstring left, std::wstring right);

// Char, WCHAR, TCHAR conversions...
long AnsiToWideCch(wchar_t* dest, const char* src, int charCount);
long WideToAnsiCch(char* dest, const wchar_t* src, int charCount);
long GenericToAnsiCch(char* dest, const TCHAR* src, int charCount);
long GenericToWideCch(wchar_t* dest, const TCHAR* src, int charCount);
long AnsiToGenericCch(TCHAR* dest, char* src, int charCount);
long WideToGenericCch(TCHAR* dest, wchar_t* src, int charCount);

// Number to String Conversions
std::string ToStr(int num, int base = 10);
std::string ToStr(unsigned int num, int base = 10);
std::string ToStr(long num, int base = 10);
std::string ToStr(unsigned long num, int base = 10);
std::string ToStr(long long num);
std::string ToStr(unsigned long long num);
std::string ToStr(float num);
std::string ToStr(double num);
std::string ToStr(bool val);

// String to Number Conversions
int ToINT(std::string str);
unsigned int ToUINT(std::string str);
long ToLONG(std::string str);
unsigned long ToULONG(std::string str);
long long ToLONGLONG(std::string str);
unsigned long long ToULONGLONG(std::string str);
float ToFLOAT(std::string str);
double ToDOUBLE(std::string str);
bool ToBOOL(std::string str);

#pragma warning(push)
#pragma warning(disable : 4311)	// Trucation when converting to int when compiling with 64-bits warning temporarily subdued.

class HashedString
{
public:
	explicit HashedString(char const* const pIdentString)
		: m_ident(hash_name(pIdentString))
		, m_identStr(pIdentString)
	{
	}

	unsigned long getHashValue(void) const
	{

		return reinterpret_cast<unsigned long>(m_ident);
	}

	const std::string& getStr() const
	{
		return m_identStr;
	}

	static void* hash_name(char const* pIdentStr);

	bool operator< (HashedString const& o) const
	{
		bool r = (getHashValue() < o.getHashValue());
		return r;
	}

	bool operator> (HashedString const& o) const
	{
		bool r = (getHashValue() > o.getHashValue());
		return r;
	}

	bool operator== (HashedString const& o) const
	{
		bool r = (getHashValue() == o.getHashValue());
		return r;
	}

private:

	void* m_ident;
	std::string		   m_identStr;
};
//Remove the warning for warning #4311...
#pragma warning(pop)
