#ifndef CBEAR_BERLIOS_DE_RANGE_BEGIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_BEGIN_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename traits<Container>::iterator begin(Container &X) 
{ 
	return traits<Container>::begin(X); 
}

template<class Container>
typename traits<const Container>::iterator begin(const Container &X) 
{ 
	return traits<const Container>::begin(X);
}

}
}

#endif
