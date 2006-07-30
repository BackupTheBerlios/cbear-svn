#ifndef CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_LESS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_LESS_HPP_INCLUDED

// std::lexicographical_compare
#include <algorithm>

#include <cbear.berlios.de/range/sub_range.hpp>

namespace cbear_berlios_de
{
namespace range
{
namespace lexicographic
{

// Calls ::std::lexicographical_compare.
// Returns true if R1 < R2, false if R1 >= R2.
template<class Range1, class Range2>
bool less(const Range1 &R1, const Range2 &R2)
{
	return ::std::lexicographical_compare(
		range::begin(R1), range::end(R1), range::begin(R2), range::end(R2));
}

}
}
}

#endif
