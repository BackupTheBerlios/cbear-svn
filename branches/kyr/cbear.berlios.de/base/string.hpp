#ifndef CBEAR_BERLIOS_DE_BASE_STRING_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_STRING_HPP_INCLUDED

#include <string>

#include <boost/type_traits/is_same.hpp>

#include <cbear.berlios.de/range/value_type.hpp>
#include <cbear.berlios.de/range/size_type.hpp>
#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>
#include <cbear.berlios.de/base/swap.hpp>
#include <cbear.berlios.de/move/main.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class ValueType>
class basic_string: private std::basic_string<ValueType>
{
public:

	typedef ValueType value_type;

private:

	typedef std::basic_string<value_type> base_type;

	class container
	{
	public:
		template<class C>
		class has_same_value_type: public boost::is_same<
			value_type, typename range::value_type<const C>::type>
		{
		};

		template<class C>
		static typename range::iterator<const C>::type begin(const C &X) 
		{ 
			BOOST_STATIC_ASSERT(has_same_value_type<C>::value);
			return range::begin(X); 
		}
		template<class C>
		static typename range::iterator<const C>::type end(const C &X)
		{
			BOOST_STATIC_ASSERT(has_same_value_type<C>::value);
			return range::end(X);
		}
		template<class C>
		static typename range::size_type<const C>::type size(const C &X)
		{
			BOOST_STATIC_ASSERT(has_same_value_type<C>::value);
			return range::size(X);
		}

		static const value_type *begin(const value_type &X) { return &X; }
		static const value_type *end(const value_type &X) { return &X + 1; }
		static std::size_t size(const value_type &) { return 1; }
	};

public:

	typedef typename base_type::iterator iterator;
	typedef typename base_type::const_iterator const_iterator;
	typedef typename base_type::reverse_iterator reverse_iterator;

	using base_type::c_str;
	using base_type::begin;
	using base_type::end;
	using base_type::size;
	using base_type::data;

	void swap(basic_string &S)
	{
		this->base_type::swap(S);
	}

	typedef typename base_type::size_type size_type;
	typedef typename base_type::iterator iterator;

	template<class Container>
	basic_string &assign(const Container &C)
	{
		this->base_type::assign(container::begin(C), container::end(C));
		return *this;
	}

	void move_assign(basic_string &F)
	{
		this->swap(F);
	}

	template<class Container>
	basic_string &push_back_range(const Container &C)
	{
		this->base_type::append(container::begin(C), container::end(C));
		return *this;
	}

	template<class Container>
	basic_string &insert(size_type P, const Container &C)
	{
		this->base_type::insert(P, container::begin(C), container::end(C));
		return *this;
	}

	template<class Container>
	basic_string &insert(iterator I, const Container &C)
	{
		this->base_type::insert(I, container::begin(C), container::end(C));
		return *this;
	}

	template<class Container>
	basic_string &replace(size_type P, const Container &C)
	{
		this->base_type::replace(P, container::begin(C), container::end(C));
		return *this;
	}

	template<class Container>
	basic_string &replace(iterator I, const Container &C)
	{
		this->base_type::replace(I, container::begin(C), container::end(C));
		return *this;
	}

	template<class Container>
	size_type find(const Container &C, size_type P = 0) const
	{
		return this->base_type::find(
			container::begin(C), container::size(C), P);
	}

	template<class Container>
	size_type rfind(const Container &C, size_type P = 0) const
	{
		return this->base_type::rfind(
			container::begin(C), container::size(C), P);
	}

	template<class Container>
	size_type find_first_of(const basic_string& C, size_type P = 0) const
	{
		return this->base_type::find_first_of(
			container::begin(C), container::size(C), P);
	}

	template<class Container>
	size_type find_last_of(const basic_string& C, size_type P = 0) const
	{
		return this->base_type::find_last_of(
			container::begin(C), container::size(C), P);
	}

	template<class Container>
	size_type find_first_not_of(const basic_string& C, size_type P = 0) const
	{
		return this->base_type::find_first_not_of(
			container::begin(C), container::size(C), P);
	}

	template<class Container>
	size_type find_last_not_of(const basic_string& C, size_type P = 0) const
	{
		return this->base_type::find_last_not_of(
			container::begin(C), container::size(C), P);
	}

	basic_string substr(size_type pos = 0, size_type n = base_type::npos) const
	{
		size_type Size = this->size();
		if(pos >= Size) return basic_string();
		const_iterator B = this->begin() + pos;
		return basic_string(range::make_iterator_range(
			B, B + std::min(n, Size - pos)));
	}

	template<class Container>
	int compare(size_type pos, size_type n, const Container& C) const
	{
		return this->base_type::compare(
			pos, n, container::begin(C), container::size(C));
	}

	template<class Container>
	int compare(const Container& C) const
	{
		return this->compare(0, base_type::npos, C);
	}

	typedef move::t<basic_string> move_type;

	basic_string() {}

	basic_string(const move_type &M) 
	{ 
		this->move_assign(*M); 
	}

	template<class Container>
	basic_string(const Container &C) 
	{ 
		this->assign(C); 
	}

	template<class Container>
	basic_string &operator=(const Container &C) 
	{ 
		return this->assign(C); 
	}

	basic_string &operator=(const move_type &C) 
	{ 
		C.swap(*this); 
		return *this; 
	}

	template<class Container>
	basic_string &operator+=(const Container &C) 
	{ 
		return this->append(C); 
	}

	/*
	template<class Container>
	void push_back(const Container &c)
	{
		this->append(c);
	}
	*/

	template<class T>
	basic_string &operator<<(const T &t)
	{
		stream::write(*this, t);
		return *this;
	}
};

template<class Char>
basic_string<Char> operator+(
	const basic_string<Char> &A, const basic_string<Char> &B)
{
	basic_string<Char> Result(A);
	Result.push_back_range(B);
	return Result;
}

template<class Char, class Container>
basic_string<Char> operator+(const basic_string<Char> &A, const Container &B)
{
	basic_string<Char> Result(A);
	Result.push_back_range(B);
	return Result;
}

template<class Char, class Container>
basic_string<Char> operator+(const Container &A, const basic_string<Char> &B)
{
	basic_string<Char> Result(A);
	Result.push_back_range(B);
	return Result;
}

template<class Char>
bool operator==(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) == 0;
}

template<class Char>
bool operator!=(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) != 0;
}

template<class Char, class Container>
bool operator==(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) == 0;
}

template<class Char, class Container>
bool operator!=(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) != 0;
}

template<class Char, class Container>
bool operator==(const Container &A, const basic_string<Char> &B)
{
	return B.compare(A) == 0;
}

template<class Char, class Container>
bool operator!=(const Container &A, const basic_string<Char> &B)
{
	return B.compare(A) != 0;
}

template<class Char>
bool operator<(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) < 0;
}

template<class Char>
bool operator>(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) > 0;
}

template<class Char>
bool operator<=(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) <= 0;
}

template<class Char>
bool operator>=(const basic_string<Char> &A, const basic_string<Char> &B)
{
	return A.compare(B) >= 0;
}

template<class Char, class Container>
bool operator<(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) < 0;
}

template<class Char, class Container>
bool operator>(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) > 0;
}

template<class Char, class Container>
bool operator<=(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) <= 0;
}

template<class Char, class Container>
bool operator>=(const basic_string<Char> &A, const Container &B)
{
	return A.compare(B) >= 0;
}

template<class Char>
void swap(basic_string<Char> &A, basic_string<Char> &B) { A.swap(B); }

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;

}
}

#endif
