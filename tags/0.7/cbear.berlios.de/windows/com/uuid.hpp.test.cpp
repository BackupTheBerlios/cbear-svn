#include <cbear.berlios.de/com/uuid.hpp>

#include <boost/test/minimal.hpp>

namespace Cbear = cbear_berlios_de;
namespace Com = Cbear::windows::com;

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
