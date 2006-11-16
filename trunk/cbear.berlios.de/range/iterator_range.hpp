#ifndef CBEAR_BERLIOS_DE_RANGE_ITERATOR_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ITERATOR_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/base/initialized.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/range/traits.hpp>
#include <cbear.berlios.de/range/helper.hpp>
#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

namespace detail
{

template<class Iterator>
class iterator_range_base_t
{
public:

	typedef Iterator iterator;
	typedef Iterator const_iterator;

private:
	typedef base::initialized<iterator> initialized_iterator;
	initialized_iterator B, E;
};

}

template<class Iterator>
class iterator_range: 
	// public helper<iterator_range<Iterator>, Iterator, Iterator>
	public helper_t<
		iterator_range<Iterator>, detail::iterator_range_base_t<Iterator> >
{
private:
	typedef helper_t<
		iterator_range<Iterator>, detail::iterator_range_base_t<Iterator> >
		helper_t;
public:
	// typedef helper<iterator_range, Iterator, Iterator> helper_type;
	typedef typename helper_t::size_type size_type;
	typedef typename helper_t::value_type value_type;
	
	iterator_range() {}
	
	typedef Iterator iterator;
	typedef Iterator const_iterator;
	
	iterator_range(const iterator &B, const iterator &E): 
		B(B),
		E(E)
	{
	}

	iterator_range(const iterator &B, const size_type &Size):
		B(B), 
		E(B + Size)
	{
	}

	iterator &begin() throw() { return *this->B; }
	iterator &end() throw() { return *this->E; }

	const iterator &begin() const throw() { return *this->B; }
	const iterator &end() const throw() { return *this->E; }

	template<class Range>
	explicit iterator_range(Range &R): 
		B(range::begin(R)), 
		E(range::end(R))
	{
	}
	
	template<class Range>
	explicit iterator_range(const Range &R): 
		B(range::begin(R)), 
		E(range::end(R))
	{
	}

	template<class T>
	void swap(T &x)
	{
		BOOST_STATIC_ASSERT((::boost::is_same<T, iterator_range>::value));
		base::swap(this->B, x.B);
		base::swap(this->E, x.E);
	}

private:

	typedef base::initialized<iterator> initialized_iterator;
	
	initialized_iterator B, E;
};

template<class Iterator>
iterator_range<Iterator> make_iterator_range(
	const Iterator &B, const Iterator &E)
{
	return iterator_range<Iterator>(B, E);
}

template<class Iterator, class SizeType>
iterator_range<Iterator> make_iterator_range(
	const Iterator &B, const SizeType &Size)
{
	return iterator_range<Iterator>(B, Size);
}

template<class Iterator>
iterator_range<Iterator> make_iterator_range(
	const std::pair<Iterator, Iterator> &P)
{
	return iterator_range<Iterator>(P);
}

template<class Range>
iterator_range<typename iterator<Range>::type> make_iterator_range(
	Range &R)
{
	return iterator_range<typename iterator<Range>::type>(R);
}

template<class Range>
iterator_range<typename iterator<const Range>::type> make_iterator_range(
	const Range &R)
{
	return iterator_range<typename iterator<const Range>::type>(R);
}

}
}

#endif
