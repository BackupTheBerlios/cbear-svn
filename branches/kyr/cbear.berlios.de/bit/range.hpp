#ifndef CBEAR_BERLIOS_DE_BIT_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BIT_RANGE_HPP_INCLUDED

// std::size_t
#include <cstddef>

// boost::noncopyable
#include <boost/noncopyable.hpp>

#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace bit
{

namespace detail
{

// To avoid conversion warnings.
template<class To>
struct casting
{
	template<class From>
	static To cast(From X) { return To(X); }
};

// To avoid conversion warnings.
template<>
struct casting<bool>
{
	template<class From>
	static bool cast(From X) { return X != 0; }
};

}

template<
	class Type, std::size_t First, std::size_t Last, class ValueType = Type>
struct range
{
	typedef Type type;
	typedef ValueType value_type;
	typedef typename base::make_unsigned<type>::type unsigned_type;

	static const std::size_t first = First;
	static const std::size_t last = Last;
	static const std::size_t size = last - first + 1;
	static const unsigned_type mask = 
		((unsigned_type(1) << size) - unsigned_type(1)) << first;
	static const unsigned_type inverse_mask = ~mask;

	static value_type get(type X) 
	{ 
		return detail::casting<value_type>::cast(
			(unsigned_type(X) & mask) >> first); 
	}
	static void set(type &D, value_type S) 
	{ 
		D = 
			(unsigned_type(D) & inverse_mask) | 
			((unsigned_type(S) << first) & mask);
	}

	class reference
	{
	public:
		explicit reference(type &X): X(&X) {}
		operator value_type() const 
		{ 
			return get(*this->X);
		}
		const reference &operator=(value_type V) const 
		{ 
			set(*this->X, V); return *this; 
		}
	private:
		type *X;
	};

	static reference make_reference(type &X) { return reference(X); }
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
struct one: range<Type, Number, Number, bool> {};

}
}

#endif
