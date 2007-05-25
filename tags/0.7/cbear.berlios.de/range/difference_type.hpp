#ifndef CBEAR_BERLIOS_DE_RANGE_DIFFERENCE_TYPE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_DIFFERENCE_TYPE_HPP_INCLUDED

#include <cbear.berlios.de/range/difference_type.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct difference_type 
{ 
	typedef typename traits<Container>::difference_type type;
};

}
}

#endif
