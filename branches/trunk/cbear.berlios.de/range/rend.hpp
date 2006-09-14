#ifndef CBEAR_BERLIOS_DE_RANGE_REND_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_REND_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename reverse_iterator<Container>::type rend(Container &X) 
{ 
	return traits<Container>::rend(X); 
}

template<class Container>
typename reverse_iterator<const Container>::type rend(const Container &X) 
{ 
	return traits<const Container>::rend(X);
}

}
}

#endif
