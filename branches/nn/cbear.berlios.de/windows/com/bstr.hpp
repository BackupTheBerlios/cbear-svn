#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_BSTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_BSTR_HPP_INCLUDED

#include <cbear.berlios.de/range/equal.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/range/fill.hpp>
#include <cbear.berlios.de/range/copy.hpp>
#include <cbear.berlios.de/range/lexicographic/compare.hpp>
#include <cbear.berlios.de/range/empty.hpp>
#include <cbear.berlios.de/base/const_ref.hpp>
#include <cbear.berlios.de/base/swap.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/stream/read.hpp>
#include <cbear.berlios.de/base/string.hpp>

// ::SysStringLen
#pragma comment(lib, "oleaut32.lib")

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
	using standard_policy_type::swap;

	typedef standard_policy_type::value_type value_type;
	typedef standard_policy_type::reference reference;
	typedef standard_policy_type::pointer pointer;

	typedef type iterator;
	typedef range::iterator_range<iterator> iterator_range;
	typedef const value_type *const_iterator;
	typedef range::iterator_range<const_iterator> const_iterator_range;

	static std::size_t size(type A)
	{
		// MSDN: if the A is null, zero is returned.
		return ::SysStringLen(A);
	}

	static iterator_range make_sub_range(type A)
	{
		return iterator_range(A, A + size(A));
	}

	//

	class bad_alloc: public std::bad_alloc
	{
	};

	static void alloc(
		type &This, const_iterator Begin, const std::size_t &Size)
	{
		if(Size)
		{
			This = ::SysAllocStringLen(Begin, uint_t(Size));
			if(!This) throw bad_alloc();
		}
		else
		{
			This = 0;
		}
	}

	static void alloc(type &This, const std::size_t &Size) 
	{ 
		alloc(This, 0, Size); 
	}

	template<class Range>
	static void construct_copy(type &This, const Range &Source)
	{
		alloc(This, range::begin(Source), range::size(Source));
	}

	static void construct_copy(type &This, const type &Source)
	{
		alloc(This, Source, size(Source));
	}

	//

	// "This" must not be 0!
	static void realloc(
		type &This, const iterator &SourceBegin, std::size_t SourceSize)
	{
		if(!::SysReAllocStringLen(&This, SourceBegin, uint_t(SourceSize)))
			throw bad_alloc();
	}

	// "This" must not be 0!
	static void reconstruct_copy(type &This, const type &Source)
	{
		realloc(This, Source, size(Source));
	}

	static void resize(type &This, std::size_t NewSize)
	{
		const iterator_range ThisRange = make_sub_range(This);
		const std::ptrdiff_t Dif = NewSize - ThisRange.size();
		if(!Dif) 
		{
			return;
		}
		if(Dif < 0) 
		{ 
			realloc(This, This, NewSize); 
			return; 
		}
		// constructing a new BSTR.
		type New;
		alloc(New, NewSize);
		range::fill(
			base::const_ref(iterator_range(range::copy(ThisRange, New), Dif)), 0);
		New[NewSize] = 0;
		//
		destroy(This);
		This = New;
	}

	static void destroy(type &This) 
	{
		// MSDN: if This is null, the function simply returns.
		::SysFreeString(This);
	}

	static void assign(type &This, const type &Source)
	{
		if(This==Source) return;
		if(!This) { construct_copy(This, Source); return; }
		reconstruct_copy(This, Source);
	}

	static bool equal(const type &A, const type &B)
	{
		return range::equal(make_sub_range(A), make_sub_range(B));
	}

	// 1. The source range can be a subrange of an operated object so
	// we can't use resize.
	// 2. Realloc can work only to decrease.
	template<class SourceRange>
	static void push_back_range(type &This, const SourceRange &Range)
	{
		if(range::empty(Range)) return;
		//
		const iterator_range ThisRange = make_sub_range(This);
		const std::size_t NewSize = ThisRange.size() + range::size(Range);
		// constructing a new BSTR.
		type New;
		alloc(New, NewSize);
		range::copy(Range, range::copy(ThisRange, New));
		New[NewSize] = 0;
		//
		destroy(This);
		This = New;
	}

	static void push_back_range(type &This, const value_type &V)
	{
		push_back_range(This, const_iterator_range(&V, &V + 1));
	}

	static void push_back_range(type &This, const type &Source) 
	{
		push_back_range(This, make_sub_range(Source));
	}

	class empty_exception
	{
	};

	static void pop_front_range(type &This, std::size_t SourceSize)
	{
		iterator_range const ThisRange = make_sub_range(This);
		std::ptrdiff_t const ThisSize = ThisRange.size();
		std::ptrdiff_t const NewSize = ThisSize - SourceSize;
		if(NewSize < 0)
		{
			throw empty_exception();
		}
		if(SourceSize == 0)
		{
			return;
		}
		iterator_range CopyRange(ThisRange.begin(), SourceSize);
		//
		for(
			; 
			CopyRange.end() != ThisRange.end(); 
			++CopyRange.begin(), ++CopyRange.end())
		{
			*CopyRange.begin() = *CopyRange.end();
		}
		//
		realloc(This, This, NewSize);
	}

	template<class Range>
	static void pop_front_range(type &This, Range &Source) 
	{
		std::ptrdiff_t const SourceSize = range::size(Source);		
		iterator_range const ThisRange = make_sub_range(This);
		std::ptrdiff_t const ThisSize = ThisRange.size();
		std::ptrdiff_t const NewSize = ThisSize - SourceSize;
		if(NewSize < 0)
		{
			throw empty_exception();
		}
		if(SourceSize == 0)
		{
			return;
		}
		iterator_range CopyRange(ThisRange.begin(), SourceSize);
		range::copy(CopyRange, range::begin(Source));
		//
		for(
			; 
			CopyRange.end() != ThisRange.end(); 
			++CopyRange.begin(), ++CopyRange.end())
		{
			*CopyRange.begin() = *CopyRange.end();
		}
		//
		realloc(This, This, NewSize);
	}

	//using standard_policy_type::output;

	// // use windows::cout instead.
	//static void output(::std::basic_ostream<wchar_t> &S, const type &This)
	//{
	//	if(!This) return;
	//	S << This;
	//}
};

typedef policy::wrap<bstr_t, ::BSTR, bstr_policy> bstr_wrap_internal;

class bstr_wrap: public bstr_wrap_internal
{
public:
	typedef bstr_policy::iterator iterator; 
	typedef bstr_policy::const_iterator const_iterator; 
	bstr_wrap()
	{
	}
	template<class T1, class T2>
	bstr_wrap(T1 const &X1, T2 const &X2):
		bstr_wrap_internal(X1, X2)
	{
	}
};

typedef range::helper_t<
	bstr_t, 
	/*
	bstr_policy::iterator, 
	bstr_policy::const_iterator, 
	*/
	bstr_wrap> bstr_helper;

}

#pragma pack(push, 1)

class bstr_t: public detail::bstr_helper
{
public:

	typedef detail::bstr_helper helper_type;
	typedef detail::bstr_wrap wrap_type;
	typedef wrap_type::internal_policy internal_policy;

	typedef move::t<bstr_t> move_type;

	typedef internal_policy::value_type value_type;
	typedef internal_policy::iterator iterator;
	typedef internal_policy::iterator_range iterator_range;
	typedef internal_policy::const_iterator const_iterator;
	typedef internal_policy::const_iterator_range const_iterator_range;
	typedef iterator_range::size_type size_type; 

	typedef value_type char_type;

	typedef ::BSTR c_in_t;
	typedef ::BSTR *c_out_t;
	typedef ::BSTR *c_in_out_t;

	static bstr_t &cpp_out(c_out_t X)
	{
		*X = 0;
		return cast::traits<bstr_t &>::reinterpret(*X);
	}

	static const vartype_t::enum_t vt = vartype_t::bstr;

	bstr_t() {}

	explicit bstr_t(::std::size_t Size) 
	{
		this->resize(Size);
	}

	bstr_t(const wchar_t *X, ::std::size_t Size): 
		helper_type(const_iterator_range(X, X + Size), 0) 
	{
	}

	template< ::std::size_t Size>
	bstr_t(const wchar_t (&X)[Size]): helper_type(const_iterator_range(X), 0) {}

	template<class Char>
	bstr_t(const range::iterator_range<Char> &X): helper_type(X, 0) {}

	explicit bstr_t(const std::basic_string<wchar_t> &X): 
		helper_type(const_iterator_range(X.c_str(), (size_type)X.size()), 0)
	{
	}

	explicit bstr_t(const base::basic_string<wchar_t> &X): 
		helper_type(const_iterator_range(X.c_str(), (size_type)X.size()), 0)
	{
	}

	bstr_t(const move_type &F) { this->move_assign(*F); }

	bstr_t &operator=(const move_type &F)
	{ 
		this->move_assign(*F); 
		return *this; 
	}

	void move_assign(bstr_t &X)
	{
		this->swap(X);
	}

	const wchar_t *c_str() const { return this->internal(); }

	wchar_t *data() { return this->internal(); }

	size_type size() const 
	{ 
		return (size_type)internal_policy::size(this->internal()); 
	}

	iterator begin() { return this->internal(); }
	iterator end() { return this->internal() + size(); }

	const_iterator begin() const { return this->internal(); }
	const_iterator end() const { return this->internal() + size(); }

	void resize(std::size_t Size)
	{
		internal_policy::resize(this->internal(), Size);
	}

	void clear()
	{
		internal_policy::destroy(this->internal());
		internal_policy::construct(this->internal());
	}

	int compare(const bstr_t &X) const
	{
		return range::lexicographic::compare(*this, X);
	}

	typedef void *extra_result;

	template<class C>
	void push_back_range(const C &c)
	{
		internal_policy::push_back_range(this->internal(), c);
	}

	template<class T>
	bstr_t &operator<<(const T &t)
	{
		::cbear_berlios_de::stream::write(*this, t);
		return *this;
	}

	void pop_front_range(std::size_t S)
	{
		internal_policy::pop_front_range(this->internal(), S);
	}

	template<class C>
	void pop_front_range(C &c)
	{
		internal_policy::pop_front_range(this->internal(), c);
	}

	const_iterator_range get_front_range(std::size_t S)
	{
		return const_iterator_range(this->begin(), ::std::min(this->size(), S));
	}

	template<class T>
	bstr_t &operator>>(T &t)
	{
		::cbear_berlios_de::stream::read(*this, t);
		return *this;
	}
};

#pragma pack(pop)

}
}
}

#endif
