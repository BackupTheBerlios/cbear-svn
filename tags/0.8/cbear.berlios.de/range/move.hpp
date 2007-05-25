#ifndef CBEAR_BERLIOS_DE_RANGE_MOVE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_MOVE_HPP_INCLUDED

#include <cbear.berlios.de/move/main.hpp>
#include <cbear.berlios.de/range/sub_range.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class OutputIterator>
OutputIterator move(Container const &From, OutputIterator To) 
{ 
	typedef typename sub_range<Container>::type iterator_range_t;
	for(iterator_range_t R(From); !R.empty(); ++R.begin(), ++To)
	{
		move::assign(*To, R.front());
	}
	return To;
}

}
}

#endif
