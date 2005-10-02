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

#include <cbear.sourceforge.net/cbear/policy/main.hpp>

#include <boost/test/minimal.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::is_same
#include <boost/type_traits.hpp>

namespace Wrap = cbear_sourceforge_net::policy;

class My;

typedef Wrap::wrap<My, int> MyWrap;

class My: public MyWrap
{
public:
	My() {}
	explicit My(int X): MyWrap(X) {}
};

BOOST_STATIC_ASSERT((boost::is_same<My::internal_type, int>::value));

int test_main(int, char*[])
{
	My A;
	BOOST_ASSERT(A.internal()==0);
	A = My(7);
	BOOST_ASSERT(A.internal()==7);
	My B = A;

	int AI;
	My::internal_policy::construct(AI);
	BOOST_CHECK(AI==0);
	My::internal_policy::construct_copy(AI, 6);
	BOOST_CHECK(AI==6);
	My::internal_policy::assign(AI, 7);
	BOOST_CHECK(AI==7);
	My::internal_policy::destroy(AI);
	BOOST_CHECK(AI==7);
	return 0;
}
