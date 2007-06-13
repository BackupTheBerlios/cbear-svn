#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_BIG_ENDIAN_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

/*
template<class T>
class big_endian;

namespace detail
{


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
*/

class big_endian_t
{
public:

	template<class S>
	static void pop_front_pod(S &s, ::boost::uint8_t &t)
	{
		char *const begin = cast::traits<char *>::reinterpret(&t);
		s.pop_front_range(S::range_type(begin, begin + 1));
	}

	template<class S>
	static void push_back_pod(S &s, ::boost::uint8_t const &t)
	{
		char const *const begin = cast::traits<char const *>::reinterpret(&t);
		s.push_back_range(S::const_range_type(begin, begin + 1));
	}

	template<class S>
	static void pop_front_pod(S &s, float &t)
	{
		typedef typename base::uint_t<sizeof(float) * CHAR_BIT>::type uint_t;
		pop_front_pod(s, cast::traits<uint_t &>::reinterpret(t));
	}

	template<class S>
	static void push_back_pod(S &s, float const &t)
	{
		push_back_pod(s, cast::traits<float_uint_t const &>::reinterpret(t));
	}

	template<class S>
	static void pop_front_pod(S &s, double &t)
	{
		typedef typename base::uint_t<sizeof(double) * CHAR_BIT>::type uint_t;
		pop_front_pod(s, cast::traits<uint_t &>::reinterpret(t));
	}

	template<class S, class T>
	static void pop_front_pod(S &s, T &t)
	{
		s.pop_front_pod(base::high(t));
		s.pop_front_pod(base::low(t));
	}

	template<class S, class T>
	static void push_back_pod(S &s, T const &t)
	{
		push_back_pod(s, base::high(t));
		push_back_pod(s, base::low(t));
	}
};

}
}
}

#endif
