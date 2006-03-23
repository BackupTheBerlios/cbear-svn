/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
