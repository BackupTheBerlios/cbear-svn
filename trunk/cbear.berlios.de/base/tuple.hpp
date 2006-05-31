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

template<class List = meta::list>
class tuple;

namespace detail
{

// size steps.
template<class List, std::size_t Size = List::size::value>
class tuple
{
public:

	// front
	typedef typename List::front::type front_t;
	front_t &front() { return this->Front; }
	const front_t &front() const { return this->Front; }

	// back
	typedef typename List::back::type back_t;	
	back_t &back() { return this->PopFront.back(); }
	const back_t &back() const { return this->PopFront.back(); }

	// pop_front
	typedef typename base::tuple<typename List::pop_front> pop_front_t;
	pop_front_t pop_front() const { return this->PopFront; }

	// pop_back
	typedef typename base::tuple<typename List::pop_back> pop_back_t;
	pop_back_t pop_back() const 
	{ 
		return pop_back_t(Front, this->PopFront.pop_back()); 
	}

	// push_front
	template<class Front1>
	class push_front_t: 
		public base::tuple<typename List::template push_front<Front1>::type> 
	{
	};
	template<class Front1>
	typename push_front_t<Front1>::type push_front(const Front1 &Value) const
	{
		return push_front_t<Front1>::type(Value, *this);
	}

	// push_back
	template<class Back1>
	class push_back_t:
		public base::tuple<typename List::template push_back<Back1>::type>
	{
	};
	template<class Back1>
	typename push_back_t<Back1>::type push_back(const Back1 &Value) const
	{
		return push_back_t<Back1>::type(
			this->Front, this->PopFront.push_back(Value));
	}

	// at_c
	template<std::size_t N>
	class at_c_t: public base::tuple<typename List::template at_c<N>::type> {};
	template<std::size_t N>
	typename at_c_t<N>::type &at_c() 
	{ 
		return this->PopFront.at_c<N - 1>(); 
	}
	template<>
	typename at_c_t<0>::type &at_c<0>() 
	{ 
		return this->Front; 
	}
	template<std::size_t N>
	typename const at_c_t<N>::type &at_c() const 
	{ 
		return this->PopFront.at_c<N - 1>(); 
	}
	template<>
	typename const at_c_t<0>::type &at_c<0>() const 
	{ 
		return this->Front; 
	}

	// insert_c
	template<std::size_t N, class Value>
	class insert_c_t: 
		public base::tuple<typename List::template insert_c<N, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<N, Value>::type> type;
		static type make(const tuple &This, const Value &V)
		{
			return type(
				This.Front, This.PopFront.template insert_c<N - 1, Value>(V));
		}
	};
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename List::template insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<0, Value>::type> type;
		static type make(const tuple &This, const Value &V)
		{
			return type(V, This);
		}
	};

	// constructor
	tuple(
		const front_t &Front = front_t(),
		const pop_front_t &PopFront = pop_front_t()):
		Front(Front), PopFront(PopFront)
	{
	}

private:
	front_t Front;
	pop_front_t PopFront;
};

// one item tuple.
template<class List>
class tuple<List, 1>
{
public:

	// front
	typedef typename List::front::type front_t;
	front_t &front() { return this->Front; }
	const front_t &front() const { return this->Front; }

	// back
	typedef typename List::back::type back_t;
	back_t &back() { return this->Front; }
	const back_t &back() const { return this->Front; }

	// pop_front
	typedef base::tuple<typename List::pop_front> pop_front_t;
	static pop_front_t pop_front() { return pop_front_t(); }

	// pop_back
	typedef base::tuple<typename List::pop_back> pop_back_t;
	static pop_back_t pop_back() { return pop_back_t(); }

	// push_front
	template<class Front1>
	class push_front_t: 
		public base::tuple<typename List::template push_front<Front1>::type>
	{
	};
	template<class Front1>
	typename push_front_t<Front1>::type push_front(const Front1 &Value) const
	{
		return push_front_t<Front1>::type(Value, *this);
	}

	// push_back
	template<class Back1>
	class push_back_t: 
		public base::tuple<typename List::template push_back<Back1>::type>
	{
	};
	template<class Back1>
	typename push_back_t<Back1>::type push_back(const Back1 &Value) const
	{
		return push_back_t<Back1>::type(
			this->Front, pop_front_t().push_back(Value));
	}

	// at_c
	template<std::size_t N>
	class at_c_t: public base::tuple<typename List::template at_c<N>::type> {};
	template<std::size_t N>
	typename at_c_t<N>::type &at_c();
	template<>
	typename at_c_t<0>::type &at_c<0>() { return this->Front; }
	template<std::size_t N>
	typename const at_c_t<N>::type &at_c() const;
	template<>
	typename const at_c_t<0>::type &at_c<0>() const { return this->Front; }

	// insert_c
	template<std::size_t N, class Value>
	class insert_c_t: 
		public base::tuple<typename List::template insert_c<N, Value>::type>
	{
	};
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename List::template insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<0, Value>::type> type;
		static type make(const tuple &This, const Value &V) 
		{
			return type(V, This);
		}
	};
	template<class Value>
	class insert_c_t<1, Value>: 
		public base::tuple<typename List::template insert_c<1, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<1, Value>::type> type;
		static type make(const tuple &This, const Value &V)
		{
			return type(This.Front, pop_front_t().template insert_c<1>(V));
		}
	};

protected:

	// erase_c
	template<std::size_t N1, std::size_t N2>
	class erase_c_t: 
		public base::tuple<typename List::template erase_c<N1, N2>::type>
	{
	};
	template<std::size_t N1, std::size_t N2>
	typename erase_c_t<N1, N2>::type erase_c() const;
	template<>
	typename erase_c_t<0, 0>::type erase_c() const 
	{ 
		return *this; 
	}
	template<>
	typename erase_c_t<0, 1>::type erase_c() const 
	{ 
		return erase_c_t<0, 1>::type(); 
	}
	template<>
	typename erase_c_t<1, 1>::type erase_c() const 
	{ 
		return *this; 
	}

public:

	// constructor
	tuple(
		const front_t &Front = front_t(), 
		const pop_front_t & = pop_front_t()): 
		Front(Front) 
	{
	}

private:
	front_t Front;
};

// empty tuple.
template<>
class tuple<meta::list, 0> 
{
public:

	// no front
	// no back
	// no pop_front
	// no pop_back

	// push_front
	template<class Front1>
	class push_front_t:
		public base::tuple<typename meta::list::push_front<Front1>::type>
	{
	};
	template<class Front1>
	static typename push_front_t<Front1>::type push_front(const Front1 &Value)
	{
		return push_front_t<Front1>::type(Value);
	}

	// push_back
	template<class Back1>
	class push_back_t: 
		public base::tuple<typename meta::list::push_back<Back1>::type>
	{
	};
	template<class Back1>
	static typename push_back_t<Back1>::type push_back(const Back1 &Value)
	{
		return push_back_t<Back1>::type(Value);
	}

	// no at_c

	// insert_c
	template<std::size_t N, class Value>
	class insert_c_t: 
		public base::tuple<typename meta::list::insert_c<N, Value>::type>
	{
	};
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename meta::list::insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename meta::list::insert_c<0, Value>::type> type;
		static type make(const tuple &, const Value &V) { return type(V); }
	};

protected:

	// no erase_c
};

}

//
template<class List>
class tuple: public detail::tuple<typename meta::list_cast<List>::type>
{
public:
	typedef typename meta::list_cast<List>::type list_t;
private:
	typedef detail::tuple<list_t> base_t;
public:
	typedef tuple type;

	// empty
	typedef typename list_t::empty empty_const;
	static bool empty() { return empty_const::value; }

	// size
	typedef typename list_t::size size_const;
	static std::size_t size() { return size_const::value; }

	// <<
	template<class Back1>
	class x: public base_t::template push_back_t<Back1> {};
	template<class Back1>
	typename x<Back1>::type operator<<(const Back1 &Value) const
	{
		return this->base_t::push_back(Value);
	}

	// clear
	typedef tuple<> clear_t;
	static clear_t clear() { return tuple<>(); }

	// []
	template<class N>
	class at_t: public base_t::template at_c<N::value> {};
	template<class N>
	typename at_t<N>::type &operator[](N) 
	{ 
		return this->base_t::at_c<N::value>(); 
	}
	template<class N>
	typename const at_t<N>::type &operator[](N) const 
	{ 
		return this->base_t::at_c<N::value>(); 
	}

	// insert
	template<std::size_t N, class Value>
	class insert_c_t: public base_t::template insert_c_t<N, Value>::type {};
	template<std::size_t N, class Value>
	typename insert_c_t<N, Value>::type insert_c(const Value &V) const
	{
		return insert_c_t<N, Value>::make(*this, V);
	}
	template<class N, class Value>
	class insert_t: public insert_c_t<N::value, Value> {};
	template<class N, class Value>
	typename insert_t<N, Value>::type insert(N, const Value &V) const
	{
		return this->insert_c<N::value, Value>(V);
	}
};

}
}

#endif
