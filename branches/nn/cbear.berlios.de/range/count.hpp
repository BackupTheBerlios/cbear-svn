#ifndef CBEAR_BERLIOS_DE_RANGE_COUNT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_COUNT_HPP_INCLUDED

#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class T>
typename traits<Container>::difference_type count(
	const Container &X, T const &V)
{ 
	return ::std::count(range::begin(X), range::end(X), V);
}

}
}

#endif
