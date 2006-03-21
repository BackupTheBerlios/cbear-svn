/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_WINDOWS_HMODULE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HMODULE_HPP_INCLUDED

#include <psapi.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/handle.hpp>
#include <cbear.berlios.de/windows/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{

typedef ::FARPROC farproc;

class hmodule: public policy::wrap<hmodule, ::HMODULE>
{
public:
	typedef policy::wrap<hmodule, ::HMODULE> wrap_type;
	typedef wrap_type::internal_type internal_type;

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
				this->internal(), Buffer, max_path);
		}
		return std::basic_string<Char>(Buffer, Length);
	}

	template<class Char>
	farproc GetProcAddress(const basic_lpstr<const Char> &ProcName)
	{
		exception::scope_last_error ScopeLastError;
		return select<Char>(::GetProcAddressA, ::GetProcAddressW)(
			this->internal(), ProcName.internal());
	}
};

}
}

#endif
