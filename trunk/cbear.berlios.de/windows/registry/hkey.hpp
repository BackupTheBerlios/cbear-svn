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
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>
#include <cbear.berlios.de/windows/registry/disposition.hpp>
#include <cbear.berlios.de/windows/registry/sam.hpp>
#include <cbear.berlios.de/windows/registry/options.hpp>
#include <cbear.berlios.de/windows/registry/value.hpp>

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

	BOOST_STATIC_ASSERT(sizeof(int)>=sizeof(internal_type));

	enum enumeration_type
	{
		classes_root = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_CLASSES_ROOT),
		current_user = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_CURRENT_USER),
		local_machine = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_LOCAL_MACHINE),
		users = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_USERS),
		performance_data = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_PERFORMANCE_DATA),
		performance_text = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_PERFORMANCE_TEXT),
		performance_nlstext = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_PERFORMANCE_NLSTEXT),
		current_config = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_CURRENT_CONFIG),
		dyn_data = 
			reinterpret_cast<std::ptrdiff_t>(HKEY_DYN_DATA),
	};

	typedef wrap_type::internal_type internal_type;

	hkey() {}
	hkey(enumeration_type X): wrap_type(internal_type(X)) {}

	template<class Char>
	class create_options
	{
	public:
		basic_lpstr<const Char> class_;
		options options;
		sam sam;
		security_attributes security_attributes;
		create_options() {}
		create_options(
			basic_lpstr<const Char> class_,
			options options,
			sam sam,
			security_attributes security_attributes):
			class_(class_), 
			options(options), 
			sam(sam), 
			security_attributes(security_attributes)
		{
		}
	};

	class create_result;

	template<class Char>
	create_result create(
		basic_lpstr<const Char> SubKey, 
		const create_options<Char> &Options) const
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
			const_cast<Char *>(Options.class_.internal()),
			//DWORD dwOptions,
			Options.options.internal(),
			//REGSAM samDesired,
			Options.sam.internal(),
			//LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			Options.security_attributes.internal(),
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
	hkey open(const basic_lpstr<const Char> &SubKey, sam Sam) const
	{
		hkey Result;
		exception::throw_unless(
			select<Char>(::RegOpenKeyExA, ::RegOpenKeyExW)(
				this->internal(), 
				SubKey.internal(), 
				0, 
				Sam.internal(), 
				&Result.internal()));
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

	template<class Char, class DataType>
	void set_value(
		const basic_lpstr<const Char> &ValueName, const DataType &Data) const
	{
		typedef data<Char> data_type;
		typedef typename data_type::properties_type properties_type;
		properties_type Properties = data_type::properties(Data);
		exception::throw_unless(select<Char>(::RegSaveKeyExA, ::RegSaveKeyW)(
			this->internal(), 
			ValueName.internal(),
			Properties.id(),
			Properties.data(),
			Properties.size()));
	}

	template<class Char>
	void set_value(const value<Char> &Value) const
	{ 
		this->set_value(Value.name, Value.data); 
	}

	template<class Char>
	void set_value(const data<Char> &Data) const 
	{ 
		this->set_value(basic_lpstr<const Char>(), Data); 
	}

	template<class Char>
	void delete_value(const basic_lpstr<const Char> &ValueName)
	{
		exception::throw_unless(select<Char>(::RegDeleteKeyA, ::RegDeleteKeyW)(
			this->internal(), ValueName.internal()));
	}

	void delete_value() { this->delete_value(lpcstr_t()); }
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
