#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DISPOSITION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DISPOSITION_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class disposition: public policy::wrap<disposition, ::DWORD>
{
	typedef policy::wrap<disposition, ::DWORD> wrap_type;
public:
	enum enumeration_type
	{
		created_new_key = REG_CREATED_NEW_KEY,
		opened_existing_key = REG_OPENED_EXISTING_KEY,
	};
	disposition() {}
	disposition(enumeration_type X): wrap_type(X) {}
};

}
}
}

#endif
