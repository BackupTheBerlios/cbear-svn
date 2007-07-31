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
#ifndef CBEAR_BERLIOS_DE_RANGE_ARRAYZ_REF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_ARRAYZ_REF_HPP_INCLUDED

#include <cbear.berlios.de/range/array_ref.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class ItemType, ::std::size_t Size>
struct arrayz_ref
{
	typedef array_ref<ItemType, Size, true> type;
};

template<class ValueType, ::std::size_t Size>
typename arrayz_ref<const ValueType, Size>::type make_arrayz_ref(
	const ValueType (&X)[Size])
{
	return arrayz_ref<const ValueType, Size>::type(X);
}

template<class ValueType, ::std::size_t Size>
typename arrayz_ref<ValueType, Size>::type make_arrayz_ref(
	ValueType (&R)[Size])
{
	return arrayz_ref<ValueType, Size>::type(X);
}

}
}

#endif