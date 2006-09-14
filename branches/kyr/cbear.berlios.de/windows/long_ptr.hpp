#ifndef CBEAR_BERLIOS_DE_WINDOWS_LONG_PTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_LONG_PTR_HPP_INCLUDED

#include <cbear.berlios.de/windows/basetsd.h>

namespace cbear_berlios_de
{
namespace windows
{

// Signed long integer type for pointer precision. Use when casting a pointer to 
// an long integer to perform pointer arithmetic.
typedef LONG_PTR long_ptr_t;

}
}

#endif
