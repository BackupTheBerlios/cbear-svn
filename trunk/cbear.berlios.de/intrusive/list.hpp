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
#ifndef CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace cbear_berlios_de
{
namespace intrusive
{

class basic_node: boost::noncopyable
{
public:

	basic_node() { this->construct(); }
	~basic_node() { this->destroy(); }

	typedef basic_node *pointer;
	typedef basic_node &reference;

	class iterator
	{
	public:

		iterator(): P(0) {}

		explicit iterator(reference N): P(&N) {}

		reference operator*() const { return *this->P; }
		pointer operator->() const { return this->P; }

		iterator &operator++()
		{
			this->P = this->P->Next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator R(*this);
			this->P = this->P->Next;
			return R;
		}

		iterator &operator--()
		{
			this->P = this->P->Prev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator R(*this);
			this->P = this->P->Prev;
			return R;
		}

		bool operator==(const iterator &B) const
		{
			return this->P == B.P;
		}
		bool operator!=(const iterator &B) const
		{
			return this->P != B.P;
		}

		void insert(reference R)
		{
			R.destroy();

			R.Prev = this->P->Prev;
			R.Next = this->P;

			R.Prev->Next = R.Next->Prev = &R;
		}

		void erase()
		{
			this->P->destroy(); 
			this->P->construct();
		}

	private:
		pointer P;
	};

private:

	pointer Prev;
	pointer Next;
  
	void construct() { this->Prev = this->Next = this; }

	void destroy()
	{
		this->Prev->Next = this->Next;
		this->Next->Prev = this->Prev;
	}
};

template<class ValueType>
class node: private basic_node
{
private:

	// Because of VC 7.1
	typedef basic_node::iterator basic_iterator;

	node(const node &);
	node &operator=(const node &);

public:

	typedef ValueType *pointer;
	typedef ValueType &reference;
	typedef std::ptrdiff_t difference_type;

	class iterator: 
		private basic_iterator,
		public boost::bidirectional_iterator_helper<
			iterator, node, difference_type, pointer, reference>
	{
	public:

		iterator() {}

		explicit iterator(reference N): basic_node::iterator(N) {}

		reference operator*() const 
		{ 
			return static_cast<reference>(this->basic_node::iterator::operator*());
		}

		iterator &operator++()
		{
			this->basic_node::iterator::operator++();
			return *this;
		}

		iterator &operator--()
		{
			this->base_node::iterator::operator--();
			return *this;
		}

		bool operator==(const iterator &B) const
		{
			return this->basic_node::iterator::operator==(B);
		}

		void insert(reference R) { this->basic_node::iterator::insert(R); }

		using basic_iterator::erase;
	};

protected:

	node() {}
};

template<class ValueType>
class list: 
	private node<ValueType>, 
	public range::helper<
		list<ValueType>, 
		typename node<ValueType>::iterator, 
		typename node<ValueType>::iterator>
{
public:

	typedef node<ValueType> node_type;

	typedef typename node_type::iterator iterator;
	typedef typename node_type::pointer pointer;
	typedef typename node_type::reference reference;

	iterator begin() { return boost::next(this->end()); }

	iterator end()
	{
		return iterator(*static_cast<pointer>(static_cast<node_type *>(this)));
	}

	void push_front(reference R) { this->begin().insert(R); }
	void push_back(reference R) { this->end().insert(R); }

	void pop_front() { this->begin().erase(); }
	void pop_back() { boost::prev(this->end()).erase(); }
};


}
}

#endif
