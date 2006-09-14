#ifndef CBEAR_BERLIOS_DE_RANGE_AT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_AT_HPP_INCLUDED

#include <cbear.berlios.de/range/reference.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class SizeType>
typename reference<const Container>::type at(const Container &X, SizeType I) 
{ 
	return traits<const Container>::at(X, I);
}

}
}

#endif
