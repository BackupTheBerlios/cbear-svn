#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_HKEY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_HKEY_HPP_INCLUDED

#include <Winreg.h>

#include <cbear.berlios.de/range/fill.hpp>
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

// RegCloseKey, ...
#pragma comment(lib, "advapi32.lib")

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
		//performance_text = 
		//	reinterpret_cast<std::ptrdiff_t>(HKEY_PERFORMANCE_TEXT),
		//performance_nlstext = 
		//	reinterpret_cast<std::ptrdiff_t>(HKEY_PERFORMANCE_NLSTEXT),
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
		registry::options options;
		registry::sam sam;
		windows::security_attributes security_attributes;
		create_options() {}
		create_options(
			basic_lpstr<const Char> class_,
			registry::options options,
			registry::sam sam,
			windows::security_attributes security_attributes):
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
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegCreateKeyEx)(
				//HKEY hKey,
				this->internal(),
				// LPCTSTR lpSubKey,
				SubKey.get(),
				//DWORD Reserved,
				0,
				//LPTSTR lpClass,
				const_cast<Char *>(Options.class_.get()),
				//DWORD dwOptions,
				Options.options.internal(),
				//REGSAM samDesired,
				Options.sam.internal(),
				//LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				Options.security_attributes.get(),
				//PHKEY phkResult,
				&Result.hkey.internal(),
				//LPDWORD lpdwDisposition,
				&Result.disposition.internal()));
		return Result;
	}

	// See
	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/base/regconnectregistry.asp
	template<class Char>
	hkey connect(const basic_lpstr<const Char> &X) const
	{
		hkey Result;
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegConnectRegistry)(
				X.internal(), this->internal(), &Result.internal()));
		return Result;
	}

	// See
	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/base/regopenkeyex.asp
	template<class Char>
	hkey open(const basic_lpstr<const Char> &SubKey, sam Sam) const
	{
		hkey Result;
		exception::throw_if(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegOpenKeyEx)(
			this->internal(), 
			SubKey.get(), 
			0, 
			Sam.internal(), 
			&Result.internal()));
		return Result;
	}

	template<class Char>
	void delete_(const basic_lpstr<const Char> &X) const
	{
		exception::throw_if(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegDeleteKey)(
			this->internal(), X.get()));
	}

	void flush() const
	{
		exception::throw_if(::RegFlushKey(this->internal()));	
	}

	void close() const
	{
		exception::throw_if(::RegCloseKey(this->internal()));
	}

	template<class Char>
	void query_value(
		basic_lpstr<Char const> const &Value,
		data<Char> &Data)
	{
		typedef data<Char> data_type;
		typedef typename data_type::properties_type properties_type;
		properties_type Properties = data_type::properties(Data);
		data_id_type Id = Properties.id;
		dword_t Size = Properties.size;
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegQueryValueEx)(
				this->internal(),
				Value.get(),
				0,
				&Id.get(),
				0,
				&Size));
		switch(Id.get())
		{
		case data_type::id_type::none:
			Data = data_type();
			break;
		case data_type::id_type::dword:
			Data = data_type(dword_t());
			break;
		case data_type::id_type::qword:
			Data = data_type(ulonglong_t());
			break;
		case data_type::id_type::sz:
			Data = data_type(data_type::string_type(range::make_fill(
				Char(0), Size / sizeof(Char) - 1)));
			break;
		default:
			BOOST_ASSERT(false);
		}
		Properties = data_type::properties(Data);
		BOOST_ASSERT(Size == Properties.size);
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegQueryValueEx)(
				this->internal(),
				Value.get(),
				0,
				&Id.get(),
				Properties.begin,
				&Size));
	}

	/*
	// Client: Requires Windows Vista or Windows XP Pro x64
	// Server: Requires Windows Server "Longhorn" or Windows Server 2003 SP1.
	template<class Char>
	void get_value(
		basic_lpstr<Char const> const &SubKey,
		basic_lpstr<Char const> const &Value,
		data<Char> &Data)
	{
		typedef data<Char> data_type;
		typedef typename data_type::properties_type properties_type;
		properties_type Properties = data_type::properties(Data);
		data_id_type Type = Properties.id;
		dword_t Size = Properties.size;
		exception::throw_if(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, RegGetValue)(
			this->internal(),
			SubKey.get(),
			Value.get(),
			Properties.flags.c_in(),
			&Type.get(),
			Properties.begin,
			&Size));
	}
	*/

	// See
	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/base/regsetvalueex.asp
	template<class Char, class DataType>
	void set_value(
		const basic_lpstr<const Char> &ValueName, DataType &Data) const
	{
		typedef data<Char> data_type;
		typedef typename data_type::properties_type properties_type;
		properties_type Properties = data_type::properties(Data);
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegSetValueEx)(
				this->internal(), 
				ValueName.get(),
				0,
				Properties.id.get(),
				Properties.begin,
				Properties.size));
	}

	template<class Char>
	void set_value(value<Char> &Value) const
	{ 
		this->set_value<Char>(Value.first, Value.second);
	}

	template<class Char>
	void set_value(data<Char> &Data) const 
	{ 
		this->set_value(basic_lpstr<const Char>(), Data); 
	}

	template<class Char>
	void delete_value(const basic_lpstr<const Char> &ValueName)
	{
		exception::throw_if(
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::RegDeleteValue)(
			this->internal(), ValueName.get()));
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
