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
#ifndef NET_SOURCEFORGE_CBEAR_BIT_RANGE_HPP_INCLUDED
#define NET_SOURCEFORGE_CBEAR_BIT_RANGE_HPP_INCLUDED

// std::size_t
#include <cstddef>

#include <net/sourceforge/cbear/base/integer.hpp>

namespace net
{
namespace sourceforge
{
namespace cbear
{
namespace bit
{

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
		return (unsigned_type(X) & mask) >> first; 
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
		explicit reference(type &X): X(X) {}
		operator value_type() const 
		{ 
			return get(this->X); 
		}
		const reference &operator=(value_type V) const 
		{ 
			set(this->X, V); return *this; 
		}
	private:
		type &X;
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
}
}

#endif
