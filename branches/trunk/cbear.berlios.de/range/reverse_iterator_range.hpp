#ifndef CBEAR_BERLIOS_DE_RANGE_REVERSE_ITERATOR_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_REVERSE_ITERATOR_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Iterator>
struct reverse_iterator_range
{
	typedef iterator_range< ::std::reverse_iterator<Iterator> > type;
};

template<class Iterator>
typename reverse_iterator_range<Iterator>::type make_reverse_iterator_range(
	const Iterator &B, const Iterator &E)
{
	typedef ::std::reverse_iterator<Iterator> reverse_iterator;
	return reverse_iterator_range<Iterator>::type(
		reverse_iterator(E), reverse_iterator(B));
}

}
}

#endif
