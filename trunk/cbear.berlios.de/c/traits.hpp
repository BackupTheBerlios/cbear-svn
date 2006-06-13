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
#ifndef CBEAR_BERLIOS_DE_C_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_TRAITS_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace c
{

template<class T>
class class_traits
{
public:

	// pointer or value.
	typedef typename T::c_in_t in_t;
	// pointer.
	typedef typename T::c_out_t out_t;
	// pointer.
	typedef typename T::c_in_out_t in_out_t;
	
	static in_t in(const T &X) throw()
	{ 
		return X.c_in(); 
	}
	static out_t out(T &X) throw()
	{ 
		return X.c_out(); 
	}
	static in_out_t in_out(T &X) throw()
	{ 
		return X.c_in_out(T); 
	}

	static const T &cpp_in(const in_t &X) throw()
	{ 
		return T::cpp_in(X); 
	}
	static T &cpp_out(out_t X) throw()
	{ 
		return T::cpp_out(X); 
	}
	static T &cpp_in_out(in_out_t X) throw()
	{ 
		return T::cpp_in_out(X); 
	}
};

template<class T>
class value_traits
{
public:

	typedef T in_t;
	typedef T *out_t;
	typedef T *in_out_t;

	static in_t in(const T &X)
	{
		return X;
	}
	static out_t out(T &X)
	{
		X = T();
		return &X;
	}
	static in_out_t in_out(T &X)
	{
		return &X;
	}

	static const T &cpp_in(const in_t &X)
	{
		return X;
	}
	static T &cpp_out(out_t X) 
	{ 
		return *X; 
	}
	static T &cpp_in_out(in_out_t X)
	{ 
		return *X; 
	}
};

template<class T>
class traits: public meta::if_< 
	::boost::is_class<T>, class_traits<T>, value_traits<T> >::type
{
};

}
}

#endif
