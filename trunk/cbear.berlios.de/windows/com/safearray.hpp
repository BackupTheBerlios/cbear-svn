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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED

#include <vector>

#include <cbear.berlios.de/range/empty.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/windows/com/double.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class ValueType>
class safearray_t;

namespace detail
{

template<class ValueType>
class safearray_policy //: private policy::standard_policy< ::SAFEARRAY *>
{
public:
	typedef safearray_t<ValueType> safearray_t;
	typedef ::SAFEARRAY *type;
	typedef policy::standard_policy<type> standard_policy;
	typedef typename standard_policy::pointer pointer;
	typedef typename standard_policy::reference reference;

	//using standard_policy::construct;

	static void construct(type &X) { X = type(); }

	static void construct_copy(type &X, const type &C) 
	{ 
		if(C)
		{
			exception::throw_unless(::SafeArrayCopy(C, &X));
		}
		else
		{
			X = 0;
		}
	}

	static void construct_copy(type &X, std::size_t Size)
	{
		if(Size==0) 
		{
			construct(X);
			return;
		}
		X = ::SafeArrayCreateVectorEx(traits<ValueType>::vt, 0, ulong_t(Size), 0);
	}

	template<class T>
	static void construct_copy(type &X, const T &C)
	{
		construct_copy(X, range::size(C));
		iterator I = begin(X);
		if(!I) return;
		for(range::sub_range<const T>::type R(C); !R.empty(); R.begin()++, I++)
		{
			*I = R.front();
		}
	}

	typedef ValueType value_type;
	typedef value_type *iterator;
	typedef value_type *const_iterator;

	static bool empty(const type &X) { return X == 0; }

	static iterator begin(const type &X)
	{
		return empty(X) ? iterator(): iterator(X->pvData);
	}

	static void destroy(type &X)
	{
		if(X) exception::throw_unless(::SafeArrayDestroy(X));
	}
	static void assign(type &X, const type &C)
	{
		destroy(X);
		construct_copy(X, C);
	}

	typedef policy::wrap<safearray_t, ::SAFEARRAY *, safearray_policy> wrap_type;
	typedef range::helper<safearray_t, iterator, const_iterator, wrap_type> 
		helper_type;
};

}

template<class ValueType>
class safearray_t: public detail::safearray_policy<ValueType>::helper_type
{
public:

	typedef detail::safearray_policy<ValueType> internal_policy;
	typedef typename internal_policy::helper_type helper_type;

	typedef typename helper_type::size_type size_type;
	typedef typename helper_type::iterator iterator;
	typedef typename helper_type::const_iterator const_iterator;

	static const vartype_t value_type_vt = traits<ValueType>::vt;
	static const vartype_t vt = VT_ARRAY | value_type_vt;

	safearray_t() {}
	explicit safearray_t(size_type Size): helper_type(std::size_t(Size), 0)
	{
	}

	explicit safearray_t(const std::vector<ValueType> &C): helper_type(C, 0)
	{
	}

	bool empty() const { return internal_policy::empty(this->internal()); }
	size_type size() const 
	{
		if(this->empty()) return 0;
		return this->internal().rgsabound[1].cElements;
	}
	const_iterator begin() const 
	{
		return internal_policy::begin(this->internal());
	}
	const_iterator end() const
	{
		return this->begin() + this->size();
	}
};

}
}
}

#endif
