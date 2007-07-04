#ifndef CBEAR_BERLIOS_DE_RANGE_FRONT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_FRONT_HPP_INCLUDED

#include <cbear.berlios.de/range/reference.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename reference<Container>::type front(Container &X) 
{ 
	return traits<Container>::front(X); 
}

template<class Container>
typename reference<Container const>::type front(Container const &X)
{ 
	return traits<Container const>::front(X); 
}

}
}

#endif
