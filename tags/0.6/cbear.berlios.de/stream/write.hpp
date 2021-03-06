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
#ifndef CBEAR_BERLIOS_DE_STREAM_WRITE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_WRITE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/size.hpp>
#include <cbear.berlios.de/select/traits.hpp>
#include <cbear.berlios.de/meta/if.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace detail
{

class unknown_traits 
{
};

class class_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t) { t.write(s); }
};

class bool_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		typedef typename S::value_type value_type;
		if(t)
			s.push_back_range(CBEAR_BERLIOS_DE_SELECT_STRING(value_type, "true"));
		else
			s.push_back_range(CBEAR_BERLIOS_DE_SELECT_STRING(value_type, "false"));
	}
};

class char_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		s.push_back_range(range::make_iterator_range(&t, &t + 1));
	}
};

class integer_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		base::out<10>(t).write(s);
	};
};

class array_traits
{
public:
	template<class S, class C, std::size_t Size>
	static void write(S &s, const C (&t)[Size])
	{
		BOOST_STATIC_ASSERT((boost::is_same<typename S::value_type, C>::value));
		s.push_back_range(t);
	}
};

template<class S, class T>
class traits: public 
	meta::if_<
		boost::is_class<T>, class_traits>::
	template else_if<
		boost::is_same<T, typename S::value_type>, char_traits>::o::
	template else_if<
		boost::is_same<T, bool>, bool_traits>::o::
	template else_if<
		boost::is_integral<T>, integer_traits>::o::
	template else_if<
		boost::is_array<T>, array_traits>::
	template else_<
		unknown_traits>::type
{
};

}

template<class S, class T>
void write(S &s, const T &t)
{
	detail::traits<S, T>::write(s, t);
}

}
}

#endif
