#ifndef CBEAR_BERLIOS_DE_WINDOWS_MUTEX_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MUTEX_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/bool.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/handle.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// The function creates or opens a named or unnamed mutex object.
template<class Char>
handle create_mutex(
	security_attributes MutexAttributes, 
	bool_t InitialOwner,
	const basic_lpstr<const Char> &Name)
{
	exception::scope_last_error ScopeLastError;
	return handle(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::CreateMutex)(
		MutexAttributes.get(), InitialOwner.get(), Name.get()));
}

}
}

#endif
