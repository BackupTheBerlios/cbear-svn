#include <cbear.berlios.de/svn/client/main.hpp>
#include <cbear.berlios.de/windows/cout.hpp>
#include <iostream>

namespace Svn = cbear_berlios_de::svn;
namespace Client = cbear_berlios_de::svn::client;
namespace Windows = cbear_berlios_de::windows;

int main()
{
	const Svn::version_t &V = Client::version();
	Windows::cout() << V << "\n";
	std::cin.get();
	return 0;
}
