#ifndef CBEAR_BERLIOS_DE_BASE_SWAP_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_SWAP_HPP_INCLUDED

#include <algorithm>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

namespace cbear_berlios_de
{
namespace base
{

namespace detail
{

class class_swap_traits
{
public:
	template<class T>
	static void swap(T &A, T &B) { A.swap(B); }
};

class std_swap_traits
{
public:
	template<class T>
	static void swap(T &A, T &B) { std::swap(A, B); }
};

}

template<class T>
void swap(T &A, T &B) 
{ 
	boost::mpl::if_<
		boost::is_class<T>, detail::class_swap_traits, detail::std_swap_traits>::
		type::swap(A, B);
}

}
}

#endif
