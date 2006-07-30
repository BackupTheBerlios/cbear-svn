#ifndef CBEAR_BERLIOS_DE_RANGE_EMPTY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_EMPTY_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
bool empty(const Container &X) 
{ 
	return traits<const Container>::empty(X); 
}

}
}

#endif
