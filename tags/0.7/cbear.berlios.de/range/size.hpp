#ifndef CBEAR_BERLIOS_DE_RANGE_SIZE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_SIZE_HPP_INCLUDED

#include <cbear.berlios.de/range/size_type.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
typename traits<const Container>::size_type size(const Container &X)
{ 
	return traits<const Container>::size(X);
}

}
}

#endif
