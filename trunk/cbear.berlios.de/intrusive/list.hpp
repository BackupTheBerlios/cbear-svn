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

		explicit iterator(reference N): P(&N) {}

		reference operator*() const { return *this->P; }
		pointer operator->() const { return this->P; }

		iterator &operator++()
		{
			*this = this->Next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator R(*this);
			*this = this->Next;
			return R;
		}

		iterator &operator--()
		{
			*this = this->Prev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator R(*this);
			*this = this->Prev;
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

			R.Prev = this->Prev;
			R.Next = *this;

			R.Prev->Next = R.Next->Prev = *this;
		}

		void erase()
		{
			this->destroy(); 
			this->construct();
		}

	private:
		pointer P;
	};

private:

	iterator Prev;
	iterator Next;
  
	void construct() { this->Prev = this->Next = iterator(*this); }

	void destroy()
	{
		this->Prev->Next = this->Next;
		this->Next->Prev = this->Prev;
	}
};

template<class ValueType>
class node: private basic_node
{
public:

	BOOST_STATIC_ASSERT((is_base_of<node, ValueType>::value));

	typedef ValueType *pointer;
	typedef ValueType &reference;

	class iterator: private basic_node::iterator
	{
	public:
		explicit iterator(reference N): basic_node::iterator(N) {}

		reference operator*() const 
		{ 
			return static_cast<reference>(this->base_node::iterator::operator*());
		}
		pointer operator->() const 
		{ 
			return &static_cast<reference>(this->base_node::iterator::operator*()); 
		}

		iterator &operator++()
		{
			this->base_node::iterator::operator++();
			return *this;
		}
		iterator operator++(int)
		{
			iterator R(*this);
			this->base_node::iterator::operator++();
			return R;
		}

		iterator &operator--()
		{
			this->base_node::iterator::operator--();
			return *this;
		}
		iterator operator--(int)
		{
			iterator R(*this);
			this->base_node::iterator::operator--();
			return R;
		}

		bool operator==(const iterator &B) const
		{
			return this->base_node::iterator::operator==(B);
		}
		bool operator!=(const iterator &B) const
		{
			return this->base_node::iterator::operator!=(B);
		}

		void insert(reference R)
		{
			this->base_node::iterator::insert(R);
		}

		using basic_node::iterator::erase;
	};

protected:

	node() {}
};

template<class ValueType>
class list: private node<ValueType>
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
