#ifndef CBEAR_BERLIOS_DE_RANGE_POINTER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_POINTER_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct pointer 
{ 
	typedef typename traits<Container>::pointer type;
};

}
}

#endif
