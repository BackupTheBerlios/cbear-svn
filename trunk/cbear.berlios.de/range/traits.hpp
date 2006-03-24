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
#ifndef CBEAR_BERLIOS_DE_RANGE_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_TRAITS_HPP_INCLUDED

#include <cstdlib>

// std::iterator_traits
#include <iterator>

// boost::remove_const
#include <boost/type_traits.hpp>

// cbear_berlios_de::base::undefined
#include <cbear.berlios.de/base/undefined.hpp>
// cbear_berlios_de::base::make_unsigned
#include <cbear.berlios.de/base/integer.hpp>
// cbear_berlios_de::base::is_character
#include <cbear.berlios.de/base/character.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Iterator>
class iterator_range;

namespace detail
{

template<class Container>
struct std_traits_iterator
{
	typedef typename Container::iterator type;
};

template<class Container>
struct std_traits_iterator<const Container>
{
	typedef typename Container::const_iterator type;
};

template<class Container>
struct class_std_traits
{
	typedef Container container;
	typedef typename std_traits_iterator<Container>::type iterator;
	typedef std::iterator_traits<iterator> iterator_traits;
	typedef typename container::reverse_iterator reverse_iterator;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::pointer pointer;
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename base::make_unsigned<difference_type>::type size_type;
	
	static iterator begin(container &X) { return X.begin(); }
	static iterator end(container &X) { return X.end(); }
	
	static bool empty(container &X) { return X.empty(); }
	static size_type size(container &X) { return X.size(); }
	
	static reference front(container &X) { return X.front(); }
	static reference back(container &X) { return X.back(); }
	
	static reference at(container &X, size_type I) { return X.at(I); }
	
	static reverse_iterator rbegin(container &X) { return X.rbegin(); }
	static reverse_iterator rend(container &X) { return X.rend(); }
};

template<class Item, std::size_t RealSize>
struct array_traits
{
	typedef Item container[RealSize];
	typedef Item *iterator;
	typedef Item &reference;
	typedef Item *pointer;
	typedef typename boost::remove_const<Item>::type value_type;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	static const size_type const_size = 
		base::is_character<value_type>::value ? RealSize - 1: RealSize;

	static iterator begin(container &X) { return X; }
	static iterator end(container &X) { return X + const_size; }
	
	static bool empty(container &) { return const_size==0; }
	static size_type size(container &) { return const_size; }
	
	static reference front(container &X) { return X[0]; }
	static reference back(container &X) { return X[const_size - 1]; }
	
	static reference at(container &X, size_type I) { return X[I]; }
	
	static reverse_iterator rbegin(container &X) 
	{ 
		return reverse_iterator(end(X)); 
	}
	
	static reverse_iterator rend(container &X) 
	{ 
		return reverse_iterator(begin(X)); 
	}
};

template<class Container, bool IsClass = boost::is_class<Container>::value>
struct std_traits
{
	typedef Container container;
	typedef base::undefined iterator;
	typedef base::undefined reverse_iterator;
	typedef base::undefined reference;
	typedef base::undefined pointer;
	typedef base::undefined value_type;
	typedef base::undefined difference_type;
	typedef base::undefined size_type;
};

template<class Container>
struct std_traits<Container, true>: class_std_traits<Container>
{
};

}

template<class Container>
struct traits: detail::std_traits<Container> 
{
};

template<class Container>
struct traits<const Container>: detail::std_traits<const Container> 
{
};

template<class Item, std::size_t Size>
struct traits<Item[Size]>: detail::array_traits<Item, Size>
{
};

template<class Item, std::size_t Size>
struct traits<const Item[Size]>: detail::array_traits<const Item, Size>
{
};

template<class Item, std::size_t Size>
struct traits<Item (&)[Size]>: detail::array_traits<Item, Size>
{
};

template<class Item, std::size_t Size>
struct traits<const Item (&)[Size]>: detail::array_traits<const Item, Size>
{
};

// VC 7.1 must die.
template<class T>
struct const_traits: traits<const T> {};

}
}

#endif
