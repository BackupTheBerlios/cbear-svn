#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_OPTIONS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_OPTIONS_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class options: public policy::wrap<options, ::DWORD>
{
	typedef policy::wrap<options, ::DWORD> wrap_type;
public:
	enum enumeration_type
	{
		reserved = REG_OPTION_RESERVED,
		non_volatile = REG_OPTION_NON_VOLATILE,
		volatile_all = REG_OPTION_VOLATILE,
		create_link = REG_OPTION_CREATE_LINK,
		backup_restore = REG_OPTION_BACKUP_RESTORE,
		open_link = REG_OPTION_OPEN_LINK,

		legal = REG_LEGAL_OPTION,
	};
	options() {}
	options(enumeration_type X): wrap_type(X) {}
};

}
}
}

#endif
