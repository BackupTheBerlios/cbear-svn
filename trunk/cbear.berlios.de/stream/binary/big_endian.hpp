#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED

#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

template<class T>
class big_endian;

namespace detail
{

/*
template<class T, class S>
T big_endian_binary_read(S &s)
{
	typedef typename base::half<T>::type half_t;
	big_endian<half_t> high;
	big_endian<half_t> low;
	s >> high >> low;
	return base::compose(high.value, low.value);
}
*/

template< ::std::size_t S, class T>
class big_endian_traits
{
public:
	T value;
	template<class S>
	void binary_read(S &s)
	{
		typedef typename base::half<T>::type half_t;
		big_endian<half_t> high;
		big_endian<half_t> low;
		s >> high >> low;
		this->value = base::compose(high.value, low.value);
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

template<class T>
class big_endian_float
{
public:
	T value;
	template<class S>
	void binary_read(S &s)
	{
		typedef typename base::uint_t<sizeof(T) * CHAR_BIT>::type uint_t;
		big_endian<uint_t> v;
		s >> v;
		this->value = cast::traits<T const &>::reinterpret(v.value);
	}
};

}

template<class T>
class big_endian: public detail::big_endian_traits<sizeof(T) * CHAR_BIT, T>
{
};

template<>
class big_endian<float>: public detail::big_endian_float<float>
{
};

template<>
class big_endian<double>: public detail::big_endian_float<double>
{
};

}
}
}

#endif
