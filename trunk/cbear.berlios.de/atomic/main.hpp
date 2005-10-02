/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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

#ifndef CBEAR_SOURCEFORGE_NET_ATOMIC_MAIN_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_ATOMIC_MAIN_HPP_INCLUDED

#include <windows.h>

// std::size_t
#include <cstddef>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::noncopyable
#include <boost/noncopyable.hpp>

#include <cbear.sourceforge.net/integer.hpp>

namespace cbear_sourceforge_net
{
namespace atomic
{

namespace detail
{

struct nothing {};

template<class T, std::size_t>
struct integer_traits;

template<class Type>
struct integer_traits<Type, 4>
{
	typedef ::LONG internal_type;
	typedef Type type;

	BOOST_STATIC_ASSERT(sizeof(volatile type)==sizeof(internal_type));
	BOOST_STATIC_ASSERT(sizeof(volatile type)==4);
	BOOST_STATIC_ASSERT(base::is_integer<Type>::value);

	static type exchange(volatile type &This, type Exchange) 
	{ 
		return ::InterlockedExchange((internal_type *)&This, Exchange);
	}

	static type compare_exchange(
		volatile type &This, type Exchange, type Comperand)
	{
		return ::InterlockedCompareExchange(
			(internal_type *)&This, Exchange, Comperand);
	}

	static type exchange_add(volatile type &This, type Value)
	{
		return ::InterlockedExchangeAdd((internal_type *)&This, Value);
	}

	static type decrement(volatile type &This)
	{
		return ::InterlockedDecrement((internal_type *)&This);
	}

	static type increment(volatile type &This)
	{
		return ::InterlockedIncrement((internal_type *)&This);
	}
};

/*
template<class Type>
struct integer_traits<Type, 8>
{
	typedef ::LONGLONG volatile internal_type;
	typedef Type volatile type;

	BOOST_STATIC_ASSERT(sizeof(type)==sizeof(internal_type));
	BOOST_STATIC_ASSERT(sizeof(type)==8);

	type exchange(type &This, type New)
	{
		return ::InterlockedExchange64((internal_type *)&This, New);
	}

	type compare_exchange(type &This, type Exchange, type Comparand)
	{
		return ::InterlockedCompareExchange64(
			(internal_type *)&This, Exchange, Comperand);
	}

	type exchange_add(type &This, type Value)
	{
		return ::InterlockedExchangeAdd64(This, Value);
	}

	type decrement(type &This)
	{
		return ::InterlockedDecrement64((internal_type *)&This);
	}

	type increment(type &This)
	{
		return ::InterlockedIncrement64((internal_type *)&This);
	}
};
*/

template<class Type>
struct pointer_traits
{
	typedef void *internal_type;
	typedef Type *type;

	BOOST_STATIC_ASSERT(sizeof(volatile type)==sizeof(internal_type));

	static type read(volatile type &This)
	{
		return This;
	}

	static type exchange(volatile type &This, type Exchange)
	{
		return reinterpret_cast<type>(InterlockedExchangePointer(
			reinterpret_cast<internal_type *>(&(type &)(This)), 
			Exchange));
	}

	static type compare_exchange(
		volatile type &This, type Exchange, type Comperand)
	{
		return reinterpret_cast<type>(InterlockedCompareExchangePointer(
			reinterpret_cast<internal_type *>(&(type &)(This)),
			Exchange, 
			Comperand));
	}
};

}

template<class T>
struct traits: detail::integer_traits<T, sizeof(T)> {};

template<class T>
struct traits<T *>: detail::pointer_traits<T> {};

template<class T, class E>
T exchange(volatile T &This, E Exchange)
{
	return traits<T>::exchange(This, Exchange);
}

template<class T, class E, class C>
T compare_exchange(volatile T &This, E Exchange, C Comperand)
{
	return traits<T>::compare_exchange(This, Exchange, Comperand);
}

template<class T, class V>
T exchange_add(volatile T &This, V Value)
{
	return traits<T>::exchange_add(This, Value);
}

template<class T>
T decrement(volatile T &This)
{
	return traits<T>::decrement(This);
}

template<class T>
T increment(volatile T &This)
{
	return traits<T>::increment(This);
}

template<class T>
T read(volatile T &This)
{
	return compare_exchange(This, T(), T());
}

template<class T>
class wrap: boost::noncopyable
{
public:

	typedef T type;

	explicit wrap(type Internal = T()): Internal(Internal) {}

	type exchange(type Exchange)
	{
		return atomic::exchange(this->Internal, Exchange);
	}

	type compare_exchange(type Exchange, type Comperand)
	{
		return atomic::compare_exchange(this->Internal, Exchange, Comperand);
	}

	type exchange_add(type Value)
	{
		return atomic::exchange_add(this->Internal, Value);
	}

	type decrement()
	{
		return atomic::decrement(this->Internal);
	}

	type increment()
	{
		return atomic::increment(this->Internal);
	}

	type read()
	{
		return atomic::read(this->Internal);
	}

private:
	volatile type Internal;
};

template<class Id, class T>
class static_wrap
{
public:
	typedef T type;

	static type exchange(type Exchange)
	{
		return atomic::exchange(This, Exchange);
	}

	static type compare_exchange(type Exchange, type Comperand)
	{
		return atomic::compare_exchange(This, Exchange, Comperand);
	}

	static type exchange_add(type Value)
	{
		return atomic::exchange_add(This, Value);
	}

	static type decrement()
	{
		return atomic::decrement(This);
	}

	static type increment()
	{
		return atomic::increment(This);
	}

	static type read()
	{
		return atomic::read(This);
	}

private:
	static volatile type This;
};

template<class Id, class T>
volatile T static_wrap<Id, T>::This = 0;

}
}

#endif
