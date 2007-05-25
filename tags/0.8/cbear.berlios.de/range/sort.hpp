#ifndef CBEAR_BERLIOS_DE_RANGE_SORT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_SORT_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
void sort(Container &X)
{
	typedef traits<Container> traits_t;
	return ::std::sort(traits_t::begin(X), traits_t::end(X));
}

template<class Container, class Less>
void sort(Container &X, Less L)
{ 
	typedef traits<Container> traits_t;
	return ::std::sort(traits_t::begin(X), traits_t::end(X), L);
}

}
}

#endif
