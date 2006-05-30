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

namespace cbear_berlios_de
{
namespace meta
{

// boost (http://boost.org)
// 
// begin<v>::type 	
// An iterator pointing to the beginning of v; see Random Access Sequence.
//
// end<v>::type 	
// An iterator pointing to the end of v; see Random Access Sequence.
//
// at<v,n>::type 	
// The nth element from the beginning of v; see Random Access Sequence.
//
// insert<v,pos,x>::type 	
// A new vector of following elements: 
// [begin<v>::type, pos), x, [pos, end<v>::type); see Extensible Sequence.
//
// insert_range<v,pos,r>::type 	A new vector of following elements: 
// [begin<v>::type, pos), [begin<r>::type, end<r>::type) [pos, end<v>::type); 
// see Extensible Sequence.
//
// erase<v,pos>::type 	
// A new vector of following elements: 
// [begin<v>::type, pos), [next<pos>::type, end<v>::type); 
// see Extensible Sequence.
//
// erase<v,pos,last>::type 	
// A new vector of following elements: 
// [begin<v>::type, pos), [last, end<v>::type); see Extensible Sequence.
//
// push_back<v,x>::type 	
// A new vector of following elements: [begin<v>::type, end<v>::type), x; 
// see Back Extensible Sequence.
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
	typedef const_::true_ empty;
	typedef const_::_<std::size_t, 0> size;
	// no front
	// no back
	// no pop_front
	// no pop_back

	template<class Front1>
	class push_front: public list<Front1, list<> > {};
};

// list base of one item.
template<class Front>
class list_base<Front, list<> >
{
public:
	typedef const_::false_ empty;
	typedef const_::_<std::size_t, 1> size;
	typedef wrap<Front> front;
	typedef wrap<Front> back;
	typedef empty_list pop_front;
	typedef empty_list pop_back;

	template<class Front1>
	class push_front: public list<Front1, list<Front> > {};
};

// list of two or more items.
template<class Front, class Second, class PopFront2>
class list_base<Front, list<Second, PopFront2> >
{
private:
	typedef list<Second, PopFront2> PopFront;
public:
	typedef const_::false_ empty;
	// N steps.
	typedef typename PopFront::size::next size;
	typedef wrap<Front> front;
	// N steps.
	typedef typename PopFront::back back;
	typedef PopFront pop_front;
	// N steps.
	typedef list<Front, typename PopFront::pop_back> pop_back;

	template<class Front1>
	class push_front: public list<Front1, list<Front, PopFront> > {};	
};

// list.
template<class Front, class PopFront>
class list: private list_base<Front, PopFront>
{
public:

	typedef list type;
	typedef list o; // VC 8.0

	typedef list<> clear;
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
typedef detail::list<> list;

}
}

#endif
