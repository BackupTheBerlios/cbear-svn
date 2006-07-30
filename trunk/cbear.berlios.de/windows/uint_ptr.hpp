#ifndef CBEAR_BERLIOS_DE_WINDOWS_UINT_PTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_UINT_PTR_HPP_INCLUDED

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

// Unsigned integral type for pointer precision. Use when casting a pointer to 
// an integer to perform pointer arithmetic.
typedef UINT_PTR uint_ptr_t;

}
}

#endif
