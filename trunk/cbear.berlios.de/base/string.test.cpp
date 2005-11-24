#include <cbear.berlios.de/base/string.hpp>
#include <iostream>

namespace Base = cbear_berlios_de::base;

int main()
{
	Base::string A("\0");
	std::cout << A.size() << std::endl;
	A = '\0';
	char C;
	std::cin.get(C);
	return 0;
}