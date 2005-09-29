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

#include <cbear.sourceforge.net/range/lexicographical_compare.hpp>

#include <boost/test/minimal.hpp>

#include <boost/range/size.hpp>

namespace Container = cbear_sourceforge_net::range;

int a[] = { 1, 2, 3 };

int test_main(int, char*[])
{
	BOOST_CHECK(boost::size("\1\2\3")==3);
	BOOST_CHECK(!Container::lexicographical_compare(a, "\1\2\2\2"));
	BOOST_CHECK(Container::lexicographical_compare(a, "\1\2\3\4"));
	BOOST_CHECK(Container::lexicographical_compare(a, "\1\2\4"));
	BOOST_CHECK(!Container::lexicographical_compare(a, "\1\2\3"));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\3", a));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\4", a));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\3\4", a));
	BOOST_CHECK(Container::lexicographical_compare("\1\2\2\2", a));
	return 0;
}
