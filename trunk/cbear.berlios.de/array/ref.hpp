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

template<class T, ::std::size_t RealSize>
class ref_t: public range::helper<ref_t<T, RealSize>, T *, T *>
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

#define CBEAR_BERLIOS_DE_ARRAY_REF(X) \
	::cbear_berlios_de::array::detail::ref<sizeof(X)/sizeof(*(X))>(X)

#endif
