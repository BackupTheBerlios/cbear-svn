#include <cbear.berlios.de/svn/client/main.hpp>
#include <iostream>

namespace Svn = cbear_berlios_de::svn;

int main()
{
	const Svn::version_t &V = Svn::client::version();
	std::cout << 
		V.major << " " << 
		V.minor << " " << 
		V.patch << " " << 
		V.tag <<
		std::endl;
	std::cin.get();
	return 0;
}
