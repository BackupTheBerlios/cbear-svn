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
		return reinterpret_cast<half_type *>(&X); 
	}

	static const half_type *array(const Type &X) 
	{ 
		return reinterpret_cast<const half_type *>(&X); 
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

	out_t(T X): X(X), P(1)
	{
		const T N = this->X / Base;
		while(N >= this->P) this->P *= Base;
	}

	out_t(T X, std::size_t I): X(X), P(1) 
	{
		for(; I>1; --I) 
		{
			BOOST_ASSERT(boost::integer_traits<T>::const_max / Base > this->P);
			this->P *= Base; 
		}
		if(this->X / this->P >= Base) this->X %= this->P * Base;
	}

	template<class Char>
	void print(std::basic_ostream<Char> &O) const
	{
		T PI = this->P;
		T XI = this->X;
		for(;;)
		{
			const T S = XI / PI;
			O << Char(S + (S < 10 ? '0': 'A' - 10));
			if(PI==1) return;
			XI %= PI;
			PI /= Base;
		}
	}

	template<class S>
	void write(S &s) const
	{
		T PI = this->P;
		T XI = this->X;
		for(;;)
		{
			const T c = XI / PI;
			stream::write(s, S::char_type(c + (c < 10 ? '0': 'A' - 10)));
			if(PI==1) return;
			XI %= PI;
			PI /= Base;
		}
	}

private:
	T X;
	T P;
};

template<std::size_t Base, class T>
out_t<Base, T> out(T X) { return out_t<Base, T>(X); }

template<std::size_t Base, class T>
out_t<Base, T> out(T X, std::size_t I) { return out_t<Base, T>(X, I); }

template<class OStream, std::size_t Base, class T>
OStream &operator<<(OStream &O, const out_t<Base, T> &Out)
{
	Out.print(O);
	return O;
}

template<class T>
out_t<16, T> hex(T X) { return out_t<16, T>(X); }

template<class T>
out_t<16, T> hex(T X, std::size_t I) { return out_t<16, T>(X, I); }

}
}

#endif
