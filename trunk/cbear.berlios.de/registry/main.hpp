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
#ifndef CBEAR_BERLIOS_DE_REGISTRY_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REGISTRY_MAIN_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/registry/sam.hpp>

namespace cbear_berlios_de
{
namespace registry
{

typedef LONG long_t;

class exception: public base::exception
{
public:
	enum enumeration_type 
	{ 
		success = ERROR_SUCCESS,
	};
	exception(long_t Result): Result(Result) {}
	virtual void what(::std::ostream &O) const
	{
		O << "cbear_berlios_de::registry::exception { result = " << this->Result <<
			" }";
	}
	long_t result() const { return this->Result; }
	static void throw_unless(long_t Result)
	{
		if(Result != success) throw exception(Result);
	}
private:
	long_t Result;
};

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

typedef SECURITY_ATTRIBUTES security_attributes;

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

	inline create_result create(
		const wchar_t *SubKey, 
		const wchar_t *Class, 
		options Options, 
		sam Sam, 
		const security_attributes &SecurityAttributes) const;

	hkey connect(const wchar_t *X) const
	{
		hkey Result;
		exception::throw_unless(::RegConnectRegistryW(
			X, this->internal(), &Result.internal()));
		return Result;
	}

	hkey open(const wchar_t *X, sam Sam) const
	{
		hkey Result;
		exception::throw_unless(RegOpenKeyExW(
			this->internal(), X, 0, Sam.internal(), &Result.internal()));
		return Result;
	}

	void delete_(const wchar_t *X) const
	{
		exception::throw_unless(::RegDeleteKeyW(this->internal(), X));
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

inline hkey::create_result hkey::create(
	const wchar_t *SubKey, 
	const wchar_t *Class, 
	options Options, 
	sam Sam, 
	const security_attributes &SecurityAttributes) const
{
	create_result Result;
	exception::throw_unless(::RegCreateKeyExW(
		//HKEY hKey,
		this->internal(),
		// LPCTSTR lpSubKey,
		SubKey,
		//DWORD Reserved,
		0,
		//LPTSTR lpClass,
		const_cast<wchar_t *>(Class),
		//DWORD dwOptions,
		Options.internal(),
		//REGSAM samDesired,
		Sam.internal(),
		//LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		const_cast<security_attributes *>(&SecurityAttributes),
		//PHKEY phkResult,
		&Result.hkey.internal(),
		//LPDWORD lpdwDisposition,
		&Result.disposition.internal()));
	return Result;
}

}
}

#endif
