#ifndef CBEAR_BERLIOS_DE_BIT_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BIT_RANGE_HPP_INCLUDED

// std::size_t
#include <cstddef>

// boost::noncopyable
#include <boost/noncopyable.hpp>

#include <cbear.berlios.de/base/integer.hpp>
#include <cbear.berlios.de/meta/const.hpp>

namespace cbear_berlios_de
{
namespace bit
{

// To avoid conversion warnings.
template<class To>
struct cast
{
	template<class From>
	static To static_(From X) 
	{ 
		return static_cast<To>(X); 
	}
};

// To avoid conversion warnings.
template<>
struct cast<bool>
{
	template<class From>
	static bool static_(From X) 
	{ 
		return X != 0; 
	}
};

template<class T, T x>
class not
{
public:
	static T const value = static_cast<T>(~x & static_cast<T>(~0));
};

template<
	class Type, std::size_t First, std::size_t Last, class ValueType = Type>
struct range
{
	typedef typename ::boost::remove_const<Type>::type type;
	typedef typename ::boost::remove_const<ValueType>::type value_type;
	typedef typename base::make_unsigned<type>::type unsigned_type;

	static ::std::size_t const first = First;
	static ::std::size_t const last = Last;
	static ::std::size_t const size = last - first + 1;
	static unsigned_type const _1 = static_cast<unsigned_type>(1);
	static unsigned_type const unshifted_mask = (_1 << size) - _1;
	static unsigned_type const mask = 
		static_cast<unsigned_type>(unshifted_mask << first);
	static unsigned_type const inverse_mask = not<unsigned_type, mask>::value;

	static value_type get(type X) 
	{ 
		return cast<value_type>::static_((unsigned_type(X) & mask) >> first);
	}
	static void set(type &D, value_type S) 
	{ 
		D = 
			(unsigned_type(D) & inverse_mask) | 
			((unsigned_type(S) << first) & mask);
	}

	typedef Type &type_reference;

	class reference
	{
	public:
		explicit reference(type_reference X): 
			X(X) 
		{
		}
		reference(reference const &R):
			X(R.X)
		{
		}
		operator value_type() const 
		{ 
			return get(this->X);
		}
		reference &operator=(value_type V)
		{ 
			set(this->X, V); 
			return *this; 
		}
		reference &operator=(reference const &V)
		{
			set(this->X, get(V.X));
			return *this;
		}
	private:
		type_reference X;
	};

	static reference make_reference(type &X) 
	{ 
		return reference(X); 
	}
};

/* Because of

4.7 4 
	If the destination type is bool, see 4.12. If the source type is bool, the 
	value false is converted to zero and the value true is converted to one.

4.12
	An rvalue of arithmetic, enumeration, pointer, or pointer to member type can 
	be converted to an rvalue of type bool. A zero value, null pointer value, or 
	null member pointer value is converted to false; any other value is converted
	to true.
*/
template<class Type, std::size_t Number>
class one: public range<Type, Number, Number, bool> 
{
};

template<class Type, ::std::size_t Size, class ValueT = Type>
class range_t
{
public:

	typedef Type t;
	typedef ValueT value_t;
	typedef typename base::make_unsigned<t>::type unsigned_t;

	static unsigned_t const _1 = static_cast<unsigned_t>(1);
	static ::std::size_t const size = Size;
	static unsigned_t const unshifted_mask = (_1 << size) - _1;

	static unsigned_t mask(::std::size_t F, unsigned_t V = unshifted_mask)
	{
		return V << static_cast<unsigned_t>(F);
	}

	static unsigned_t inverse_mask(::std::size_t F)
	{
		return ~mask(F);
	}

	class reference
	{
	public:

		reference(Type &R, ::std::size_t F):
			R(R), F(F)
		{
		}

		void set(value_t V)
		{
			this->R = 
				this->R & 
				inverse_mask(this->F) | 
				mask(this->F, cast<unsigned_t>::static_(V));
		}

		value_t get() const
		{
			return cast<value_t>::static_(
				(cast<unsigned_t>::static_(this->R) >> this->F) & unshifted_mask);
		}

		operator value_t() const
		{
			return this->get();
		}

		reference &operator=(value_t V)
		{
			this->set(V);
			return *this;
		}

		reference &operator=(reference const &V)
		{
			this->set(V.get());
			return *this;
		}

	private:
		Type &R;
		::std::size_t F;
	};                
};

template<class Type>
class one_t: public range_t<Type, 1, bool>
{
};

/*
template<class Type>
class one_reference_t
{
public:

	typedef Type t;
	typedef typename ::boost::remove_const<t>::type value_t;
	typedef typename base::make_unsigned<value_t>::type unsigned_t;

	static unsigned_t mask(::std::size_t N, bool V = true)
	{
		return cast<unsigned_t>::static_(V) << cast<unsigned_t>::static_(N);
	}

	static unsigned_t inverse_mask(::std::size_t N)
	{
		return ~mask(N);
	}

	one_reference_t(Type &R, ::std::size_t N):
		R(R), N(N)
	{
	}

	one_reference_t(one_reference_t const &X):
		R(X.R), N(X.N)
	{
	}

	void set(bool V)
	{
		this->R = this->R & inverse_mask(this->N) | mask(this->N, V);
	}

	bool get() const
	{
		return cast<bool>::static_(
			(cast<unsigned_t>::static_(this->R) >> this->F) & 
			static_cast<unsigned_t>(1));
	}

	operator bool() const
	{
		return this->get();
	}

	one_reference_t &operator=(bool V)
	{
		this->set(V);
		return *this;
	}

	one_reference_t &operator=(one_reference_t const &V)
	{
		this->set(V.get());
		return *this;
	}

private:
	Type &R;
	::std::size_t const N;
};
*/

template<class Type>
typename one_t<Type>::reference make_one_reference(Type &R, ::std::size_t N)
{
	return one_t<Type>::reference<Type>(R, N);
}

}
}

#endif
