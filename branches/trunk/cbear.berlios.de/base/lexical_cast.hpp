#ifndef CBEAR_BERLIOS_DE_BASE_LEXICAL_CAST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_LEXICAL_CAST_HPP_INCLUDED

// boost::mpl::bool_
#include <boost/mpl/bool.hpp>

#include <cbear.berlios.de/stream/write.hpp>

namespace cbear_berlios_de
{
namespace base
{

	/*
namespace detail
{

template<class T>
class lexical_cast_traits;

template<class Char>
class lexical_cast_traits< ::std::basic_string<Char> >
{
public:
	template<class S>
	static ::std::basic_string<Char> do_(const S &s)
	{
		::std::basic_ostringstream<Char> Stream;
		Stream << s;
		return Stream.str();
	}
};

}

template<class T, class S>
T lexical_cast(const S &s)
{
	return detail::lexical_cast_traits<T>::do_(s);
}
*/

template<class Stream, class T>
Stream to_stream(const T &t)
{
	Stream s;
	s << t;
	return s;
}

}
}

#endif
