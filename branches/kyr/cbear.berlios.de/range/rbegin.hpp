#ifndef CBEAR_BERLIOS_DE_RANGE_RBEGIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_RBEGIN_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename reverse_iterator<Container>::type rbegin(Container &X) 
{ 
	return traits<Container>::rbegin(X); 
}

template<class Container>
typename reverse_iterator<const Container>::type rbegin(const Container &X) 
{ 
	return traits<const Container>::rbegin(X);
}

}
}

#endif
