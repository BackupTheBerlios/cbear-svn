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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_HKEY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_HKEY_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>
#include <cbear.berlios.de/windows/registry/disposition.hpp>
#include <cbear.berlios.de/windows/registry/sam.hpp>
#include <cbear.berlios.de/windows/registry/options.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class hkey: public policy::wrap<hkey, ::HKEY>
{
	typedef policy::wrap<hkey, ::HKEY> wrap_type;
public:

	static hkey classes_root() { return hkey(HKEY_CLASSES_ROOT); }
	static hkey current_user() { return hkey(HKEY_CURRENT_USER); }
	static hkey local_machine() { return hkey(HKEY_LOCAL_MACHINE); }
	static hkey users() { return hkey(HKEY_USERS); }
	static hkey performance_data() { return hkey(HKEY_PERFORMANCE_DATA); }
	static hkey performance_text() { return hkey(HKEY_PERFORMANCE_TEXT); }
	static hkey performance_nlstext() { return hkey(HKEY_PERFORMANCE_NLSTEXT); }
	static hkey current_config() { return hkey(HKEY_CURRENT_CONFIG); }
	static hkey dyn_data() { return hkey(HKEY_DYN_DATA); }

	typedef wrap_type::internal_type internal_type;

	hkey() {}
	explicit hkey(internal_type X): wrap_type(X) {}

	class create_result;

	template<class Char>
	inline create_result create(
		basic_lpstr<const Char> SubKey, 
		basic_lpstr<const Char> Class, 
		options Options, 
		sam Sam, 
		security_attributes SecurityAttributes) const
	{
		create_result Result;
		exception::throw_unless(::RegCreateKeyExW(
			//HKEY hKey,
			this->internal(),
			// LPCTSTR lpSubKey,
			SubKey.internal(),
			//DWORD Reserved,
			0,
			//LPTSTR lpClass,
			const_cast<Char *>(Class.internal()),
			//DWORD dwOptions,
			Options.internal(),
			//REGSAM samDesired,
			Sam.internal(),
			//LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			SecurityAttributes.internal(),
			//PHKEY phkResult,
			&Result.hkey.internal(),
			//LPDWORD lpdwDisposition,
			&Result.disposition.internal()));
		return Result;
	}

	template<class Char>
	hkey connect(const basic_lpstr<const Char> &X) const
	{
		hkey Result;
		exception::throw_unless(
			select<Char>(::RegConnectRegistryA, ::RegConnectRegistryW)(
				X.internal(), this->internal(), &Result.internal()));
		return Result;
	}

	template<class Char>
	hkey open(const basic_lpstr<const Char> &X, sam Sam) const
	{
		hkey Result;
		exception::throw_unless(
			select<Char>(::RegOpenKeyExA, ::RegOpenKeyExW)(
				this->internal(), X.internal(), 0, Sam.internal(), &Result.internal()));
		return Result;
	}

	template<class Char>
	void delete_(const basic_lpstr<const Char> &X) const
	{
		exception::throw_unless(select<Char>(::RegDeleteKeyA, ::RegDeleteKeyW)(
			this->internal(), X.internal()));
	}

	void flush() const
	{
		exception::throw_unless(::RegFlushKey(this->internal()));	
	}

	void close() const
	{
		exception::throw_unless(::RegCloseKey(this->internal()));
	}
};

class hkey::create_result
{
public:
	hkey hkey;
	disposition disposition;
};

}
}
}

#endif
