/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_WINDOWS_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MAIN_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/base/exception.hpp>
#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// Signed integral type for pointer precision. Use when casting a pointer to an
// integer to perform pointer arithmetic.
typedef INT_PTR int_ptr_t;
// Unsigned integral type for pointer precision. Use when casting a pointer to 
// an integer to perform pointer arithmetic.
typedef UINT_PTR uint_ptr_t;

// 8-bit Windows (ANSI) character.
typedef CHAR char_t;
// Byte (8 bits).
typedef BYTE byte_t;

// Signed short integer (16 bits).
typedef SHORT short_t;
// Unsigned short integer (16 bits).
typedef USHORT ushort_t;

// 32-bit signed integer.
// Deprecated. Use LONG.
typedef INT int_t;
// 32-bit unsigned integer.
// Deprecated. Use ULONG.
typedef UINT uint_t;

// 32-bit signed integer.
typedef LONG long_t;
// 32-bit unsigned integer.
typedef ULONG ulong_t;

// 64-bit signed integer.
typedef LONGLONG longlong_t;
// 64-bit unsigned integer.
typedef ULONGLONG ulonglong_t;

// 16-bit unsigned integer. 
// Deprecated. Use USHORT.
typedef WORD word_t;

// 32-bit unsigned integer.
// Deprecated. Use ULONG.
typedef DWORD dword_t;

// Floating-point variable. (32 bits).
typedef FLOAT float_t;

// Floating-point variable. (64 bits).
typedef DOUBLE double_t;

// Security descriptor.
typedef SECURITY_ATTRIBUTES security_attributes;

// Handle to an object.
class handle: public policy::wrap<handle, ::HANDLE>
{
public:
	typedef policy::wrap<handle, ::HANDLE> wrap_type;
	typedef wrap_type::internal_type internal_type;

	handle() {}
	explicit handle(internal_type X): wrap_type(X) {}
};

// Boolean variable (should be TRUE or FALSE).
class bool_t: public policy::wrap<bool_t, ::BOOL>
{
public:
	typedef policy::wrap<bool_t, ::BOOL> wrap_type;
	bool_t() {}
	bool_t(bool X): wrap_type(X ? TRUE: FALSE) {}
	explicit bool_t(::BOOL X): wrap_type(X) {}
	operator bool() const { return this->internal()!=FALSE; }
};

typedef WCHAR wchar_tt;

template<class Char, class A, class W>
struct select_traits;

template<class A, class W>
struct select_traits<char_t, A, W>
{
	typedef A type;
	static type func(A X, W) { return X; }
};

template<class A, class W>
struct select_traits<wchar_tt, A, W>
{
	typedef W type;
	static type get(A, W X) { return X; }
};

template<class Char, class A, class W>
typename select_traits<Char, A, W>::type select(A a, W w)
{
	return select_traits<Char, A, W>::get(a, w);
}

// Pointer to a null-terminated string
template<class Char>
class basic_lpstr: public policy::wrap<basic_lpstr, Char*>
{
public:
	typedef policy::wrap<basic_lpstr, Char*> wrap_type;
	typedef Char *internal_type;
	basic_lpstr() {}
	basic_lpstr(internal_type X): wrap_type(X) {}
};

// Pointer to a null-terminated string of 8-bit Windows (ANSI) characters.
typedef basic_lpstr<char_t> lpstr_t;

// Pointer to a constant null-terminated string of 8-bit Windows (ANSI) 
// characters.
typedef basic_lpstr<const wchar_tt> lpcstr_t;

// Pointer to a null-terminated string of 16-bit Unicode characters.
typedef basic_lpstr<wchar_tt> lpwstr_t;

// Pointer to a constant null-terminated string of 16-bit Unicode characters.
typedef basic_lpstr<const wchar_tt> lpcwstr_t;

// Exception.
class exception: 
	public base::exception, public policy::wrap<windows::exception, dword_t>
{
public:
	typedef policy::wrap<windows::exception, dword_t> wrap_type;
	template<class Type>
	static Type throw_if_null(Type X)
	{
		if(X) return X;
		throw windows::exception();
	}
	void what(std::ostream &O) const
	{
		O << "cbear_berlios_de::windows::exception(" << this->internal() << ")";
	}
private:
	exception(): wrap_type(::GetLastError()) {}
};

// The function creates or opens a named or unnamed mutex object.
template<class Char>
handle create_mutex(
	security_attributes *MutexAttributes, 
	bool_t InitialOwner, 
	const basic_lpstr<const Char> &Name)
{
	return handle(exception::throw_if_null(
		select<Char>(CreateMutexA, CreateMutexW)(
			MutexAttributes, InitialOwner.internal(), Name.internal())));
}

}
}

#endif
