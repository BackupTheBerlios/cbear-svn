#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_TRAITS_HPP_INCLUDED

#include <cbear.berlios.de/base/undefined.hpp>
#include <cbear.berlios.de/move/main.hpp>
#include <cbear.berlios.de/windows/message_box.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/com/vartype.hpp>

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
namespace windows
{
namespace com
{

using namespace windows;

template<class Type, class = void>
struct traits;

enum io_type
{
	in = 1,
	out = 2,
	in_out = in|out,
};

// typedef ::VARTYPE vartype_t;

template<class Type>
struct class_traits
{
	typedef Type type;
	typedef typename type::internal_policy internal_policy;
	typedef typename internal_policy::type internal_type;

	typedef typename type::move_type move_type;

	static const vartype_t::enum_t vt = type::vt;

	static typename type::extra_result extra() { return type::extra(); }

	template<io_type Io, class = void>
	struct io_traits;

	template<class D>
	struct io_traits<in, D>
	{
		typedef internal_type internal_result;
		typedef const type &wrap_result;

		static internal_result internal(wrap_result X) 
		{
			return X.internal();
		}
		static wrap_result wrap(internal_result &X)
		{
			return type::wrap_ref(X);
		}
	};

	template<class D>
	struct io_traits<in_out, D>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X)
		{
			return &X.internal();
		}
		static wrap_result wrap(internal_result &X)
		{
			return type::wrap_ref(*X);
		}
	};

	template<class D>
	struct io_traits<out, D>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X) 
		{
			//type Temp;
			//Temp.swap(X);
			X = type();
			return &X.internal(); 
		}
		static wrap_result wrap(internal_result &X) 
		{
			internal_policy::construct(*X);
			return type::wrap_ref(*X);
		}
	};
};

template<class Type, vartype_t::enum_t Vt>
struct default_traits
{
	typedef Type type;
	typedef policy::standard_policy<type> internal_policy;

	typedef type internal_type;

	typedef type move_type;

	static vartype_t::enum_t const vt = Vt;

	static void *extra() { return 0; }

	template<io_type Io, class D = void>
	struct io_traits;

	template<class D>
	struct io_traits<in, D>
	{
		typedef internal_type internal_result;
		typedef type wrap_result;

		static internal_result internal(wrap_result X) { return X; }
		static wrap_result wrap(internal_result &X) { return X; }
	};

	template<class D>
	struct io_traits<in_out, D>
	{
		typedef internal_type *internal_result;
		typedef type &wrap_result;

		static internal_result internal(wrap_result X) { return &X; }
		static wrap_result wrap(internal_result &X) { return *X; }
	};

	template<class D>
	struct io_traits<out, D>
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
struct enum_traits: default_traits<Type, vartype_t::int_> 
{
};

template<class Type, class>
struct traits: 
	boost::mpl::if_<
		boost::is_class<Type>, 
		class_traits<Type>, 
		typename boost::mpl::if_<
			boost::is_enum<Type>, enum_traits<Type>, undefined_traits>::type>::type
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

template<io_type Io, class Type>
struct internal_result<Io, move::t<Type> >: internal_result<Io, Type>
{ 
};

template<io_type Io, class Type>
typename internal_result<Io, Type>::type internal(const move::t<Type> &X)
{
	return io_traits<Io, Type>::internal(X.get());
}

template<io_type Io, class Type>
typename internal_result<Io, Type>::type internal(move::t<Type> &X)
{
	return io_traits<Io, Type>::internal(X.get());
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

#define CBEAR_BERLIOS_DE_WINDOWS_COM_DECLARE_DEFAULT_TRAITS(T, VT) \
	template<class X> struct traits<T, X>: default_traits<T, VT> {}

}
}
}

#endif
