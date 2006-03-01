#include <cbear.berlios.de/base/string.hpp>
#include <iostream>
#include <boost/assert.hpp>

namespace Base = cbear_berlios_de::base;

int main()
{
	BOOST_ASSERT(Base::string("\0").size()==1);
	BOOST_ASSERT(Base::string('\0').size()==1);
	BOOST_ASSERT(Base::string("\0\0A\0").size()==4);
	BOOST_ASSERT(Base::string('\0') == "\0");
	BOOST_ASSERT("\0" == Base::string('\0'));
	BOOST_ASSERT(Base::string("\0") == '\0');
	BOOST_ASSERT('\0' == Base::string("\0"));
	BOOST_ASSERT(Base::string('\0') == Base::string("\0"));
	std::cout << "Ok" << std::endl;
	char C;
	std::cin.get(C);
	return 0;
}