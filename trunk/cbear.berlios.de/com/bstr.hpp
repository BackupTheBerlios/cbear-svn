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
#ifndef CBEAR_BERLIOS_DE_COM_BSTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_BSTR_HPP_INCLUDED

#include <cbear.berlios.de/com/traits.hpp>
#include <cbear.berlios.de/range/equal.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace com
{

class bstr_t;

namespace detail
{

struct bstr_policy: private policy::standard_policy< ::BSTR>
{
	typedef ::BSTR type;
	typedef policy::standard_policy<type> standard_policy_type;

	using standard_policy_type::construct;

	typedef range::iterator_range<type> iterator_range;

	static iterator_range make_sub_range(type A)
	{
		return iterator_range(A, A + ::SysStringLen(A));
	}

	static void construct_copy(type &This, const iterator_range &Source)
	{
		This = ::SysAllocStringLen(Source.begin(), Source.size());
	}

	static void construct_copy(type &This, const type &Source)
	{
		construct_copy(This, make_sub_range(Source));
	}

	static void destroy(type &This) 
	{
		::SysFreeString(This);
	}

	static void assign(type &This, const type &Source)
	{ 
		type New;
		construct_copy(New, Source);
		destroy(This);
		This = New;
	}

	static bool equal(const type &A, const type &B)
	{
		return range::equal(make_sub_range(A), make_sub_range(B));
	}
	/*
	static bool less(const type &A, const type &B)
	{
		return A<B;
	}
	*/

	typedef standard_policy_type::value_type value_type;
	typedef standard_policy_type::reference reference;
	typedef standard_policy_type::pointer pointer;

	/*
	static reference reference_of(const type &This) { return *This; }
	*/

	using standard_policy_type::output;
};

typedef policy::wrap<bstr_t, ::BSTR, bstr_policy> bstr_wrap;

}

class bstr_t: public detail::bstr_wrap
{
public:
	typedef detail::bstr_wrap wrap_type;
	typedef wrap_type::internal_policy internal_policy;
	typedef internal_policy::value_type value_type;
	typedef internal_policy::iterator_range iterator_range;
	bstr_t() {}
	template< ::std::size_t Size>
	bstr_t(const wchar_t (&X)[Size]): wrap_type(iterator_range(X), 0) {}
};

}
}

#endif
