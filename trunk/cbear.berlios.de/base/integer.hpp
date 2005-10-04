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
#ifndef CBERA_BERLIOS_DE_BASE_INTEGER_HPP_INCLUDED
#define CBERA_BERLIOS_DE_BASE_INTEGER_HPP_INCLUDED

// std::size_t
#include <cstddef>
// CHAR_BIT
#include <climits>

// std::numeric_limits
#include <limits>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>

// boost::int_t, boost::uint_t.
#include <boost/integer.hpp>
// boost::mpl::bool_
#include <boost/mpl/bool.hpp>

namespace cbear_berlios_de
{
namespace base
{

/// Meta functions. Returns 'true' if the given type is an integer type.
template<class Type>
struct is_integer: boost::mpl::bool_<std::numeric_limits<Type>::is_integer> {};

/// Meta functions. Returns 'true' if the given type is signed integer type.
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

namespace detail
{

// LITTLE ENDIAN
enum endian_offset { low_offset, high_offset };

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

}
}

#endif
