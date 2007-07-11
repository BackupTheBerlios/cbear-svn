#ifndef CBEAR_BERLIOS_DE_RANGE_SUB_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_SUB_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Range>
struct sub_range 
{ 
	typedef iterator_range<typename iterator<Range>::type> type; 
};

template<class Range>
typename sub_range<Range>::type make_sub_range(Range &R)
{
	return sub_range<Range>::type(R);
}

template<class Range>
typename sub_range<Range const>::type make_sub_range(Range const &R)
{
	return sub_range<Range const>::type(R);
}

}
}

#endif
