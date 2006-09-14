#ifndef CBEAR_BERLIOS_DE_WINDOWS_HMODULE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HMODULE_HPP_INCLUDED

// VC: winnt.h.
#include <windows.h>
// MINGW: winnt.h: CONST
#include <windef.h>
// MINGW: psapi.h: LPVOID
#include <winnt.h>
// DMC: psapi.h: SIZE_T
#include <basetsd.h>
#include <psapi.h>

#ifndef GetProcAddressA
#define GetProcAddressA GetProcAddress
#endif

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/handle.hpp>
#include <cbear.berlios.de/windows/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{

typedef ::FARPROC farproc;

class hmodule: public base::initialized< ::HMODULE>
{
public:
	typedef base::initialized< ::HMODULE> wrap_type;
	typedef wrap_type::value_t internal_type;

	hmodule() {}
	explicit hmodule(internal_type X): wrap_type(X) {}

	template<class Char>
	std::basic_string<Char> file_name() const
	{
		Char Buffer[max_path];
		dword_t Length;
		{
			exception::scope_last_error ScopeLastError;
			Length = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::GetModuleFileName)(
				this->get(), Buffer, max_path);
		}
		return std::basic_string<Char>(Buffer, Length);
	}

	farproc GetProcAddress(const lpcstr_t &ProcName)
	{
		exception::scope_last_error ScopeLastError;
		return ::GetProcAddressA(this->get(), ProcName.get());
	}

	/* // Because MINGW doesn't have GetProcAddressA and GetProcAddressW.
	template<class Char>
	farproc GetProcAddress(const basic_lpstr<const Char> &ProcName)
	{
		exception::scope_last_error ScopeLastError;
		return CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::GetProcAddress)(
			this->internal(), ProcName.internal());
	}
	*/
};

}
}

#endif
