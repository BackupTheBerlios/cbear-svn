#ifndef CBEAR_BERLIOS_DE_ARRAY_REF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_ARRAY_REF_HPP_INCLUDED

#include <cbear.berlios.de/range/helper.hpp>
#include <cbear.berlios.de/base/character.hpp>
// ::boost::remove_const
#include <boost/type_traits/remove_const.hpp>

namespace cbear_berlios_de
{
namespace array
{

namespace detail
{

template<class T>
class ref_base_t
{
public:
	typedef T *iterator;
	typedef T *const_iterator;
};

}

template<class T, ::std::size_t RealSize>
class ref_t: public range::helper_t<ref_t<T, RealSize>, detail::ref_base_t<T> >
{ 
public:

	typedef typename ::boost::remove_const<T>::type value_type;

	static const bool zero_terminated = base::is_character<value_type>::value;

	static const ::std::size_t const_size = 
		zero_terminated ? RealSize - 1 : RealSize;

	typedef T *iterator;

	explicit ref_t(iterator B): 
		B(B) 
	{
	}

	iterator begin() const 
	{ 
		return this->B; 
	}
	iterator end() const 
	{ 
		return this->B + const_size; 
	}

private:
	iterator B;
	BOOST_STATIC_ASSERT(const_size > 0);
};

namespace detail
{
// Because of DMC.
template< ::std::size_t Size, class T>
ref_t<T, Size> ref(T *B)
{
	return ref_t<T, Size>(B);
}

}

template< ::std::size_t Size, class T>
ref_t<const T, Size> ref(const T (&X)[Size])
{
	return ref_t<const T, Size>(X);
}

template< ::std::size_t Size, class T>
ref_t<T, Size> ref(T (&X)[Size])
{
	return ref_t<T, Size>(X);
}

}
}

#define CBEAR_BERLIOS_DE_ARRAY_SIZE(X) (sizeof(X)/sizeof(*(X)))

#define CBEAR_BERLIOS_DE_ARRAY_REF(X) \
	::cbear_berlios_de::array::detail::ref<CBEAR_BERLIOS_DE_ARRAY_SIZE(X)>(X)

#endif
