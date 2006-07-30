#ifndef CBEAR_BERLIOS_DE_RANGE_ARRAYZ_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ARRAYZ_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class V>
iterator_range<V *> make_arrayz_range(V *B)
{
	iterator_range<V *> R(B, B);
	if(!B) return R;
	for(; *R.end() != 0; ++R.end());
	return R;
}

}
}

#endif
