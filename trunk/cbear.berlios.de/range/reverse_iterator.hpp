#ifndef CBEAR_BERLIOS_DE_RANGE_REVERSE_ITERATOR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_REVERSE_ITERATOR_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct reverese_iterator 
{ 
	typedef typename traits<Container>::reverese_iterator type;
};

}
}

#endif
