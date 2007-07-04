#ifndef CBEAR_BERLIOS_DE_RANGE_REFERENCE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_REFERENCE_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
class reference 
{ 
public:
	typedef typename traits<Container>::reference type; 
};

}
}

#endif
