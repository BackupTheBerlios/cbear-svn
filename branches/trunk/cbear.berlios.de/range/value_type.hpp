#ifndef CBEAR_BERLIOS_DE_RANGE_VALUE_TYPE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_VALUE_TYPE_HPP_INCLUDED

#include <cbear.berlios.de/range/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container>
struct value_type { typedef typename traits<Container>::value_type type; };

}
}

#endif
