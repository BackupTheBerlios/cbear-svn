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

#include <cbear.berlios.de/com/uuid.hpp>

#include <boost/test/minimal.hpp>

namespace Cbear = cbear_berlios_de;
namespace Com = Cbear::com;

class IDMy: public ::IUnknown
{
};

namespace net
{
namespace sourceforge
{
namespace cbear
{
namespace com
{

template<> struct uuid::of_type< ::IDMy>
{ 
	static uuid create() 
	{ 
		return uuid(
			0x01234567, 
			0x89AB, 
			0xCDEF, 
			0x01, 
			0x23, 
			0x34, 
			0x56, 
			0x67, 
			0x78, 
			0x9A, 
			0xBF);
	} 
};

}
}
}
}

int test_main(int, char*[])
{
	const ::UUID Internal = 
	{
		0x01234567, 0x89AB, 0xCDEF, 
		{ 0x01, 0x23, 0x34, 0x56, 0x67, 0x78, 0x9A, 0xBC }
	};
	const ::UUID Internal2 =
	{
		0x01234567, 0x89AB, 0xCDEF, 
		{ 0x01, 0x23, 0x34, 0x56, 0x67, 0x78, 0x9A, 0xBE }
	};
	Com::uuid Uuid = Com::uuid(
		0x01234567, 0x89AB, 0xCDEF, 0x01, 0x23, 0x34, 0x56, 0x67, 0x78, 0x9A, 0xBC);
	BOOST_CHECK(Uuid==Com::uuid(Internal));
	BOOST_CHECK(Com::uuid(Internal2)!=Uuid);

	BOOST_CHECK(Com::uuid::of< ::IUnknown>() == Com::uuid(::IID_IUnknown));
	BOOST_CHECK((Com::uuid::of< ::IDMy>() == Com::uuid(
		0x01234567, 
		0x89AB, 
		0xCDEF, 
		0x01, 
		0x23, 
		0x34, 
		0x56, 
		0x67, 
		0x78, 
		0x9A, 
		0xBF)));
	return 0;
}
