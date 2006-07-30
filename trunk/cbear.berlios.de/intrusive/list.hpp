#ifndef CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/operators.hpp>

#include <cbear.berlios.de/range/helper.hpp>

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

		// R, this->P.
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

	// Because of DMC.
	friend class iterator;

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
			return static_cast<reference>(
				this->basic_node::iterator::operator*());
		}

		pointer operator->() const 
		{ 
			return &static_cast<reference>(
				this->basic_node::iterator::operator*());
		}

		iterator &operator++()
		{
			this->basic_node::iterator::operator++();
			return *this;
		}

		iterator &operator--()
		{
			this->basic_node::iterator::operator--();
			return *this;
		}

		bool operator==(const iterator &B) const
		{
			return this->basic_node::iterator::operator==(B);
		}

		void insert(reference R) { this->basic_node::iterator::insert(R); }

		using basic_iterator::erase;
	};

	node() {}
};

template<class ValueType>
class list: 
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

	iterator begin() const { return boost::next(this->end()); }

	iterator end() const
	{
		return iterator(*static_cast<pointer>(&this->Node));
	}

	void push_front(reference R) { this->begin().insert(R); }
	void push_back(reference R) { this->end().insert(R); }

	void pop_front() { this->begin().erase(); }
	void pop_back() { boost::prior(this->end()).erase(); }
private:
	mutable node<ValueType> Node;
};

}
}

#endif
