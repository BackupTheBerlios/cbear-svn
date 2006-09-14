#ifndef CBEAR_BERLIOS_DE_RANGE_BACK_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_BACK_HPP_INCLUDED

#include <cbear.berlios.de/range/reference.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename reference<Container>::type back(Container &X) 
{ 
	return traits<Container>::back(X); 
}

template<class Container>
typename reference<const Container>::type back(const Container &X) 
{ 
	return traits<const Container>::back(X);
}

}
}

#endif
