#ifndef CBEAR_BERLIOS_DE_REMOTE_UUID_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_UUID_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/uuid.hpp>

namespace cbear_berlios_de
{
namespace remote
{

inline const windows::com::uuid &uuid()
{
	static const windows::com::uuid Result(
		0xde9237bb, 
		0x2fac, 
		0x4944, 
		0x85, 
		0xf5, 
		0xe7, 
		0xd, 
		0x6c, 
		0x53, 
		0xa1, 
		0xd2);
	return Result;
}

}
}

#endif
