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

namespace cbear_berlios_de
{
namespace stream
{

// Complex structures.
template<class S, class T>
typename boost::enable_if<boost::is_class<T> >::type 
write(S &s, const T &t)
{
	t.write(s);
}

// An array of symbols.
template<class S, class Char, std::size_t Size>
void write(
	S &s, 
	const Char (&t)[Size], 
	typename boost::enable_if<boost::is_same<
		typename S::value_type, Char> >::type * = 0)
{ 
	s.push_back_range(t); 
}

// One symbol.
template<class S>
void write(S &s, const typename S::value_type &x)
{
	s.push_back_range(range::make_iterator_range(&x, &x + 1));
}

// Boolean.
template<class S>
void write(S &s, const bool &x)
{
	typedef typename S::value_type value_type;
	if(x)
		s.push_back_range(CBEAR_BERLIOS_DE_BASE_SELECT(value_type, "true"));
	else
		s.push_back_range(CBEAR_BERLIOS_DE_BASE_SELECT(value_type, "false"));
}

// Integers.
template<class S, class I>
typename boost::enable_if<boost::is_integral<I> >::type
write(S &s, const I &i)
{
	base::out<10>(i).write(s);
}

}
}

#endif