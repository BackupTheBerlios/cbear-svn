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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_BSTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_BSTR_HPP_INCLUDED

#include <cbear.berlios.de/range/equal.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace windows
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

	typedef standard_policy_type::value_type value_type;
	typedef standard_policy_type::reference reference;
	typedef standard_policy_type::pointer pointer;

	typedef type iterator;
	typedef range::iterator_range<iterator> iterator_range;
	typedef const value_type *const_iterator;
	typedef range::iterator_range<const_iterator> const_iterator_range;

	static std::size_t size(type A)
	{
		return ::SysStringLen(A);
	}

	static iterator_range make_sub_range(type A)
	{
		return iterator_range(A, A + size(A));
	}

	template<class Range>
	static void construct_copy(type &This, const Range &Source)
	{
		This = ::SysAllocStringLen(Source.begin(), uint_t(Source.size()));
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

typedef range::helper<
	bstr_t, 
	bstr_policy::iterator, 
	bstr_policy::const_iterator, 
	bstr_wrap> bstr_helper;

}

#pragma pack(push, 1)

class bstr_t: public detail::bstr_helper
{
public:
	typedef detail::bstr_helper helper_type;
	typedef detail::bstr_wrap wrap_type;
	typedef wrap_type::internal_policy internal_policy;

	typedef internal_policy::value_type value_type;
	typedef internal_policy::iterator iterator;
	typedef internal_policy::iterator_range iterator_range;
	typedef internal_policy::const_iterator const_iterator;
	typedef internal_policy::const_iterator_range const_iterator_range;
	typedef iterator_range::size_type size_type; 

	static const vartype_t vt = ::VT_BSTR;

	bstr_t() {}

	template< ::std::size_t Size>
	bstr_t(const wchar_t (&X)[Size]): helper_type(const_iterator_range(X), 0) {}

	bstr_t(const std::basic_string<wchar_t> &X): 
		helper_type(const_iterator_range(X.c_str(), (size_type)X.size()), 0)
	{
	}

	wchar_t *c_str() const { return this->internal(); }

	size_type size() const 
	{ 
		return (size_type)internal_policy::size(this->internal()); 
	}

	iterator begin() { return this->internal(); }
	iterator end() { return this->internal() + size(); }

	const_iterator begin() const { return this->internal(); }
	const_iterator end() const { return this->internal() + size(); }
};

#pragma pack(pop)

}
}
}

#endif
