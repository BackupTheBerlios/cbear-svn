#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED

#include <cbear.berlios.de/range/reverse_iterator_range.hpp>
#include <cbear.berlios.de/range/move.hpp>
#include <cbear.berlios.de/range/empty.hpp>
#include <cbear.berlios.de/base/undefined.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/windows/com/ushort.hpp>
#include <cbear.berlios.de/windows/com/double.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

#include <vector>

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

	typedef policy::wrap<safearray_t, ::SAFEARRAY *, safearray_policy>
		wrap_internal_type;

	class wrap_type: public wrap_internal_type
	{
	public:
		typedef typename safearray_policy::iterator iterator;
		typedef typename safearray_policy::const_iterator const_iterator;
		wrap_type()
		{
		}
		template<class T1, class T2>
		wrap_type(T1 const &X1, T2 const &X2):
			wrap_internal_type(X1, X2)
		{
		}
	};
	typedef range::helper_t<safearray_t, /*iterator, const_iterator,*/ wrap_type> 
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

	typedef ValueType value_type;
	typedef typename helper_type::size_type size_type;
	typedef typename helper_type::iterator iterator;
	typedef typename helper_type::const_iterator const_iterator;

	typedef typename helper_type::const_reference const_reference;

	typedef range::iterator_range<iterator> iterator_range_t;
	typedef range::iterator_range<const_iterator> const_iterator_range_t;

	typedef typename range::reverse_iterator_range<iterator_range_t>::type 
		reverse_iterator_range_t;
	typedef typename range::reverse_iterator_range<const_iterator_range_t>::type 
		const_reverse_iterator_range_t;

	static vartype_t::enum_t const value_type_vt = traits<ValueType>::vt;
	static vartype_t::enum_t const vt = 
		vartype_t::or_<vartype_t::array, value_type_vt>::value;

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

	safearray_t &operator=(const const_iterator_range_t &R)
	{
		this->resize(R.size());
		range::copy(R, this->begin());
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

	const_reference operator[](::std::size_t I) const
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

	void push_back(value_type const &R)
	{
		::std::size_t const I = this->size();
		this->resize(I + 1);
		this->begin()[I] = R;
	}

	void pop_back()
	{
		BOOST_ASSERT(!this->empty());
		this->resize(boost::prior(this->size()));
	}

	template<class R>
	iterator insert_range(iterator i, R const &r)
	{
		if(range::empty(r))
		{
			return i;
		}
		size_type const size = this->size();
		size_type const r_size = range::size(r);
		difference_type const i_n = i - this->begin();
		this->resize(size + r_size);
		iterator const b = this->begin();
		i = b + i_n;
		range::move(
			range::make_reverse_iterator_range(i, b + size),
			reverse_iterator(this->end()));
		range::copy(r, i);
		return i;
	}

	void erase(iterator I)
	{
		iterator const E = this->end();
		BOOST_ASSERT((this->begin()<=I) && (I<=E));
		if(I!=E) 
		{
			range::move(iterator_range(I, ::boost::prior(E)), ::boost::next(I));
			/*
			for(iterator N = ::boost::next(I); N!=E; I = N++)
			{
				move::assign(*I, *N);
			}
			*/
			this->pop_back();
		}
	}
};

}
}
}

#endif
