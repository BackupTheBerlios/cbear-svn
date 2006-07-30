#ifndef CBEAR_BERLIOS_DE_RANGE_SIZE_TYPE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_SIZE_TYPE_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct size_type { typedef typename traits<Container>::size_type type; };

}
}

#endif
