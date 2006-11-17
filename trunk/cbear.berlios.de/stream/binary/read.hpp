#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_READ_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_READ_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

// POD.
template<class S, class T>
typename boost::enable_if<boost::is_pod<T> >::type read(S &s, T &t)
{
	// char *B = &reinterpret_cast<char &>(t);
	// s.pop_front_range(range::make_iterator_range(B, B + sizeof(T)));
	s.pop_front_pod(t);
}

// Complex structures.
template<class S, class T>
typename boost::enable_if<boost::is_class<T> >::type read(S &s, T &t)
{
	t.binary_read(s);
}

// An array.
template<class S, class T, std::size_t Size>
void read(S &s, T (&t)[Size])
{ 
	for(range::iterator_range<T *> R(t); !R.empty(); ++R.begin())
		binary::read(s, R.front());
}

}
}
}

#endif