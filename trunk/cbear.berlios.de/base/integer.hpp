#ifndef CBEAR_BERLIOS_DE_BASE_INTEGER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_INTEGER_HPP_INCLUDED

// std::size_t
#include <cstddef>
// CHAR_BIT
#include <climits>

// std::numeric_limits
#include <limits>

// BOOST_ASSERT
#include <boost/assert.hpp>
// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// BOOST_..._ENDIAN
#include <boost/detail/endian.hpp>
// boost::int_t, boost::uint_t.
#include <boost/integer.hpp>
// boost::mpl::bool_
#include <boost/mpl/bool.hpp>

namespace cbear_berlios_de
{
namespace base
{

/// Meta functions. Returns 'true' if the given type is an integer type.
/// To be consistent with std library.
template<class Type>
struct is_integer: boost::mpl::bool_<std::numeric_limits<Type>::is_integer> {};

/// Meta functions. Returns 'true' if the given type is signed integer type.
/// Use boost::is_signed instead.
template<class Type>
struct is_signed: boost::mpl::bool_<std::numeric_limits<Type>::is_signed> {};

namespace detail
{

template<class Least, std::size_t Bits, std::size_t LeastBits>
struct integer_helper1 {};

template<class Least, std::size_t Bits>
struct integer_helper1<Least, Bits, Bits>
{
	typedef Least type;
};

template<class Type, std::size_t Bits> 
struct integer_helper: integer_helper1<
	typename Type::least, Bits, sizeof(typename Type::least)*CHAR_BIT>
{
};

}

/// The built-in signed integral type with the given number of bits, 
/// including the sign bit.
template<std::size_t Bits>
struct int_t: detail::integer_helper<boost::int_t<Bits>, Bits> {};

/// The built-in unsigned integral type with the given number of bits.
template<std::size_t Bits>
struct uint_t: detail::integer_helper<boost::uint_t<Bits>, Bits> {};

template<>
struct uint_t<64>
{
	typedef unsigned __int64 type;
};

template<>
struct int_t<64>
{
	typedef __int64 type;
};

/// The built-in signed integral type with the same number of bits (including 
/// the sign bit) as the given type has.
template<class Type>
struct make_signed: int_t<sizeof(Type)*CHAR_BIT> 
{
	BOOST_STATIC_ASSERT(is_integer<Type>::value);
};

/// The built-in unsigned integral type with the same number of bits as the 
/// given type has, including the sign bit.
template<class Type>
struct make_unsigned: uint_t<sizeof(Type)*CHAR_BIT> 
{
	BOOST_STATIC_ASSERT(is_integer<Type>::value);
};

template<>
struct make_unsigned<std::ptrdiff_t>
{
	typedef std::size_t type;
};

template<>
struct make_unsigned<std::size_t>
{
	typedef std::size_t type;
};

template<>
struct make_signed<std::ptrdiff_t>
{
	typedef std::ptrdiff_t type;
};

template<>
struct make_signed<std::size_t>
{
	typedef std::ptrdiff_t type;
};

template<class T>
typename make_unsigned<T>::type unsigned_(T X)
{
	return make_unsigned<T>::type(X);
}

template<class T>
typename make_signed<T>::type signed_(T X)
{
	return make_signed<T>::type(X);
}

namespace detail
{

#ifdef BOOST_LITTLE_ENDIAN
enum endian_offset { low_offset, high_offset };
#elif defined(BOOST_BIG_ENDIAN)
enum endian_offset { high_offset, low_offset };
#else
#error Unknown machine endianness detected.
#endif

template<class Type>
struct integer_parts
{
	BOOST_STATIC_ASSERT(is_integer<Type>::value);
	BOOST_STATIC_ASSERT(sizeof(Type) % 2 == 0);

	static const std::size_t half_size = sizeof(Type) / 2;
	typedef typename uint_t<half_size * CHAR_BIT>::type half_type;

	static half_type *array(Type &X) 
	{ 
		return cast::traits<half_type *>::reinterpret(&X);
	}

	static const half_type *array(const Type &X) 
	{ 
		return cast::traits<half_type const *>::reinterpret(&X);
	}
};

}

template<class Type>
struct half
{
	typedef typename detail::integer_parts<Type>::half_type type;
};

// Because of low(Type &) and high(Type &).
template<class Type> struct half<const Type> {};

template<class Type>
typename half<Type>::type low(const Type &X) 
{ 
	return detail::integer_parts<Type>::array(X)[detail::low_offset];
}

template<class Type>
typename half<Type>::type &low(Type &X) 
{ 
	return detail::integer_parts<Type>::array(X)[detail::low_offset]; 
}

template<class Type>
typename half<Type>::type high(const Type &X)
{
	return detail::integer_parts<Type>::array(X)[detail::high_offset];
}

template<class Type>
typename half<Type>::type &high(Type &X)
{
	return detail::integer_parts<Type>::array(X)[detail::high_offset];
}

template<class Half>
struct compose_result
{
	BOOST_STATIC_ASSERT(is_integer<Half>::value);
	typedef typename uint_t<sizeof(Half) * CHAR_BIT * 2>::type type;
};

template<class Half>
typename compose_result<Half>::type compose(const Half &High, const Half &Low)
{
	typename compose_result<Half>::type Result;
	low(Result) = Low;
	high(Result) = High;
	return Result;
}

template<std::size_t Base, class T>
class out_t
{
public:

	out_t(T X): 
		X(X), 
		P(1)
	{
		T const N = this->X / Base;
		while(N >= this->P) 
		{
			this->P *= Base;
		}
	}

	out_t(T X, std::size_t I): 
		X(X), 
		P(1) 
	{
		for(; I>1; --I) 
		{
			BOOST_ASSERT(boost::integer_traits<T>::const_max / Base > this->P);
			this->P *= Base; 
		}
		if(this->X / this->P >= Base) 
		{
			this->X %= this->P * Base;
		}
	}


	template<class S>
	void write(S &s) const
	{
		typedef typename S::value_type value_type;
		T PI = this->P;
		T XI = this->X;
		for(;;)
		{
			const T c = XI / PI;
			s << value_type(c + (c < 10 ? '0': 'A' - 10));
			if(PI==1) 
			{
				return;
			}
			XI %= PI;
			PI /= Base;
		}
	}

private:
	T X;
	T P;
};

template<std::size_t Base, class T>
class uint_fixed_read
{
public:

	uint_fixed_read(T &X, std::size_t I):
		X(X),
		I(I)
	{
	}

	template<class S>
	void read(S &s) const
	{
		this->X = 0;
		typedef typename S::value_type value_type;
		for(std::size_t Ii = I; Ii > 0; --Ii)
		{
			value_type C;
			s >> C;
			if('0' <= C && C <= '9')
			{
				C -= '0';
			}
			else if('A' <= C && C <= 'Z')
			{
				C -= ('A' - 10);
			}
			else if('a' <= C && C <= 'z')
			{
				C -= ('a' - 10);
			}
			else
			{
				return;
			}
			if(C >= Base)
			{
				return;
			}
			// It should throw an exception if C is not in any range or >= Base.
			X = X * Base + T(C);
		}
	}
	
private:
	T &X;
	std::size_t const I;
	uint_fixed_read &operator=(uint_fixed_read const &);
};

template<std::size_t Base, class T>
class uint_read
{
public:

	uint_read(T &X):
		X(X)
	{
	}

	template<class S>
	void read(S &s) const
	{
		this->X = 0;
		typedef typename S::value_type value_type;
		typedef typename S::const_iterator_range const_iterator_range;
		for(;;)
		{
			const_iterator_range R = s.get_front_range(1);
			if(R.size() != 1)
			{
				return;
			}
			value_type C = R.front();
			if('0' <= C && C <= '9')
			{
				C -= '0';
			}
			else if('A' <= C && C <= 'Z')
			{
				C -= ('A' - 10);
			}
			else if('a' <= C && C <= 'z')
			{
				C -= ('a' - 10);
			}
			else
			{
				return;
			}
			if(C >= Base)
			{
				return;
			}			
			X = X * Base + T(C);
			s.pop_front_range(1);
		}
	}

private:
	T &X;
	uint_read &operator=(uint_read const &);
};

template<std::size_t Base, class T>
out_t<Base, T> out(T X) { return out_t<Base, T>(X); }

template<std::size_t Base, class T>
out_t<Base, T> out(T X, std::size_t I) { return out_t<Base, T>(X, I); }

template<class T>
uint_read<10, T> dec(T &X) 
{ 
	return uint_read<10, T>(X); 
}

template<class T>
out_t<16, T> hex(T X) { return out_t<16, T>(X); }

template<class T>
out_t<16, T> hex(T const &X, std::size_t I) { return out_t<16, T>(X, I); }

template<class T>
uint_fixed_read<16, T> hex(T &X, std::size_t I)
{
	return uint_fixed_read<16, T>(X, I);
}

}
}

#endif
