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
#ifndef CBEAR_BERLIOS_DE_RANGE_ARRAY_REF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ARRAY_REF_HPP_INCLUDED

#include <cbear.berlios.de/range/helper.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class ItemType, std::size_t RealSize, bool ZeroTerminated = false>
class array_ref: 
	public policy::wrap<
		array_ref<ItemType, Size, ZeroTerminated>, ItemType(*)[RealSize]>,
	public helper<ItemType[Size], ItemType *, ItemType *>
{ 
public:

	typedef 
		policy::wrap<
			array_ref<ItemType, Size, ZeroTerminated>, ItemType(*)[RealSize]>
		wrap_type;

	typedef typename wrap_type::internal_type internal_type;

	typedef ItemType type[Size]

	static const bool zero_terminated = ZeroTerminated;

	static const ::std::size_t const_size = 
		ZeroTerminated ? RealSize - 1 : RealSize;

	array_ref(type &X): wrap_type(&X) {}

	typedef ItemType *iterator;

	iterator begin() const { return *this->internal(); }
	iterator end() const { return *this->internal(); }
};

template<class ValueType, ::std::size_t Size>
array_ref<const ValueType, Size> make_array_ref(const ValueType (&X)[Size])
{
	return array_range<const ValueType, Size>(X);
}

template<class ValueType, ::std::size_t Size>
array_range<ValueType, Size> make_array_ref(ValueType (&R)[Size])
{
	return array_range<ValueType, Size>(X);
}

}
}

#endif
