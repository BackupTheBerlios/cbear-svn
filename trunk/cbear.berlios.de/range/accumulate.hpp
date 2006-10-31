#ifndef CBEAR_BERLIOS_DE_RANGE_ACCUMULATE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ACCUMULATE_HPP_INCLUDED

#include <numeric>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class T>
T accumulate(Container const &X, T const &V)
{ 
	return ::std::accumulate(range::begin(X), range::end(X), V);
}

template<class Container>
typename traits<Container const>::value_type accumulate(Container const &X)
{ 

	return ::std::accumulate(
		range::begin(X), range::end(X), traits<Container const>::value_type());
}

}
}

#endif
