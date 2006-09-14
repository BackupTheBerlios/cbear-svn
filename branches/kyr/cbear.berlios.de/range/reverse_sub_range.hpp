#ifndef CBEAR_BERLIOS_DE_RANGE_REVERSE_SUB_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_REVERSE_SUB_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/range/reverse_iterator_range.hpp>
#include <cbear.berlios.de/range/rbegin.hpp>
#include <cbear.berlios.de/range/rend.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Range>
struct reverse_sub_range: reverse_iterator_range<typename iterator<Range>::type>
{
};

template<class Range>
typename reverse_sub_range<Range>::type make_reverse_sub_range(
	Range &X)
{
	return reverse_sub_range<Range>::type(rbegin(X), rend(X));
}

template<class Range>
typename reverse_sub_range<const Range>::type make_reverse_sub_range(
	const Range &X)
{
	return reverse_sub_range<const Range>::type(rbegin(X), rend(X));
}

}
}

#endif
