#ifndef CBEAR_BERLIOS_DE_RANGE_MOVE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_MOVE_HPP_INCLUDED

#include <cbear.berlios.de/move/main.hpp>
#include <cbear.berlios.de/range/sub_range.hpp>

namespace cbear_berlios_de
{
namespace range
{

namespace detail
{

class move_copy_t
{
public:

	template<class Container, class OutputIterator>
	static OutputIterator do_(Container &From, OutputIterator To)
	{
		return ::std::copy(range::begin(From), range::end(From), To);
	}

};

class move_common_t
{
public:

	template<class Container, class OutputIterator>
	static OutputIterator do_(Container &From, OutputIterator To)
	{
		typedef typename sub_range<Container>::type iterator_range_t;
		for(iterator_range_t R(From); !R.empty(); ++R.begin(), ++To)
		{
			::cbear_berlios_de::move::assign(*To, R.front());
		}
		return To;
	}

};

template<class Container, class OutputIterator>
class move_t: 
	public meta::if_c< 
		!::boost::is_class<typename traits<Container>::value_type>::value,
		move_copy_t,
		move_common_t>::type
{
};

}

template<class Container, class OutputIterator>
iterator_range<OutputIterator> move(Container const &From, OutputIterator To)
{ 
	return iterator_range<OutputIterator>(
		To, detail::move_t<Container const, OutputIterator>::do_(From, To));
}

template<class Container, class OutputIterator>
iterator_range<OutputIterator> move(Container &From, OutputIterator To)
{
	return iterator_range<OutputIterator>(
		To, detail::move_t<Container, OutputIterator>::do_(From, To));
}

}
}

#endif
