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

	typedef base::tuple<List> type;

	// front
public:
	typedef typename List::front::type front_t;
	front_t &front() { return this->Front; }
	const front_t &front() const { return this->Front; }

	// back
public:
	typedef typename List::back::type back_t;	
	back_t &back() { return this->PopFront.back(); }
	const back_t &back() const { return this->PopFront.back(); }

	// pop_front
public:
	typedef typename base::tuple<typename List::pop_front> pop_front_t;
	pop_front_t pop_front() const { return this->PopFront; }

	// pop_back
public:
	typedef typename base::tuple<typename List::pop_back> pop_back_t;
	pop_back_t pop_back() const 
	{ 
		return pop_back_t(Front, this->PopFront.pop_back()); 
	}

	// push_front
public:
	template<class Front1>
	class push_front_t: 
		public base::tuple<typename List::template push_front<Front1>::type> 
	{
	};
	template<class Front1>
	typename push_front_t<Front1>::type push_front(const Front1 &Value) const
	{
		return push_front_t<Front1>::type(Value, this->This());
	}

	// push_back
public:
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
public:
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
public:
	template<std::size_t N, class Value>
	class insert_c_t: 
		public base::tuple<typename List::template insert_c<N, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<N, Value>::type> 
			result_t;
		static result_t make(const type &This, const Value &V)
		{
			return result_t(
				This.Front, This.PopFront.template insert_c<N - 1, Value>(V));
		}
	};
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename List::template insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<0, Value>::type> 
			result_t;
		static result_t make(const type &This, const Value &V)
		{
			return result_t(V, This);
		}
	};

	// erase_c
protected:
	template<std::size_t N1, std::size_t N2>
	class erase_c_t: 
		public base::tuple<typename List::template erase_c<N1, N2>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<N1, N2>::type> result_t;
		static result_t make(const type &This)
		{
			return result_t(
				This.Front, This.PopFront.template erase_c<N1 - 1, N2 - 1>());
		}
	};
	template<std::size_t N2>
	class erase_c_t<0, N2>:
		public base::tuple<typename List::template erase_c<0, N2>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<0, N2>::type> result_t;
		static result_t make(const type &This)
		{
			return This.PopFront.template erase_c<0, N2 - 1>();
		}
	};
	template<>
	class erase_c_t<0, 0>:
		public base::tuple<typename List::template erase_c<0, 0>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<0, 0>::type> result_t;
		static result_t make(const type &This)
		{
			return This;
		}
	};

	// push_front_tuple
protected:
	template<class Tuple>
	class push_front_tuple_t: 
		public base::tuple<
			typename List::template push_front_list<typename Tuple::list_t>::type>
	{
	};
public:
	template<class Tuple>
	typename push_front_tuple_t<Tuple>::type 
	push_front_tuple(const Tuple &V) const
	{
		return V.push_back_tuple(this->This());
	}

	// push_back_tuple
protected:
	template<class Tuple>
	class push_back_tuple_t: 
		public base::tuple<
			typename List::template push_back_list<typename Tuple::list_t>::type>
	{
	};
public:
	template<class Tuple>
	typename push_back_tuple_t<Tuple>::type 
	push_back_tuple(const Tuple &V) const
	{
		return push_back_tuple_t<Tuple>::type(
			this->Front, this->PopFront::template push_back_tuple(V));
	}

	// constructor
public:
	tuple(
		const front_t &Front = front_t(),
		const pop_front_t &PopFront = pop_front_t()):
		Front(Front), PopFront(PopFront)
	{
	}

	// internal members
private:
	front_t Front;
	pop_front_t PopFront;
	type &This() { return *static_cast<type*>(this); }
	const type &This() const { return *static_cast<const type*>(this); }
};

// one item tuple.
template<class List>
class tuple<List, 1>
{
public:

	typedef base::tuple<List> type;

	// front
public:
	typedef typename List::front::type front_t;
	front_t &front() { return this->Front; }
	const front_t &front() const { return this->Front; }

	// back
public:
	typedef typename List::back::type back_t;
	back_t &back() { return this->Front; }
	const back_t &back() const { return this->Front; }

	// pop_front
public:
	typedef base::tuple<typename List::pop_front> pop_front_t;
	static pop_front_t pop_front() { return pop_front_t(); }

	// pop_back
public:
	typedef base::tuple<typename List::pop_back> pop_back_t;
	static pop_back_t pop_back() { return pop_back_t(); }

	// push_front
public:
	template<class Front1>
	class push_front_t: 
		public base::tuple<typename List::template push_front<Front1>::type>
	{
	};
	template<class Front1>
	typename push_front_t<Front1>::type push_front(const Front1 &Value) const
	{
		return push_front_t<Front1>::type(Value, this->This());
	}

	// push_back
public:
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
public:
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
public:
	template<std::size_t N, class Value>
	class insert_c_t;
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename List::template insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<0, Value>::type> 
			result_t;
		static result_t make(const type &This, const Value &V) 
		{
			return result_t(V, This);
		}
	};
	template<class Value>
	class insert_c_t<1, Value>: 
		public base::tuple<typename List::template insert_c<1, Value>::type>
	{
	public:
		typedef base::tuple<typename List::template insert_c<1, Value>::type> 
			result_t;
		static result_t make(const type &This, const Value &V)
		{
			return result_t(This.Front, pop_front_t().template insert_c<1>(V));
		}
	};

	// erase_c
protected:
	template<std::size_t N1, std::size_t N2>
	class erase_c_t;
	template<>
	class erase_c_t<0, 0>:
		public base::tuple<typename List::template erase_c<0, 0>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<0, 0>::type> result_t;
		static result_t make(const type &This)
		{
			return this->This();
		}
	};
	template<>
	class erase_c_t<0, 1>:
		public base::tuple<typename List::template erase_c<0, 1>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<0, 1>::type> result_t;
		static result_t make(const type &)
		{
			return result_t();
		}
	};
	template<>
	class erase_c_t<1, 1>:
		public base::tuple<typename List::template erase_c<1, 1>::type>
	{
	public:
		typedef base::tuple<typename List::template erase_c<1, 1>::type> result_t;
		static result_t make(const type &This)
		{
			return this->This();
		}
	};

	// push_front_tuple
protected:
	template<class Tuple>
	class push_front_tuple_t: 
		public base::tuple<
			typename List::template push_front_list<typename Tuple::list_t>::type>
	{
	};
public:
	template<class Tuple>
	typename push_front_tuple_t<Tuple>::type 
	push_front_tuple(const Tuple &V) const
	{
		return V.push_back(this->Front);
	}

	// push_back_tuple
protected:
	template<class Tuple>
	class push_back_tuple_t:
		public base::tuple<
			typename List::template push_back_list<typename Tuple::list_t>::type>
	{
	};
public:
	template<class Tuple>
	typename push_back_tuple_t<Tuple>::type 
	push_back_tuple(const Tuple &V) const
	{
		return push_back_tuple_t<Tuple>::type(this->Front, V);
	}

	// constructor
public:
	tuple(
		const front_t &Front = front_t(), 
		const pop_front_t & = pop_front_t()): 
		Front(Front) 
	{
	}

	// internal members
private:
	front_t Front;
	type &This() { return *static_cast<type*>(this); }
	const type &This() const { return *static_cast<const type*>(this); }
};

// empty tuple.
template<>
class tuple<meta::list, 0> 
{
	// no front
	// no back
	// no pop_front
	// no pop_back

	// push_front
public:
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
public:
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
public:
	template<std::size_t N, class Value>
	class insert_c_t;
	template<class Value>
	class insert_c_t<0, Value>: 
		public base::tuple<typename meta::list::insert_c<0, Value>::type>
	{
	public:
		typedef base::tuple<typename meta::list::insert_c<0, Value>::type> result_t;
		static result_t make(const meta::list &, const Value &V) 
		{ 
			return result_t(V); 
		}
	};

	// no erase_c

	// push_front_tuple
protected:
	template<class Tuple>
	class push_front_tuple_t: public Tuple {};
public:
	template<class Tuple>
	static Tuple push_front_tuple(const Tuple &V) { return V; }

	// push_back_tuple
protected:
	template<class Tuple>
	class push_back_tuple_t: public Tuple {};
public:
	template<class Tuple>
	static Tuple push_back_tuple(const Tuple &V) { return V; }
};

template<class Tuple>
class tuple_cast;

template<class List>
class tuple_cast<base::tuple<List> >: public base::tuple<List> {};

}

template<class Tuple>
class tuple_cast: public detail::tuple_cast<typename Tuple::type> {};

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

	// insert, insert_c
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

	// erase, erase_c
	template<std::size_t N1, std::size_t N2 = N1 + 1>
	class erase_c_t: public base_t::template erase_c_t<N1, N2>::type {};
	template<std::size_t N1, std::size_t N2 = N1 + 1>
	typename erase_c_t<N1, N2>::type erase_c() const
	{
		return erase_c_t<N1, N2>::make(*this);
	}
	template<class N1, class N2 = typename N1::next>
	class erase_t: public erase_c_t<N1::value, N2::value> {};
	template<class N1, class N2>
	typename erase_t<N1, N2>::type erase(N1, N2) const
	{
		return erase_t<N1, N2>::make(*this);
	}
	template<class N1>
	typename erase_t<N1>::type erase(N1) const
	{
		return erase_t<N1>::make(*this);
	}

	// push_front_tuple_t
	template<class Tuple>
	class push_front_tuple_t: 
		public base_t::template push_front_tuple_t<typename tuple_cast<Tuple>::type>
	{
	};
	// push_back_tuple_t
	template<class Tuple>
	class push_back_tuple_t: 
		public base_t::template push_back_tuple_t<typename tuple_cast<Tuple>::type>
	{
	};
};

}
}

#endif
