#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <locale.h>

/*
*	文件名:	character.h
*	功	能:	wchar_t * 与 char * 之间的转换，string 与wstring之间的转换
*	说	明:	wchar_t * 与 char * 之间的转换 之间转换 方式采用动态申请内存方式
*			宏TEXT_ANTI_TO_TCHAR等都是申请了一个匿名临时对象，并且调用这个临时对象
*			的方法返回wchar_t * 或char * 指针
*			使用时应当注意: 临时对象在出了作用域之后，会析构内部申请的内存，
*			所以以下方式的调用是错误的:
*			
*		1. ************************************************
*			char charbuf[500]="你好"
*			wchar_t * pss = TEXT_ANTI_TO_TCHAR(charbuf);  //错误的方式，返回的指针已经被析构
			在给pss 赋值之前，匿名对象已经调用了析构函数
*			************************************************
*			
		2.	wcout << TEXT_ANTI_TO_TCHAR(charbuf)<< endl; 这样连用的调用方式是正确的
*			
*			如果要保存，请使用下面几种方式：
*		3.	*************************************************
*			Ascii_To_Wide as(charbuf) ;// 申明命名对象，调用转换方法
*			wchar_t * tst = as.wchar_rep();	
*			*************************************************
*		4.	**************************************************
*			TCHAR ss[1024];// 申请buf,将数据复制到buf中，(要足够的空间)
*			_tcscpy(ss, TEXT_ANTI_TO_TCHAR(charbuf)); 
*			**************************************************
*			
*			inline void InitLocal() 函数是为了输出wchar_t * 中的中文而设置，在调用
*			wcout wprintf 等输出函数时候，如果不能输出正常的字符串，请先调用该函数
*			可以解决调试输出问题
*
*/

//inline void NDSCommonLibs::InitLocal();

//以下是char* 与wchar_t *直接转换
#ifdef _UNICODE
# define TEXT_ALWAYS_CHAR(STRING) (NDSCommonLibs::Wide_To_Ascii(STRING).char_rep())
# define TEXT_ALWAYS_WCHAR(STRING) STRING
# define TEXT_CHAR_TO_TCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide(STRING).wchar_rep())
# define TEXT_WCHAR_TO_TCHAR(STRING) STRING
# define TEXT_ANTI_TO_TCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide(STRING).wchar_rep())
//
# define TEXT_ALWAYS_UTF8(STRING) (NDSCommonLibs::Wide_To_Ascii(CP_UTF8, STRING).char_rep())
# define TEXT_CHAR_TO_UTF8(STRING) (NDSCommonLibs::Ascii_To_Utf8(STRING).char_rep())
# define TEXT_UTF8_TO_CHAR(STRING) (NDSCommonLibs::Utf8_To_Ascii(STRING).char_rep())
# define TEXT_UTF8_TO_WCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide(CP_UTF8, STRING).wchar_rep())
# define TEXT_UTF8_TO_TCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide(CP_UTF8, STRING).wchar_rep())
#else
# define TEXT_ALWAYS_CHAR(STRING) STRING
# define TEXT_ALWAYS_WCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide (STRING).wchar_rep ())
# define TEXT_CHAR_TO_TCHAR(STRING) STRING
# define TEXT_WCHAR_TO_TCHAR(STRING) (NDSCommonLibs::Wide_To_Ascii (STRING).char_rep ())
# define TEXT_ANTI_TO_TCHAR(STRING) (NDSCommonLibs::Wide_To_Ascii (STRING).char_rep ())
//
# define TEXT_ALWAYS_UTF8(STRING) (NDSCommonLibs::Ascii_To_Utf8 (STRING).char_rep ())
# define TEXT_CHAR_TO_UTF8(STRING) (NDSCommonLibs::Ascii_To_Utf8 (STRING).char_rep ())
# define TEXT_WCHAR_TO_UTF8(STRING) (NDSCommonLibs::Wide_To_Ascii (CP_UTF8, STRING).char_rep ())
# define TEXT_UTF8_TO_CHAR(STRING) (NDSCommonLibs::Utf8_To_Ascii (STRING).char_rep ())
# define TEXT_UTF8_TO_WCHAR(STRING) (NDSCommonLibs::Ascii_To_Wide (CP_UTF8, STRING).wchar_rep ())
# define TEXT_UTF8_TO_TCHAR(STRING) (NDSCommonLibs::Utf8_To_Ascii (STRING).char_rep ())
#endif
//end

namespace NDSCommonLibs
{

class Wide_To_Ascii
{
public:
	/// Ctor must take a wchar string.
	explicit Wide_To_Ascii (const wchar_t *s);
	explicit Wide_To_Ascii(UINT cp, const wchar_t *s);

	/// Dtor will free up the memory.
	~Wide_To_Ascii (void);

	/// Return the internal char* representation.
	char *char_rep (void);

	char *detach_char_rep(void);

	/// Converts an wchar_t string to ascii and returns a new string.
	char *convert (const wchar_t *wstr);

private:
	// code page
	UINT cp_;
	/// Internal pointer to the converted string.
	char *s_;

	/// Disallow these operation.
	Wide_To_Ascii (void);
	Wide_To_Ascii (Wide_To_Ascii &);
	Wide_To_Ascii& operator= (Wide_To_Ascii &);
};

class Ascii_To_Wide
{
public:
	/// Ctor must take a wchar string.
	explicit Ascii_To_Wide (const char *s);
	explicit Ascii_To_Wide(UINT cp, const char *s);

	/// Dtor will free up the memory.
	~Ascii_To_Wide (void);

	/// Return the internal wchar* representation.
	wchar_t *wchar_rep (void);

	wchar_t *detach_wchar_rep(void);

	/// Converts an char string to unicode/wide and returns a new string.
	wchar_t *convert (const char *str);

private:
	// code page
	UINT cp_;
	/// Internal pointer to the converted string.
	wchar_t *s_;

	/// Disallow these operation.
	Ascii_To_Wide (void);
	Ascii_To_Wide (Ascii_To_Wide &);
	Ascii_To_Wide operator= (Ascii_To_Wide &);
};

class Ascii_To_Utf8
{
public:
	/// Ctor must take a wchar string.
	explicit Ascii_To_Utf8(const char *s);

	/// Dtor will free up the memory.
	~Ascii_To_Utf8(void);

	/// Return the internal char* representation.
	char *char_rep(void);

	char *detach_char_rep(void);

	/// Converts an char string to unicode/wide and returns a new string.
	char *convert(const char *str);

private:
	// code page
	UINT cp_;
	/// Internal pointer to the converted string.
	char *s_;

	/// Disallow these operation.
	Ascii_To_Utf8(void);
	Ascii_To_Utf8(Ascii_To_Utf8 &);
	Ascii_To_Utf8 operator= (Ascii_To_Utf8 &);
};

class Utf8_To_Ascii
{
public:
	/// Ctor must take a wchar string.
	explicit Utf8_To_Ascii(const char *s);

	/// Dtor will free up the memory.
	~Utf8_To_Ascii(void);

	/// Return the internal char* representation.
	char *char_rep(void);

	char *detach_char_rep(void);

	/// Converts an char string to unicode/wide and returns a new string.
	char *convert(const char *str);

private:
	// code page
	UINT cp_;
	/// Internal pointer to the converted string.
	char *s_;

	/// Disallow these operation.
	Utf8_To_Ascii(void);
	Utf8_To_Ascii(Utf8_To_Ascii &);
	Utf8_To_Ascii operator= (Utf8_To_Ascii &);
};


inline Wide_To_Ascii::~Wide_To_Ascii (void)
{
	delete [] this->s_;
}

inline char * Wide_To_Ascii::char_rep (void)
{
	//setlocale(LC_ALL, "chs");
	return this->s_;
}

inline char * Wide_To_Ascii::detach_char_rep(void)
{
	char *detach_s_ = this->s_;
	this->s_ = 0;
	return detach_s_;
}

inline char *Wide_To_Ascii::convert (const wchar_t *wstr)
{
	// Short circuit null pointer case
	if (wstr == 0)
		return 0;

	//UINT cp = GetACP ();
	int len = ::WideCharToMultiByte (cp_/*cp*/,
		0,
		wstr,
		-1,
		0,
		0,
		0,
		0);


	char *str = new char[len];

	::WideCharToMultiByte (cp_/*cp*/, 0, wstr, -1, str, len, 0, 0);

	return str;
}

inline Wide_To_Ascii::Wide_To_Ascii (const wchar_t *s)
	:cp_(GetACP())
	, s_(Wide_To_Ascii::convert(s))
{
}

inline Wide_To_Ascii::Wide_To_Ascii (UINT cp, const wchar_t *s)
	: cp_(cp)
	, s_(Wide_To_Ascii::convert(s))
{
}

inline
Ascii_To_Wide::~Ascii_To_Wide (void)
{
	delete [] this->s_;
}

inline wchar_t * Ascii_To_Wide::wchar_rep (void)
{
	return this->s_;
}

inline wchar_t * Ascii_To_Wide::detach_wchar_rep(void)
{
	wchar_t *detach_s_ = this->s_;
	this->s_ = 0;
	return detach_s_;
}

inline wchar_t * Ascii_To_Wide::convert (const char *str)
{
	// Short circuit null pointer case
	if (str == 0)
		return 0;
	
	//UINT cp = GetACP ();
	int len = ::MultiByteToWideChar (cp_/*cp*/, 0, str, -1, 0, 0);


	wchar_t *wstr = new wchar_t[len];
	::MultiByteToWideChar (cp_/*cp*/, 0, str, -1, wstr, len);
	return wstr;
}

inline Ascii_To_Wide::Ascii_To_Wide (const char *s)
	: cp_(GetACP())
	, s_(Ascii_To_Wide::convert(s))
{
}

inline Ascii_To_Wide::Ascii_To_Wide(UINT cp, const char *s)
	: cp_(cp)
	, s_(Ascii_To_Wide::convert(s))
{
}

inline
Ascii_To_Utf8::~Ascii_To_Utf8(void)
{
	delete[] this->s_;
}

inline char * Ascii_To_Utf8::char_rep(void)
{
	return this->s_;
}

inline char * Ascii_To_Utf8::detach_char_rep(void)
{
	char *detach_s_ = this->s_;
	this->s_ = 0;
	return detach_s_;
}

inline char * Ascii_To_Utf8::convert(const char *str)
{
	// Short circuit null pointer case
	if (str == 0)
		return 0;

	return Wide_To_Ascii(cp_, Ascii_To_Wide(str).wchar_rep()).detach_char_rep();
}

inline Ascii_To_Utf8::Ascii_To_Utf8(const char *s)
	: cp_(CP_UTF8)
	, s_(Ascii_To_Utf8::convert(s))
{
}

inline
Utf8_To_Ascii::~Utf8_To_Ascii(void)
{
	delete[] this->s_;
}

inline char * Utf8_To_Ascii::char_rep(void)
{
	return this->s_;
}

inline char * Utf8_To_Ascii::detach_char_rep(void)
{
	char *detach_s_ = this->s_;
	this->s_ = 0;
	return detach_s_;
}

inline char * Utf8_To_Ascii::convert(const char *str)
{
	// Short circuit null pointer case
	if (str == 0)
		return 0;

	return Wide_To_Ascii(Ascii_To_Wide(cp_, str).wchar_rep()).detach_char_rep();
}

inline Utf8_To_Ascii::Utf8_To_Ascii(const char *s)
	: cp_(CP_UTF8)
	, s_(Utf8_To_Ascii::convert(s))
{
}

inline void InitLocal()
{
	char   scp[16]; 
	UINT   cp   =   GetACP(); 
	sprintf_s(scp, ".%d ",cp); 
	setlocale(LC_ALL,   scp   );
}

}