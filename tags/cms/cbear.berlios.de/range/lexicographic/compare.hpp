#ifndef CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_COMPARE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_COMPARE_HPP_INCLUDED

#include <cbear.berlios.de/base/compare.hpp>
#include <cbear.berlios.de/range/sub_range.hpp>

namespace cbear_berlios_de
{
namespace range
{
namespace lexicographic
{

// Warning: ::std::lexicographical_compare has different functionality!
// See also lexicographic::less.
// Returns -1 if R1 < R2, 0 if R1==R2, 1 if R1 > R2.
template<class Range1, class Range2>
int compare(const Range1 &R1, const Range2 &R2)
{
	typename range::sub_range<const Range1>::type S1(R1);
	typename range::sub_range<const Range2>::type S2(R2);
	for(;;)
	{
		if(S1.empty()) return S2.empty() ? 0: -1;
		if(S2.empty()) return 1;
		if(S1.front()!=S2.front()) return S1.front() < S2.front() ? -1: 1;
		S1.begin()++;
		S2.begin()++;
	}
}

}
}
}

#endif
