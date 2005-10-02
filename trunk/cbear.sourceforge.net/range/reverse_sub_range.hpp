/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
#ifndef CBEAR_SOURCEFORGE_NET_RANGE_REVERSE_SUB_RANGE_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_RANGE_REVERSE_SUB_RANGE_HPP_INCLUDED

#include <cbear.sourceforge.net/range/reverse_iterator_range.hpp>
#include <cbear.sourceforge.net/range/rbegin.hpp>
#include <cbear.sourceforge.net/range/rend.hpp>

namespace cbear_sourceforge_net
{
namespace range
{

template<class Range>
struct reverse_sub_range: reverse_iterator_range<typename iterator<Range>::type>
{
};

template<class Range>
typename reverse_sub_range<Range>::type make_reverse_sub_range(
	Range &X)
{
	return reverse_sub_range<Range>::type(rbegin(X), rend(X));
}

template<class Range>
typename reverse_sub_range<const Range>::type make_reverse_sub_range(
	const Range &X)
{
	return reverse_sub_range<const Range>::type(rbegin(X), rend(X));
}

}
}

#endif
