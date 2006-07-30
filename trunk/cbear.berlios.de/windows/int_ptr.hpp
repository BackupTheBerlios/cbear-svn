#ifndef CBEAR_BERLIOS_DE_WINDOWS_INT_PTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_INT_PTR_HPP_INCLUDED

#include <cbear.berlios.de/windows/basetsd.h>

namespace cbear_berlios_de
{
namespace windows
{

// Signed integral type for pointer precision. Use when casting a pointer to an
// integer to perform pointer arithmetic.
typedef INT_PTR int_ptr_t;

}
}

#endif
