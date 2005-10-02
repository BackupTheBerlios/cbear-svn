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

#include <cbear.sourceforge.net/base/integer.hpp>

#include <boost/test/minimal.hpp>

namespace Base = cbear_sourceforge_net::base;

int test_main(int, char *[])
{
	/* See http://www.boost.org/libs/integer/cstdint.htm.
	Base::uint_t<64>::type Q = 0x0123456789ABCDEFull;
	BOOST_CHECK(Base::low(Q)==0x01234567);
	BOOST_CHECK(Base::high(Q)=0x89ABCDEF);	
	*/

	BOOST_CHECK('\1\2\3\4' == 0x01020304);

	Base::uint_t<32>::type A = 0x12345678;
	BOOST_CHECK(Base::low(A)==0x5678);
	BOOST_CHECK(Base::high(A)==0x1234);	

	Base::low(A) = 0x9ABC;
	Base::high(A) = 0xDEF0;
	BOOST_CHECK(A == 0xDEF09ABCul);

	BOOST_CHECK(Base::compose(Base::high(A), Base::low(A)) == A);	

	const Base::uint_t<32>::type CA = 0x12345678;
	BOOST_CHECK(Base::low(CA)==0x5678);
	BOOST_CHECK(Base::high(CA)==0x1234);

	BOOST_CHECK(Base::compose(Base::high(CA), Base::low(CA)) == CA);	

	// 16 => 8, 8

	Base::uint_t<16>::type B = 0x1234;
	BOOST_CHECK(Base::low(B)==0x34);
	BOOST_CHECK(Base::high(B)==0x12);	

	Base::low(B) = 0x56;
	Base::high(B) = 0x78;
	BOOST_CHECK(B == 0x7856);

	BOOST_CHECK(Base::compose(Base::high(B), Base::low(B)) == B);

	const Base::uint_t<16>::type CB = 0x1234;
	BOOST_CHECK(Base::low(CB)==0x34);
	BOOST_CHECK(Base::high(CB)==0x12);	

	BOOST_CHECK(Base::compose(Base::high(CB), Base::low(CB)) == CB);	

	BOOST_CHECK((Base::compose<Base::uint_t<16>::type>(
		Base::uint_t<8>::type(0x12), Base::uint_t<16>::type(0x3456))==0x123456));

	return 0;
}
