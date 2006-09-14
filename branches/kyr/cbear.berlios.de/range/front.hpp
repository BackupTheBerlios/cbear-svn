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
typename reference<const Container>::type front(const Container &X) 
{ 
	return traits<const Container>::front(X); 
}

}
}

#endif
