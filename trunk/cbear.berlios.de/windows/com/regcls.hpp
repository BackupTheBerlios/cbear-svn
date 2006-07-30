#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_REGCLS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_REGCLS_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class regcls: public com::enum_t<regcls, dword_t>
{
public:
	typedef com::enum_t<regcls, dword_t> wrap_type;
	enum enumeration_type 
	{ 
		singleuse = REGCLS_SINGLEUSE,
    multipleuse = REGCLS_MULTIPLEUSE,                        
    multi_separat = REGCLS_MULTI_SEPARATE,
    suspended = REGCLS_SUSPENDED,
    surrogate = REGCLS_SURROGATE,
	};
	regcls(enumeration_type X): wrap_type(X) {}
};

}
}
}

#endif
