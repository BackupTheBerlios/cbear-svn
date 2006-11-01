#ifndef CBEAR_BERLIOS_DE_RANGE_HELPER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_HELPER_HPP_INCLUDED

// std::distance
#include <iterator>

// boost::prior, boost::next
#include <boost/utility.hpp>
// boost::is_same
#include <boost/type_traits/is_same.hpp>

#include <cbear.berlios.de/base/empty.hpp>
#include <cbear.berlios.de/base/integer.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<
	class Container, class Iterator, class ConstIterator, class Base = base::empty>
class helper: public Base
{
public:
	typedef Container container;
	typedef Iterator iterator;
	typedef ConstIterator const_iterator;
	
	typedef ::std::iterator_traits<Iterator> iterator_traits;
	typedef ::std::iterator_traits<ConstIterator> const_iterator_traits;
	
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

	helper() 
	{
	}

	template<class T>
	helper(const T &X): Base(X) 
	{
	}

	template<class T1, class T2>
	helper(const T1 &X1, const T2 &X2): 
		Base(X1, X2) 
	{
	}
	
	bool empty() const 
	{ 
		return This().begin()==This().end(); 
	}
	size_type size() const 
	{ 
		return size_type(::std::distance(This().begin(), This().end())); 
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
	reference operator[](size_type I)
	{
		return *boost::next(This().begin(), I);
	}
	const_reference operator[](size_type I) const
	{
		return *boost::next(This().begin(), I);
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
	
private:
	container &This() 
	{ 
		return *static_cast<container *>(this); 
	}
	const container &This() const 
	{ 
		return *static_cast<const container *>(this); 
	}
};

}
}

#endif
