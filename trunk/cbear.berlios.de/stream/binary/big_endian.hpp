#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED

#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

namespace detail
{

template< ::std::size_t S, class T>
class big_endian_traits
{
public:
	T value;
	typedef typename base::half<T>::type half_t;
	template<class S>
	void binary_read(S &s)
	{
		big_endian<half_t> high;
		big_endian<half_t> low;
		s >> high >> low;
		base::high(this->value) = high.value;
		base::low(this->value) = low.value;
	}
};

template<class T>
class big_endian_traits<8, T>
{
public:
	T value;
	template<class S>
	void binary_read(S &s)
	{
		s >> this->value;
	}
};

}

template<class T>
class big_endian: public detail::big_endian_traits<sizeof(T) * CHAR_BIT, T>
{
};

}
}
}

#endif
