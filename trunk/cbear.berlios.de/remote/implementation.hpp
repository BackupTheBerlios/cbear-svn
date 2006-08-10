#ifndef CBEAR_BERLIOS_DE_REMOTE_IMPLEMENTATION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_IMPLEMENTATION_HPP_INCLUDED

#inclide <cbear.berlios.de/remote/interface.hpp>

namespace cbear_berlios_de
{
namespace remote
{

class implementation: private interface<implementation>
{
public:
	implementation(const windows::com::itypeinfo &TypeInfo):
		TypeInfo(TypeInfo)
	{
	}
};

}
}

#endif
