#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_WRITE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_WRITE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

// POD.
template<class S, class T>
typename boost::enable_if<boost::is_pod<T> >::type write(S &s, T const &t)
{
	// char const *B = &reinterpret_cast<char const &>(t);
	// s.push_back_range(range::make_iterator_range(B, B + sizeof(T)));
	s.push_back_pod(t);
}

// Complex structures.
template<class S, class T>
typename boost::enable_if<boost::is_class<T> >::type write(S &s, T const &t)
{
	t.binary_write(s);
}

// An array.
template<class S, class T, std::size_t Size>
void write(S &s, T const (&t)[Size])
{ 
	for(range::iterator_range<T const *> R(t); !R.empty(); ++R.begin())
	{
		binary::write(s, R.front());
	}
}

}
}
}

#endif