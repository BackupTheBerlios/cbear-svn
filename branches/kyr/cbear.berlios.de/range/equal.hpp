#ifndef CBEAR_BERLIOS_DE_RANGE_EQUAL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_EQUAL_HPP_INCLUDED

// std::equal
#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>
#include <cbear.berlios.de/range/size.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Range1, class Range2>
bool equal(const Range1 &A, const Range2 &B)
{
	return 
		range::size(A)==range::size(B) && 
		::std::equal(
			range::begin(A), range::end(A), range::begin(B));
}

template<class Range1, class Range2, class Pred>
bool equal(const Range1 &A, const Range2 &B, Pred P)
{
	return 
		range::size(A)==range::size(B) && 
		::std::equal(
			range::begin(A), range::end(A), range::begin(B), P);
}

}
}

#endif
