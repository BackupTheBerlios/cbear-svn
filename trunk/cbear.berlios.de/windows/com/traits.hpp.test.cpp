/*
The MIT License

Copyright (c) 2005 C Bear (http://sourceforge.net)

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
#include <cbear.berlios.de/com/traits.hpp>

#include <boost/test/minimal.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::is_same
#include <boost/type_traits.hpp>

namespace Cbear = cbear_berlios_de;
namespace Com = cbear_berlios_de::com;

class My
{
public:

	typedef Cbear::policy::standard_policy<int> internal_policy;

	const int &internal() const { return this->I; }
	int &internal() { return this->I; }
	
private:
	int I;
};

BOOST_STATIC_ASSERT((
	boost::is_same<Com::traits<My>::internal_policy::type, int>::value));

int test_main(int, char*[])
{
	return 0;
}
