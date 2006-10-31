#ifndef CBEAR_BERLIOS_DE_RANGE_DEQUE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_DEQUE_HPP_INCLUDED

#include <deque>
#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class T>
class deque: public ::std::deque<T>
{
private:

	typedef ::std::deque<T> internal_t;

public:

	typedef typename internal_t::iterator iterator;
	typedef typename internal_t::const_iterator const_iterator;

	typedef iterator_range<iterator> iterator_range_t;
	typedef iterator_range<const_iterator> const_iterator_range_t; 

	template<class stream_t>
	void write(stream_t &stream) const
	{
		typedef typename stream_t::value_type char_t;
		stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "{");
		{
			const_iterator_range_t r(*this);
			if(!r.empty())
			{
				for(;;)
				{
					stream << r.front();
					++r.begin();
					if(r.empty())
					{
						break;
					}
					stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, ", ");
				}
			}
		}
		stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "}");
	}
};

}
}

#endif
