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
#include <cbear.berlios.de/base/undefined.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/windows/com/ushort.hpp>
#include <cbear.berlios.de/windows/com/double.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

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
class safearray_policy: private policy::standard_policy< ::SAFEARRAY *>
{
public:
	typedef safearray_t<ValueType> safearray_t;
	typedef ::SAFEARRAY *type;
	typedef policy::standard_policy<type> standard_policy;
	typedef typename standard_policy::pointer pointer;
	typedef typename standard_policy::reference reference;

	using standard_policy::swap;

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
		X = ::SafeArrayCreateVectorEx(
			traits<ValueType>::vt, 0, ulong_t(Size), traits<ValueType>::extra());
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

	static std::size_t size(const type &X)
	{
		if(empty(X)) return 0;
		return X->rgsabound[0].cElements;
	}

	static iterator begin(const type &X)
	{
		return empty(X) ? iterator(): iterator(X->pvData);
	}

	static void destroy(type &X)
	{
		if(X) exception::throw_unless(::SafeArrayDestroy(X));
	}

	static void clear(type &X)
	{
		destroy(X);
		construct(X);
	}

	static void assign(type &X, const type &C)
	{
		destroy(X);
		construct_copy(X, C);
	}

	typedef policy::wrap<safearray_t, ::SAFEARRAY *, safearray_policy> wrap_type;
	typedef range::helper<safearray_t, iterator, const_iterator, wrap_type> 
		helper_type;

	static bool equal(const type &A, const type &B)
	{
		return range::equal(
			range::make_iterator_range(begin(A), size(A)), 
			range::make_iterator_range(begin(B), size(B)));
	}

	static void resize(type &X, std::size_t Size)
	{
		std::size_t OldSize = size(X);
		if(OldSize == Size) return;
		if(OldSize == 0)
		{
			construct_copy(X, Size);
			return;
		}
		if(Size == 0)
		{
			clear(X);
			return;
		}
		::SAFEARRAYBOUND bounds;
		bounds.cElements = ulong_t(Size);
		bounds.lLbound = 0;
		exception::throw_unless(::SafeArrayRedim(X, &bounds));
	}
};

}

template<class ValueType>
class safearray_t: public detail::safearray_policy<ValueType>::helper_type
{
public:

	typedef base::undefined extra_result;

	typedef detail::safearray_policy<ValueType> internal_policy;
	typedef typename internal_policy::helper_type helper_type;

	typedef move::t<safearray_t> move_type;

	typedef typename helper_type::size_type size_type;
	typedef typename helper_type::iterator iterator;
	typedef typename helper_type::const_iterator const_iterator;

	typedef typename helper_type::const_reference const_reference;

	static const vartype_t value_type_vt = traits<ValueType>::vt;
	static const vartype_t vt = VT_ARRAY | value_type_vt;

	class scoped_lock: boost::noncopyable
	{
	public:
		scoped_lock(const safearray_t &A): A(A) 
		{ 
			exception::throw_unless(::SafeArrayLock(this->A.internal())); 
		}
		~scoped_lock()
		{
			exception::throw_unless(::SafeArrayUnlock(this->A.internal()));
		}
	private:
		const safearray_t &A;
	};

	safearray_t() {}
	explicit safearray_t(size_type Size): helper_type(std::size_t(Size), 0)
	{
	}

	explicit safearray_t(const std::vector<ValueType> &C): helper_type(C, 0)
	{
	}

	safearray_t(const move_type &C) throw()
	{ 
		this->move_assign(*C);
	}

	safearray_t &operator=(const move_type &C) throw()
	{
		this->move_assign(*C);
		return *this;
	}

	void move_assign(safearray_t &F) throw()
	{
		this->swap(F);
	}

	bool empty() const { return internal_policy::empty(this->internal()); }
	size_type size() const 
	{
		return internal_policy::size(this->internal());
	}
	const_iterator begin() const 
	{
		return internal_policy::begin(this->internal());
	}
	const_iterator end() const
	{
		return this->begin() + this->size();
	}

	const_reference operator[](std::size_t I) const
	{
		if(this->size() <= I) throw std::exception("Wrong index");
		return this->begin()[I];
	}

	void resize(std::size_t Size)
	{
		internal_policy::resize(this->internal(), Size);
	}

	void clear()
	{
		internal_policy::clear(this->internal());
	}

	void push_back(const_reference R)
	{
		const std::size_t I = this->size();
		this->resize(I + 1);
		this->begin()[I] = R;
	}
};

}
}
}

#endif
