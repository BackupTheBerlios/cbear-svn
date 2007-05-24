#ifndef CBEAR_BERLIOS_DE_RANGE_FILL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_FILL_HPP_INCLUDED

#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>
#include <cbear.berlios.de/range/helper.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class T>
void fill(Container &X, T const &Value) 
{ 
	::std::fill(range::begin(X), range::end(X), Value);
}

template<class T>
class fill_iterator_t
{
public:
	typedef ::std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef ::std::ptrdiff_t difference_type;
	typedef T const *pointer;
	typedef T const &reference;
	fill_iterator_t(T const &V, difference_type I):
		V(V), I(I)
	{
	}
	T const &operator*() const
	{
		return this->V;
	}
	bool operator==(fill_iterator_t const &B) const
	{
		return this->I == B.I;
	}
	bool operator!=(fill_iterator_t const &B) const
	{
		return this->I != B.I;
	}
	fill_iterator_t &operator++()
	{
		++this->I;
		return *this;
	}
	bool operator<(fill_iterator_t const &B) const
	{
		return this->I < B.I;
	}
	difference_type operator-(fill_iterator_t const &B) const
	{
		return this->I - B.I;
	}
	fill_iterator_t &operator+=(difference_type d)
	{
		this->I += d;
		return *this;
	}
	fill_iterator_t operator+(difference_type d) const
	{
		fill_iterator_t t(*this);
		t += d;
		return t;
	}
private:
	T const &V;
	difference_type I;
	fill_iterator_t &operator=(fill_iterator_t const &);
};

namespace detail
{

template<class T>
class fill_base_t
{
public:
	typedef fill_iterator_t<T> iterator;
	typedef iterator const_iterator;
};

}

template<class T>
class fill_t:
	public helper_t<fill_t<T>, detail::fill_base_t<T> >
{
public:

	typedef fill_iterator_t<T> const_iterator;
	typedef typename const_iterator::difference_type difference_type;

	fill_t(T const &V, difference_type Size):
		End(V, Size)
	{
	}

	const_iterator begin() const
	{
		return const_iterator(*this->End, 0);
	}

	const_iterator end() const
	{
		return this->End;
	}

private:
	const_iterator End;
	fill_t &operator=(fill_t const &);
};

template<class T>
fill_t<T> make_fill(T const &V, std::size_t Size)
{
	return fill_t<T>(V, Size);
}

}
}

#endif
