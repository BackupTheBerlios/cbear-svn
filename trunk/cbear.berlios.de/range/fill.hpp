#ifndef CBEAR_BERLIOS_DE_RANGE_FILL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_FILL_HPP_INCLUDED

#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class T>
void fill(Container &X, const T &Value) 
{ 
	std::fill(range::begin(X), range::end(X), Value);
}

}
}

#endif
