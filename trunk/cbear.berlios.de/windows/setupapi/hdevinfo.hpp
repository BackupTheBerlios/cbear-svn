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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_HDEVINFO_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_HDEVINFO_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/overlapped.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/windows/hwnd.hpp>

#include <cbear.berlios.de/windows/com/uuid.hpp>

#include <cbear.berlios.de/windows/registry/data.hpp>

#include <setupapi.h>

namespace cbear_berlios_de
{
namespace windows
{
namespace setupapi
{

class sp_devinfo_data: public policy::wrap<sp_devinfo_data, ::SP_DEVINFO_DATA>
{
public:
	sp_devinfo_data() { this->internal().cbSize = sizeof(internal_type); }

	com::uuid &ClassGuid() 
	{ 
		return com::uuid::wrap_ref(this->internal().ClassGuid); 
	}
	const com::uuid &ClassGuid() const 
	{ 
		return com::uuid::wrap_ref(this->internal().ClassGuid); 
	}

	dword_t &DevInst() { return this->internal().DevInst; }
	const dword_t &DevInst() const { return this->internal().DevInst; }
};

class spdrp: public policy::wrap<spdrp, dword_t>
{
public:

	typedef policy::wrap<spdrp, dword_t> wrap;

	enum enum_
	{
		address = SPDRP_ADDRESS,
		bustypeguid = SPDRP_BUSTYPEGUID,
		capabilities = SPDRP_CAPABILITIES,
		class_ = SPDRP_CLASS,
		characteristics = SPDRP_CHARACTERISTICS,
		classguid = SPDRP_CLASSGUID,
		compatibleids = SPDRP_COMPATIBLEIDS,
		configflags = SPDRP_CONFIGFLAGS,
		device_power_data = SPDRP_DEVICE_POWER_DATA,
		devicedesc = SPDRP_DEVICEDESC,
		devtype = SPDRP_DEVTYPE,
		driver = SPDRP_DRIVER,
		enumerator_name = SPDRP_ENUMERATOR_NAME,
		friendlyname = SPDRP_FRIENDLYNAME,
		hardwareid = SPDRP_HARDWAREID,
		location_information = SPDRP_LOCATION_INFORMATION,
		lowerfilters = SPDRP_LOWERFILTERS,
		mfg = SPDRP_MFG,
		physical_device_object_name = SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
		removal_policy = SPDRP_REMOVAL_POLICY,
		removal_policy_hw_default = SPDRP_REMOVAL_POLICY_HW_DEFAULT,
		removal_removal_policy_override = SPDRP_REMOVAL_POLICY_OVERRIDE,
		security = SPDRP_SECURITY,
		security_sds = SPDRP_SECURITY_SDS,
		service = SPDRP_SERVICE,
		ui_number = SPDRP_UI_NUMBER,
		ui_number_desc_format = SPDRP_UI_NUMBER_DESC_FORMAT,
		upperfilters = SPDRP_UPPERFILTERS,
	};

	spdrp() {}
	spdrp(enum_ E): wrap(E) {}
};

class hdevinfo: public policy::wrap<hdevinfo, ::HDEVINFO>
{
public:

	void DestroyDeviceInfoList() const
	{
		exception::scope_last_error ScopeLastError;
		::SetupDiDestroyDeviceInfoList(this->internal());
	}

	void EnumDeviceInfo(
		dword_t MemberIndex, sp_devinfo_data &DeviceInfoData) const
	{
		exception::scope_last_error ScopeLastError;
		::SetupDiEnumDeviceInfo(
			this->internal(), MemberIndex, &DeviceInfoData.internal());
	}

	template<class Char>
	void GetDeviceRegistryProperty(
		const sp_devinfo_data &DeviceInfoData,
		spdrp Property,
		registry::data_id_type &PropertyRegDataType,
		const byte_range &Buffer,
		dword_t &RequiredSize) const
	{
		exception::scope_last_error ScopeLastError;
		select<Char>(
			::SetupDiGetDeviceRegistryPropertyA, ::SetupDiGetDeviceRegistryPropertyW)(
				this->internal(), 
				const_cast<sp_devinfo_data::internal_type *>(
					&DeviceInfoData.internal()),
				Property.internal(),
				&PropertyRegDataType.internal(),
				Buffer.begin(),
				Buffer.size(),
				&RequiredSize);
	}
};

inline hdevinfo CreateDeviceInfoList(
	const com::uuid *ClassGuid, hwnd Parent)
{
	hdevinfo Result;
	{
		exception::scope_last_error ScopeLastError;
		Result.internal() = 
			::SetupDiCreateDeviceInfoList(
				ClassGuid ? &ClassGuid->internal(): 0,
				Parent.internal());
	}
	return Result;
}

class digcf: public policy::wrap<digcf, dword_t>
{
public:
	typedef policy::wrap<digcf, dword_t> wrap;

	enum enum_t
	{
		allclasses = DIGCF_ALLCLASSES,
		deviceinterface = DIGCF_DEVICEINTERFACE,
		present = DIGCF_PRESENT,
		profile = DIGCF_PROFILE,
	};

	digcf(enum_t E): wrap(E) {}
	digcf(): wrap(0) {}
};

template<class Char>
hdevinfo GetClassDevsEx(
	const com::uuid *ClassGuid,
	const basic_lpstr<const Char> &Enumerator,
	const hwnd &Parent,
	const digcf &Flags,
	hdevinfo DeviceInfoSet,
	const basic_lpstr<const Char> &MachineName)
{
	hdevinfo Result;
	{
		exception::scope_last_error ScopeLastError;
		Result.internal() = 
			select<Char>(::SetupDiGetClassDevsExA, ::SetupDiGetClassDevsExW)(
				ClassGuid ? &ClassGuid->internal(): 0,
				Enumerator.internal(),
				Parent.internal(),
				Flags.internal(),
				DeviceInfoSet.internal(),
				MachineName.internal(),
				0);
	}
	return Result;
}

}
}
}

#endif
