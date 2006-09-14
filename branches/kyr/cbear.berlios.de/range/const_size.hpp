#ifndef CBEAR_BERLIOS_DE_RANGE_CONST_SIZE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_CONST_SIZE_HPP_INCLUDED

#include <boost/array.hpp>

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class T, std::size_t Size>
char (&const_size(const T (&X)[Size]))[Size];

template<class T, std::size_t Size>
char (&const_size(const boost::array<T, Size> &X))[Size];

}
}

#endif
