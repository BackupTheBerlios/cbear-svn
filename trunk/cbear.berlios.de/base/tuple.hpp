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
#ifndef CBEAR_BERLIOS_DE_META_TUPLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_TUPLE_HPP_INCLUDED

#include <cbear.berlios.de/meta/list.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class List>
class tuple;

namespace detail
{

template<class List>
class tuple
{
public:

	typedef typename List::front::type front_type;

	front_type &front() { return this->Front; }
	const front_type &front() const { return this->Front; }

	typedef typename List::back::type back_type;	

	// size steps.
	typedef typename base::tuple<List::pop_front> pop_front_type;

	tuple(
		const front_type &Front = front_type(),
		const pop_front_type &PopFront = pop_front_type()):
		Front(Front), PopFront(PopFront)
	{
	}
private:
	front_type Front;
	pop_front_type PopFront;
};

template<>
class tuple<meta::list> 
{
public:

	template<class Back1>
	class push_back_type: 
		public base::tuple<typename meta::list::push_back<Back1>::type>
	{
	};

	template<class Back1>
	typename push_back_type<Back1>::type push_back(const Back1 &Value) const
	{
		return push_back_type<Back1>::type(Value);
	}

	template<class Back1>
	typename push_back_type<Back1>::type operator,(const Back1 &Value) const
	{
		return push_back_type<Back1>::type(Value);
	}
};

}

template<class List>
class tuple: public detail::tuple<typename meta::list_cast<List>::type>
{
public:
	typedef tuple type;
};

}
}

#endif
