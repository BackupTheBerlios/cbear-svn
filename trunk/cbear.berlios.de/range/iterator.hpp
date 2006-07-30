#ifndef CBEAR_BERLIOS_DE_RANGE_ITERATOR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ITERATOR_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct iterator 
{ 
	typedef typename traits<Container>::iterator type; 
};

}
}

#endif
