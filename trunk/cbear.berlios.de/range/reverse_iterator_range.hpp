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
#ifndef CBEAR_SOURCEFORGE_NET_RANGE_REVERSE_ITERATOR_RANGE_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_RANGE_REVERSE_ITERATOR_RANGE_HPP_INCLUDED

#include <cbear.sourceforge.net/range/iterator_range.hpp>

namespace cbear_sourceforge_net
{
namespace range
{

template<class Iterator>
struct reverse_iterator_range
{
	typedef iterator_range< ::std::reverse_iterator<Iterator> > type;
};

template<class Iterator>
typename reverse_iterator_range<Iterator>::type make_reverse_iterator_range(
	const Iterator &B, const Iterator &E)
{
	typedef ::std::reverse_iterator<Iterator> reverse_iterator;
	return reverse_iterator_range<Iterator>::type(
		reverse_iterator(E), reverse_iterator(B));
}

}
}

#endif
