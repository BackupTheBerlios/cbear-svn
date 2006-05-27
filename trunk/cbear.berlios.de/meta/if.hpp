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
#ifndef CBEAR_BERLIOS_DE_META_IF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_IF_HPP_INCLUDED

namespace cbear_berlios_de
{

namespace meta
{

namespace detail
{
class no_else;
}

template<bool C, class T, class E = detail::no_else>
class if_c;

namespace detail
{

template<bool C, class T>
class if_c
{
public:

	typedef if_c o;

	template<bool C1, class T1, class E1 = no_else>
	class else_if_c: 
		public meta::if_c<C || C1, typename meta::if_c<C, T, T1>::type, E1>
	{
	};

	template<class C1, class T1, class E1 = no_else>
	class else_if: public else_if_c<C1::value, T1, E1> {};

	template<class E>
	class else_: public meta::if_c<C, T, E> {};
};

}

template<class T, class E>
class if_c<false, T, E>
{
public:
	typedef E type;
};

template<class T, class E>
class if_c<true, T, E>
{
public:
	typedef T type;
};

template<class T>
class if_c<false, T, detail::no_else>: public detail::if_c<false, T>
{
};

template<class T>
class if_c<true, T, detail::no_else>: public detail::if_c<true, T>
{
public:
	typedef T type;
};

template<class C, class T, class E = detail::no_else>
class if_: public if_c<C::value, T, E> {};

}
}

#endif
