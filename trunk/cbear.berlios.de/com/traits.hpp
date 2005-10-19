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
#ifndef CBEAR_BERLIOS_DE_COM_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_TRAITS_HPP_INCLUDED

#include <cbear.berlios.de/base/undefined.hpp>
#include <cbear.berlios.de/policy/main.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::mpl::if_
#include <boost/mpl/if.hpp>
// boost::is_class
#include <boost/type_traits/is_class.hpp>
// boost::is_enum
#include <boost/type_traits/is_enum.hpp>

namespace cbear_berlios_de
{
namespace com
{

template<class Type>
struct traits;

enum io_type
{
	in = 1,
	out = 2,
	in_out = in|out,
};

typedef ::VARTYPE vartype_t;

template<class Type>
struct class_traits
{
	typedef Type type;
	typedef typename type::internal_policy internal_policy;
	typedef typename internal_policy::type internal_type;

	BOOST_STATIC_ASSERT(sizeof(type)==sizeof(internal_type));

	static const vartype_t vt = type::vt;

	template<io_type Io>
	struct io_traits;

	template<>
	struct io_traits<in>
	{
		typedef internal_type internal_result;
		typedef const type &wrap_result;

		static internal_result internal(wrap_result X) 
		{
			return X.internal();
		}
		static wrap_result wrap(internal_result &X)
		{
			return reinterpret_cast<wrap_result>(X);
		}
	};

	template<>
	struct io_traits<in_out>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X)
		{
			return &X.internal();
		}
		static wrap_result wrap(internal_result &X)
		{
			return reinterpret_cast<wrap_result>(*X);
		}
	};

	template<>
	struct io_traits<out>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X) 
		{
			X = type();
			return &X.internal(); 
		}
		static wrap_result wrap(internal_result &X) 
		{
			internal_policy::construct(*X);
			return reinterpret_cast<wrap_result>(*X);
		}
	};
};

template<class Type, vartype_t Vt>
struct default_traits
{
	typedef Type type;
	typedef policy::standard_policy<type> internal_policy;

	typedef type internal_type;

	static const vartype_t vt = Vt;

	template<io_type Io>
	struct io_traits;

	template<>
	struct io_traits<in>
	{
		typedef internal_type internal_result;
		typedef type wrap_result;

		static internal_result internal(wrap_result X) { return X; }
		static wrap_result wrap(internal_result &X) { return X; }
	};

	template<>
	struct io_traits<in_out>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X) { return &X; }
		static wrap_result wrap(internal_result &X) { return *X; }
	};

	template<>
	struct io_traits<out>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X) 
		{ 
			X = type();
			return &X; 
		}
		static wrap_result wrap(internal_result &X) 
		{ 
			internal_policy::construct(*X);
			return *X;
		}
	};
};

struct undefined_traits
{
	template<io_type> struct io_traits 
	{
		typedef base::undefined internal_result;
	};
};

template<class Type>
struct enum_traits: default_traits<Type, ::VT_INT> {};

template<class Type>
struct traits: 
	boost::mpl::if_<boost::is_class<Type>, class_traits<Type>, 
	typename boost::mpl::if_<boost::is_enum<Type>, enum_traits<Type>,
	undefined_traits>::type>::type
{
};

template<io_type Io, class Type>
struct io_traits: traits<Type>::template io_traits<Io> {};

template<io_type Io, class Type>
struct internal_result 
{ 
	typedef typename io_traits<Io, Type>::internal_result type; 
};

template<io_type Io, class Type>
typename internal_result<Io, Type>::type internal(const Type &X)
{
	return io_traits<Io, Type>::internal(X);
}

template<io_type Io, class Type>
typename internal_result<Io, Type>::type internal(Type &X)
{
	return io_traits<Io, Type>::internal(X);
}

template<class Type>
struct internal_in_result: internal_result<in, Type> {};

template<class Type>
typename internal_in_result<Type>::type internal_in(const Type &X) 
{ 
	return internal<in>(X); 
}

template<class Type>
struct internal_in_out_result: internal_result<in_out, Type> {};

template<class Type>
typename internal_in_out_result<Type>::type internal_in_out(Type &X)
{ 
	return internal<in_out>(X); 
}

template<class Type>
struct internal_out_result: internal_result<out, Type> {};

template<class Type>
typename internal_out_result<Type>::type internal_out(Type &X)
{ 
	return internal<out>(X); 
}

template<io_type Io, class Type>
struct wrap_result 
{
	typedef typename io_traits<Io, Type>::wrap_result type;
};

template<io_type Io, class Type>
typename wrap_result<Io, Type>::type wrap(
	typename internal_result<Io, Type>::type &X)
{
	return io_traits<Io, Type>::wrap(X);
}

template<class Type>
struct wrap_in_result: wrap_result<in, Type> {};

template<class Type>
typename wrap_in_result<Type>::type wrap_in(
	typename internal_in_result<Type>::type &X)
{
	return wrap<in, Type>(X);
}

template<class Type>
struct wrap_in_out_result: wrap_result<in_out, Type> {};

template<class Type>
typename wrap_in_out_result<Type>::type wrap_in_out(
	typename internal_in_out_result<Type>::type &X)
{
	return wrap<in_out, Type>(X);
}

template<class Type>
struct wrap_out_result: wrap_result<out, Type> {};

template<class Type>
typename wrap_out_result<Type>::type wrap_out(
	typename internal_out_result<Type>::type &X)
{
	return wrap<out, Type>(X);
}

#define CBEAR_BERLIOS_DE_COM_DECLARE_DEFAULT_TRAITS(T, VT) \
	template<> struct traits<T>: default_traits<T, VT> {}

}
}

#endif
