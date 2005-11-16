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
#ifndef CBEAR_BERLIOS_DE_RANGE_TRANSFORM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_TRANSFORM_HPP_INCLUDED

// std::transform
#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

/** @brief Assigns through every iterator I in the range
	[result, result + size(R)) a new value equal to op(at(R, I - result)).

    @result result + size(R).

    @sa std::transform.
*/
template<class InputRange, class OutputIterator, class UnaryOperation>
OutputIterator
transform(InputRange &R, OutputIterator result, UnaryOperation op)
{
	return std::transform(begin(R), end(R), result, op);
}

}
}

#endif
