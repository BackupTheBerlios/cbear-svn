#ifndef CBEAR_BERLIOS_DE_C_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_TRAITS_HPP_INCLUDED

#include <boost/type_traits/is_class.hpp>

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
