#ifndef CBEAR_BERLIOS_DE_WINDOWS_BASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_BASE_HPP_INCLUDED

#pragma warning(push)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#include <basetsd.h>
#include <windows.h>
#include <wtypes.h>
#pragma warning(pop)

#include <cstddef>

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace windows
{

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
