#ifndef CBEAR_BERLIOS_DE_RANGE_END_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_END_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename traits<Container>::iterator end(Container &X) 
{ 
	return traits<Container>::end(X); 
}

template<class Container>
typename traits<Container const>::iterator end(Container const &X)
{ 
	return traits<Container const>::end(X);
}

}
}

#endif
