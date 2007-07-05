#ifndef CBEAR_BERLIOS_DE_RANGE_HELPER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_HELPER_HPP_INCLUDED

#include <cbear.berlios.de/base/default.hpp>
#include <cbear.berlios.de/base/empty.hpp>
#include <cbear.berlios.de/base/integer.hpp>

// std::distance
#include <iterator>

// boost::prior, boost::next
#include <boost/utility.hpp>
// boost::is_same
#include <boost/type_traits/is_same.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Iterator>
class iterator_range;

template<class Container, class Base>
class helper_t: public Base
{
public:
	typedef Container container_t;
	typedef typename Base::iterator iterator;
	typedef typename Base::const_iterator const_iterator;
	
	typedef ::std::iterator_traits<iterator> iterator_traits;
	typedef ::std::iterator_traits<const_iterator> const_iterator_traits;
	
	typedef typename const_iterator_traits::value_type value_type;
	typedef typename const_iterator_traits::difference_type difference_type;
	typedef typename base::make_unsigned<difference_type>::type size_type;
	
	typedef typename iterator_traits::reference reference;
	typedef typename const_iterator_traits::reference const_reference;
	typedef typename iterator_traits::pointer pointer;
	typedef typename const_iterator_traits::pointer const_pointer;
	
	typedef typename ::std::reverse_iterator<iterator> 
		reverse_iterator;
	typedef typename ::std::reverse_iterator<const_iterator> 
		const_reverse_iterator;

	typedef iterator_range<iterator> iterator_range_t;
	typedef iterator_range<const_iterator> const_iterator_range_t;

	helper_t() 
	{
	}

	template<class T>
	helper_t(T const &X): 
		Base(X)
	{
	}

	template<class T1, class T2>
	helper_t(T1 const &X1, T2 const &X2): 
		Base(X1, X2)
	{
	}
	
	bool empty() const 
	{ 
		return this->This().begin()==this->This().end(); 
	}
	size_type size() const 
	{ 
		return size_type(::std::distance(
			this->This().begin(), this->This().end()));
	}
	
	reference front() 
	{ 
		return *This().begin(); 
	}
	const_reference front() const 
	{ 
		return *This().begin(); 
	}
	reference back() 
	{ 
		return *boost::prior(This().end()); 
	}
	const_reference back() const 
	{ 
		return *boost::prior(This().end()); 
	}
	reference at(size_type I)
	{
		return *boost::next(this->This().begin(), I);
	}
	const_reference at(size_type I) const
	{
		return *boost::next(this->This().begin(), I);
	}
	reference operator[](size_type I)
	{
		return this->at(I);
	}
	const_reference operator[](size_type I) const
	{
		return this->at(I);
	}
	
	reverse_iterator rbegin() 
	{ 
		return reverse_iterator(This().end()); 
	}
	const_reverse_iterator rbegin() const 
	{ 
		return const_reverse_iterator(This().end()); 
	}
	
	reverse_iterator rend() 
	{ 
		return reverse_iterator(This().begin()); 
	}
	const_reverse_iterator rend() const 
	{ 
		return const_reverse_iterator(This().begin());
	}

	template<class Stream>
	void write(Stream &S) const
	{
		typedef typename Stream::value_type char_t;
		BOOST_STATIC_ASSERT((boost::is_same<char_t, value_type>::value));
		S.push_back_range(this->This());
	}

	void resize(size_type S)
	{
		difference_type dif = 
			static_cast<difference_type>(S) -
			static_cast<difference_type>(this->This().size());
		if(dif > 0)
		{
			this->This().insert_range(this->This().end(), make_fill(base::default_(), dif));
		}
		else if(dif < 0)
		{
			this->This().erase_range(iterator_range_t(
				::boost::prior(this->This().end(), -dif), this->This().end()));
		}
	}

	template<class T>
	iterator insert(iterator I, T const &X)
	{
		return this->This().insert_range(I, make_fill(X, 1));
	}
	template<class T>
	void push_front(T const &X)
	{
		this->insert(this->This().begin(), X);
	}
	void push_front()
	{
		this->insert(this->This().begin(), base::default_());
	}
	template<class R>
	void push_front_range(R const &source)
	{
		this->This().insert_range(this->This().begin(), source);
	}
	template<class T>
	void push_back(T const &X)
	{
		this->insert(this->This().end(), X);
	}
	void push_back()
	{
		this->insert(this->This().end(), base::default_());
	}
	template<class R>
	void push_back_range(R const &source)
	{
		this->This().insert_range(this->This().end(), source);
	}

	void erase(iterator I)
	{
		this->This().erase_range(iterator_range_t(I, 1));
	}
	
private:
	container_t &This() 
	{ 
		return *static_cast<container_t *>(this); 
	}
	container_t const &This() const 
	{ 
		return *static_cast<container_t const *>(this); 
	}
};

}
}

#endif
