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
#ifndef CBEAR_BERLIOS_DE_META_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_LIST_HPP_INCLUDED

#include <cbear.berlios.de/meta/const.hpp>
#include <cbear.berlios.de/meta/wrap.hpp>
#include <cstddef>

namespace cbear_berlios_de
{
namespace meta
{

//
// not implemented:
//
// boost (http://boost.org)
// 
// begin<v>::type 	
// An iterator pointing to the beginning of v; see Random Access Sequence.
//
// end<v>::type 	
// An iterator pointing to the end of v; see Random Access Sequence.
//

namespace detail
{

class none;

template<class Front = none, class PopFront = none>
class list;

// list base.
template<class Front, class PopFront>
class list_base;

// empty list base.
template<>
class list_base<none, none>
{
public:
	typedef list<> type;
	typedef const_::true_ empty;
	typedef const_::_<std::size_t, 0> size;
	// no front
	// no back
	// no pop_front
	// no pop_back

	template<class Front1>
	class push_front: public list<Front1, type> {};

	template<class Back1>
	class push_back: public list<Back1, type> {};

	// no at_c

	template<std::size_t, class>
	class insert_c;
	template<class X>
	class insert_c<0, X>: public list<X, type> {};

protected:

	// erase_c
	template<std::size_t, std::size_t, class EmptyList = type>
	class erase_c;
	template<class EmptyList>
	class erase_c<0, 0, EmptyList>: public EmptyList {};

	template<class List>
	class push_front_list: public List {};

	template<class List>
	class push_back_list: public List {};

	template<std::size_t, class>
	class insert_list_c;
	template<class List>
	class insert_list_c<0, List>: public List {};
};

// list base of one item.
template<class Front>
class list_base<Front, list<> >
{
public:
	typedef list<Front, list<> > type;
	typedef const_::false_ empty;
	typedef const_::_<std::size_t, 1> size;
	typedef wrap<Front> front;
	typedef wrap<Front> back;
	typedef list<> pop_front;
	typedef list<> pop_back;

	template<class Front1>
	class push_front: public list<Front1, type> {};

	template<class Back1>
	class push_back: public list<Front, list<Back1> > {};

	template<std::size_t>
	class at_c;
	template<>
	class at_c<0>: public wrap<Front> {};

	template<std::size_t, class>
	class insert_c;
	template<class X>
	class insert_c<0, X>: public list<X, type> {};
	template<class X>
	class insert_c<1, X>: public list<Front, list<X> > {};

protected:

	template<std::size_t, std::size_t, class EmptyList = list<> >
	class erase_c;
	template<class EmptyList>
	class erase_c<0, 0, EmptyList>: public type {};
	template<class EmptyList>
	class erase_c<0, 1, EmptyList>: public EmptyList {};
	template<class EmptyList>
	class erase_c<1, 1, EmptyList>: public type {};

	// List::size steps.
	template<class List>
	class push_front_list: public List::template push_back<Front>::type {};

	template<class List>
	class push_back_list: public list<Front, List> {};

	template<std::size_t, class>
	class insert_list_c;
	// List::size steps.
	template<class List>
	class insert_list_c<0, List>: public List::template push_back<Front>::type {};
	template<class List>
	class insert_list_c<1, List>: public list<Front, List> {};
};

// list of two or more items.
template<class Front, class PopFront>
class list_base
{
public:
	typedef list<Front, PopFront> type;
	typedef const_::false_ empty;
	// size steps.
	typedef typename PopFront::size::next size;
	typedef wrap<Front> front;
	// size steps.
	typedef typename PopFront::back back;
	typedef PopFront pop_front;
	// size steps.
	typedef list<Front, typename PopFront::pop_back> pop_back;

	template<class Front1>
	class push_front: public list<Front1, type> {};

	// size steps.
	template<class Back1>
	class push_back: 
		public list<Front, typename PopFront::template push_back<Back1>::type>
	{
	};

	// N steps.
	template<std::size_t N>
	class at_c: public PopFront::template at_c<N - 1> {};
	template<>
	class at_c<0>: public wrap<Front> {};

	// N steps.
	template<std::size_t N, class X>
	class insert_c: 
		public list<Front, typename PopFront::template insert_c<N - 1, X>::type>
	{
	};
	template<class X>
	class insert_c<0, X>: public list<X, type> {};

protected:

	// N2 steps.
	template<std::size_t N1, std::size_t N2>
	class erase_c: 
		public list<
			Front, typename PopFront::template erase_c<N1 - 1, N2 - 1>::type>
	{
	};
	// N2 steps.
	template<std::size_t N2>
	class erase_c<0, N2>: public PopFront::template erase_c<0, N2 - 1>::type {};
	template<>
	class erase_c<0, 0>: public type {};
	template<>
	class erase_c<0, 1>: public PopFront {};

	// L::size steps.
	template<class List>
	class push_front_list: public List::template push_back_list<type>::type {};
	
	// size steps.
	template<class List>
	class push_back_list: 
		public list<Front, typename PopFront::template push_back_list<List>::type> 
	{
	};

	// N + L::size steps.
	template<std::size_t N, class List>
	class insert_list_c: 
		public list<
			Front, typename PopFront::template insert_list_c<N - 1, List>::type>
	{
	};
	// List::size steps.
	template<class List>
	class insert_list_c<0, List>: public List::template push_back_list<type>::type
	{
	};
};

template<class>
class list_cast;
template<class Front, class PopFront>
class list_cast<list<Front, PopFront> >: public wrap<list<Front, PopFront> >
{
};

}

template<class List>
class list_cast: public detail::list_cast<typename List::type> {};

namespace detail
{

// list.
template<class Front, class PopFront>
class list: private list_base<Front, PopFront>
{
private:
	typedef list_base<Front, PopFront> base;
public:

	typedef list type;
	typedef list o; // VC 8.0

	typedef list<> clear;

	// size steps.
	template<class B>
	class x: public base::template push_back<B> {};

	template<class N>
	class at: public base::template at_c<N::value> {};

	template<class N, class X>
	class insert: public base::template insert_c<N::value, X> {};

	template<std::size_t N1, std::size_t N2 = N1 + 1>
	class erase_c: public base::template erase_c<N1, N2> {};

	template<class N1, class N2 = typename N1::next>
	class erase: public base::template erase_c<N1::value, N2::value> {};

	template<class List>
	class push_front_list: 
		public base::template push_front_list<typename list_cast<List>::type>
	{
	};

	template<class List>
	class push_back_list: 
		public base::template push_back_list<typename list_cast<List>::type>
	{
	};

	template<std::size_t N, class List>
	class insert_list_c: 
		public base::template insert_list_c<N, typename list_cast<List>::type>
	{
	};

	template<class N, class List>
	class insert_list: public insert_list_c<N::value, List> {};
};

}

//
// size
// The size of the list.
//
// empty
// A boolean Integral Constant such that empty::value == true if and only if the
// list is empty.
//
// clear
// An empty list.
//
// front
// The first element in the list.
//
// back
// The last element in the list.
//
// pop_front
// A new vector of following elements: [begin::next, end).
//
// pop_back
// A new vector of following elements: [begin, end::prior).
//
// push_front<x>::type 	
// A new vector of following elements: x, [begin, end).
//
// push_back<x>::type 	
// A new vector of following elements: [begin, end), x.
//
// at<n>::type, at_c<N>::type
// The nth element from the beginning of the list.
//
// insert<n, x>::type, insert_c<N, x>::type
// A new list of following elements: 
// [begin, n), x, [n, end).
//
// erase<n>::type, erase_c<N>::type
// A new vector of following elements: 
// [begin, n), [n::next, end).
//
// erase<n1, n2>::type 	
// A new vector of following elements: 
// [begin, n1), [n2, end).
//
// push_front_list<v>::type
//
// push_back_list<v>::type
//
// insert_list<n, v>::type, insert_list_c<n, v>::type
// A new vector of following elements: 
// [begin::type, n), [v::begin, v::end) [n, end).
//
typedef detail::list<> list;

}
}

#endif
