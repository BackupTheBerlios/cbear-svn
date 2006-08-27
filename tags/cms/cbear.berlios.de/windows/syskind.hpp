#ifndef CBEAR_BERLIOS_DE_WINDOWS_SYSKIND_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SYSKIND_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{

class syskind_t: public policy::wrap<syskind_t, ::SYSKIND>
{
public:
	typedef policy::wrap<syskind_t, ::SYSKIND> wrap_type;

	enum enumeration_type
	{
		win16 = ::SYS_WIN16,
		win32 = ::SYS_WIN32,
		mac = ::SYS_MAC,
	};

	syskind_t() {}
	syskind_t(enumeration_type X): wrap_type(internal_type(X)) {}
};

}
}

#endif
