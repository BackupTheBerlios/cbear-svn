#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_SAM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_SAM_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class sam: public policy::wrap<sam, ::REGSAM>
{
	typedef policy::wrap<sam, ::REGSAM> wrap_type;
public:
	enum enumeration_type
	{
		all_access = KEY_ALL_ACCESS,
		create_link = KEY_CREATE_LINK,
		create_sub_key = KEY_CREATE_SUB_KEY,
		enumerate_sub_keys = KEY_ENUMERATE_SUB_KEYS,
		execute = KEY_EXECUTE,
		notify = KEY_NOTIFY,
		query_value = KEY_QUERY_VALUE,
		read = KEY_READ,
		set_value = KEY_SET_VALUE,
		//wow64_32key = KEY_WOW64_32KEY,
		//wow64_64key = KEY_WOW64_64KEY,
		write = KEY_WRITE,
		
	};
	sam(enumeration_type X = all_access): wrap_type(X) {}
};

}
}
}

#endif
