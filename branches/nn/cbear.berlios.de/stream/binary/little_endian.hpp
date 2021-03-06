#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_LITTLE_ENDIAN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_LITTLE_ENDIAN_HPP_INCLUDED

#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class little_endian_t
{
public:

	template<class S>
	static void pop_front_pod(S &s, ::boost::uint8_t &t)
	{
		char *const begin = cast::traits<char *>::reinterpret(&t);
		s.pop_front_range(S::range_type(begin, begin + 1));
	}

	template<class S>
	static void pop_front_pod(S &s, float &t)
	{
		typedef typename base::uint_t<sizeof(float) * CHAR_BIT>::type uint_t;
		pop_front_pod(s, cast::traits<uint_t &>::reinterpret(t));
	}

	template<class S>
	static void push_back_pod(S &s, ::boost::uint8_t const &t)
	{
		char const *const begin = cast::traits<char const *>::reinterpret(&t);
		s.push_back_range(S::const_range_type(begin, begin + 1));
	}

	template<class S, class T>
	static void pop_front_pod(S &s, T &t)
	{
		pop_front_pod(s, base::low(t));
		pop_front_pod(s, base::high(t));
	}

	template<class S, class T>
	static void push_back_pod(S &s, T const &t)
	{
		push_back_pod(s, base::low(t));
		push_back_pod(s, base::high(t));
	}
};

}
}
}

#endif
