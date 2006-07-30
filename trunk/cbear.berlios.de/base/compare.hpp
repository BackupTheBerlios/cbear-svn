#ifndef CBEAR_BERLIOS_DE_BASE_COMPARE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_COMPARE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_class.hpp>

namespace cbear_berlios_de
{
namespace base
{

namespace detail
{

class default_compare
{
public:
	template<class T>
	static int do_(const T &A, const T &B) { return A == B ? 0: A<B ? -1: 1; }
};

class class_compare
{
public:
	template<class T>
	static int do_(const T &A, const T &B) { return A.compare(B); }
};

}

template<class T>
int compare(const T &A, const T &B)
{
	return boost::mpl::if_<
		boost::is_class<T>, detail::class_compare, detail::default_compare>::type::
		do_(A, B);
}

}
}

#endif
