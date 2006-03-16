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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_SELECT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SELECT_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{

template<class Char, class A, class W>
struct select_traits;

template<class A, class W>
struct select_traits<char_t, A, W>
{
	typedef A type;
	static type get(A X, W) { return X; }
};

template<class A, class W>
struct select_traits<wchar_t_, A, W>
{
	typedef W type;
	static type get(A, W X) { return X; }
};

template<class Char, class A, class W>
typename select_traits<Char, A, W>::type select(A a, W w)
{
	return select_traits<Char, A, W>::get(a, w);
}

}
}

#define CBEAR_BERLIOS_DE_WINDOWS_SELECT_STRING(Char, X) \
	select<Char>(X, CBEAR_BERLIOS_DE_PP_WIDEN(X))

#define CBEAR_BERLIOS_DE_WINDOWS_SELECT_FUNCTION(Char, Name) \
	select<Char>(BOOST_PP_CAT(Name, A), BOOST_PP_CAT(Name, W))

#define CBEAR_BERLIOS_DE_WINDOWS_SELECT_TYPE(Char, Name) \
	typename select_traits<Char, BOOST_PP_CAT(Name, A), BOOST_PP_CAT(Name, W)>:: \
	type

#endif
