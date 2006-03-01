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
#ifndef CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_LESS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_LEXICOGRAPHIC_LESS_HPP_INCLUDED

// std::lexicographical_compare
#include <algorithm>

#include <cbear.berlios.de/range/sub_range.hpp>

namespace cbear_berlios_de
{
namespace range
{
namespace lexicographic
{

// Calls ::std::lexicographical_compare.
// Returns true if R1 < R2, false if R1 >= R2.
template<class Range1, class Range2>
bool less(const Range1 &R1, const Range2 &R2)
{
	return ::std::lexicographical_compare(
		range::begin(R1), range::end(R2), range::begin(R1), range::end(R2));
}

}
}
}

#endif
