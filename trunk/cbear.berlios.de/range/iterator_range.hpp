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
#ifndef CBEAR_BERLIOS_DE_RANGE_ITERATOR_RANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ITERATOR_RANGE_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/range/traits.hpp>
#include <cbear.berlios.de/range/helper.hpp>
#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Iterator>
class iterator_range;

namespace detail
{

template<class Iterator>
struct iterator_range_traits
{
	typedef iterator_range<Iterator> type;
	typedef std::pair<Iterator, Iterator> internal_type;
	typedef policy::wrap<type, internal_type> wrap_type;
	typedef helper<type, Iterator, Iterator> helper_type;
};

}

template<class Iterator>
class iterator_range: 
	public detail::iterator_range_traits<Iterator>::wrap_type,
	public detail::iterator_range_traits<Iterator>::helper_type
{
public:
	typedef typename detail::iterator_range_traits<Iterator>::wrap_type wrap_type;
	typedef typename wrap_type::internal_type internal_type;
	typedef typename detail::iterator_range_traits<Iterator>::helper_type 
		helper_type;
	typedef typename helper_type::size_type size_type;
	typedef typename helper_type::value_type value_type;
	
	iterator_range() {}
	explicit iterator_range(const internal_type &X): wrap_type(X) {}
	
	typedef Iterator iterator;
	typedef Iterator const_iterator;
	
	iterator_range(const iterator &Begin, const iterator &End): 
		wrap_type(internal_type(Begin, End)) 
	{
	}

	iterator_range(const iterator &Begin, const size_type &Size):
		wrap_type(internal_type(Begin, Begin + Size))
	{
	}

	iterator &begin() { return this->internal().first; }
	iterator &end() { return this->internal().second; }

	const iterator &begin() const { return this->internal().first; }
	const iterator &end() const { return this->internal().second; }

	template<class Range>
	explicit iterator_range(Range &R): 
		wrap_type(internal_type(iterator(range::begin(R)), iterator(range::end(R)))) 
	{
	}
	
	template<class Range>
	explicit iterator_range(const Range &R): 
		wrap_type(internal_type(iterator(range::begin(R)), iterator(range::end(R))))
	{
	}

	template<class Stream>
	typename boost::enable_if<boost::is_same<
		value_type, typename Stream::value_type> >::type
	write(Stream &S) const
	{
		S.push_back_range(*this);
	}
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
