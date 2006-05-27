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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_BASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_BASE_HPP_INCLUDED

#pragma warning(push)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#include <windows.h>
#include <wtypes.h>
#pragma warning(pop)

#include <cstddef>

#include <cbear.berlios.de/range/iterator_range.hpp>

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
// WTypes.h
typedef DOUBLE double_t;

// 16-bit Unicode character.
typedef WCHAR wchar_t_;

typedef LRESULT lresult_t;

static const std::size_t max_path = MAX_PATH;

typedef SYSTEMTIME systemtime_t;

typedef range::iterator_range<byte *> byte_range;

template<class T>
byte_range pod_range(T &X)
{
	return byte_range((byte*)&X, (byte*)(&X + 1));
}

}
}

#endif
