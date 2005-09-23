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

#include <net/sourceforge/cbear/bit/range.hpp>

// boost::uint32_t
#include <boost/cstdint.hpp>
// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>

#include <boost/test/minimal.hpp>

namespace Cbear = net::sourceforge::cbear;

template<class T>
void print(T X) 
{ 
	BOOST_STATIC_ASSERT(!Cbear::base::is_signed<T>::value);
}

int test_main(int, char*[])
{
	signed long Result;
	typedef Cbear::bit::one<signed long, 31> BitRange;

	BOOST_CHECK(BitRange::mask==0x80000000);

	print(boost::uint32_t(0x80000000));
	print(
		boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000));
	print(
		(boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000)) >> 31);

	Result = 0x80000000;
	BOOST_CHECK((Result & BitRange::mask) == 0x80000000);
	BOOST_CHECK((0x80000000 >> 31) == 1);
	BOOST_CHECK(
		static_cast<signed short>(0x8000) >> 15 == 
		static_cast<signed short>(0xFFFF));
	BOOST_CHECK(BitRange::first==31);
	BOOST_CHECK(((Result & BitRange::mask) >> 31) == 1);
	BOOST_CHECK(((Result & BitRange::mask) >> BitRange::first) == 1);

	BOOST_CHECK(BitRange::get(Result)==1);

	Result = 0;
	BOOST_CHECK(!BitRange::reference(Result));
	Result = 0x80000000;
	BOOST_CHECK(
		(BitRange::mask & BitRange::unsigned_type(Result)) == 0x80000000);
	BOOST_CHECK(
		(BitRange::mask & BitRange::unsigned_type(Result)) >> BitRange::first);
	BOOST_CHECK(BitRange::get(Result));
	BOOST_CHECK(BitRange::reference(Result));

	Result = 0;
	BitRange::make_reference(Result) = true;
	BOOST_CHECK(bool(BitRange::reference(Result)));
	BOOST_CHECK(Result==0x80000000);

	BitRange::make_reference(Result) = false;
	BOOST_CHECK(!BitRange::reference(Result));
	BOOST_CHECK(Result==0);

	return 0;
}
