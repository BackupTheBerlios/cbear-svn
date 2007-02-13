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

#include <cbear.berlios.de/windows/registry/data.hpp>

#include <cbear.berlios.de/windows/optional_ref.hpp>
#include <cbear.berlios.de/windows/dynamic.hpp>

#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/com/bstr.hpp>

#include <vector>

#include <cbear.berlios.de/windows/setupapi.h>

#pragma comment(lib, "setupapi.lib")

namespace cbear_berlios_de
{
namespace windows
{
namespace setupapi
{

class sp_devinfo_data: public base::initialized< ::SP_DEVINFO_DATA>
{
public:

	sp_devinfo_data() 
	{ 
		this->get().cbSize = sizeof(value_t); 
	}

	com::uuid &ClassGuid() 
	{ 
		return com::uuid::cpp_in_out(&this->get().ClassGuid); 
	}
	const com::uuid &ClassGuid() const 
	{ 
		return com::uuid::wrap_ref(this->get().ClassGuid); 
	}

	dword_t &DevInst() { return this->get().DevInst; }
	const dword_t &DevInst() const { return this->get().DevInst; }
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

class sp_device_interface_data: 
	public policy::wrap<sp_device_interface_data, ::SP_DEVICE_INTERFACE_DATA>
{
public:

	typedef policy::wrap<sp_device_interface_data, ::SP_DEVICE_INTERFACE_DATA> 
		wrap;

	typedef wrap::internal_type internal_type;

	com::uuid &InterfaceClassGuid()
	{
		return com::uuid::cpp_in_out(&this->internal().InterfaceClassGuid);
	}

	sp_device_interface_data() 
	{ 
		this->internal().cbSize = sizeof(internal_type); 
	}
};

template<class Char>
class sp_device_interface_detail_data: public dynamic<typename 
	CBEAR_BERLIOS_DE_WINDOWS_TYPE(Char, ::SP_DEVICE_INTERFACE_DETAIL_DATA_)>
{
public:

	typedef dynamic<typename CBEAR_BERLIOS_DE_WINDOWS_TYPE(
		Char, ::SP_DEVICE_INTERFACE_DETAIL_DATA_)>
		wrap;

	typedef typename wrap::internal_type internal_type;

	sp_device_interface_detail_data()
	{
		this->internal().cbSize = sizeof(internal_type);
	}

	range::iterator_range<const wchar_t *> DevicePath()
	{
		static const int remainder_size = 
			sizeof(internal_type) - sizeof(this->internal().DevicePath);
		return range::iterator_range<const wchar_t *>(
			this->internal().DevicePath, 
			(this->wrap::size() - remainder_size) / sizeof(wchar_t) - 1);
	}
};

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

class hdevinfo: public policy::wrap<hdevinfo, ::HDEVINFO>
{
public:

	void Create(const com::uuid *ClassGuid, hwnd Parent)
	{
		this->Destroy();
		exception::scope_last_error ScopeLastError;
		this->internal() = 
			::SetupDiCreateDeviceInfoList(
				ClassGuid ? ClassGuid->c_in(): 0,
				Parent.get());
	}

	template<class Char>
	void GetClassDevsEx(
		const optional_ref<const com::uuid> &ClassGuid,
		const basic_lpstr<const Char> &Enumerator,
		const hwnd &Parent,
		const digcf &Flags,
		hdevinfo DeviceInfoSet,
		const basic_lpstr<const Char> &MachineName)
	{
		this->Destroy();
		exception::scope_last_error ScopeLastError;
		this->internal() = 
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::SetupDiGetClassDevsEx)(
				ClassGuid.get(),
				Enumerator.get(),
				Parent.get(),
				Flags.internal(),
				DeviceInfoSet.internal(),
				MachineName.get(),
				0);
		// Windows 2000 hack.
		ScopeLastError.reset_if(this->internal() != INVALID_HANDLE_VALUE);
	}

	~hdevinfo() { this->Destroy(); }

	void Destroy()
	{
		if(!this->internal()) 
		{
			return;
		}
		exception::scope_last_error ScopeLastError;
		::SetupDiDestroyDeviceInfoList(this->internal());
		this->internal() = 0;
	}

	bool EnumDeviceInfo(
		dword_t MemberIndex, sp_devinfo_data &DeviceInfoData) const
	{
		try
		{
			exception::scope_last_error ScopeLastError;
			::SetupDiEnumDeviceInfo(
				this->internal(), MemberIndex, &DeviceInfoData.get());
		}
		catch(const exception &E)
		{
			if(E.result()==exception::no_more_items) return false;
			throw;
		}
		return true;
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
		CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
			Char, ::SetupDiGetDeviceRegistryProperty)(
				this->internal(), 
				const_cast<sp_devinfo_data::value_t *>(
					&DeviceInfoData.get()),
				Property.internal(),
				&PropertyRegDataType.get(),
				Buffer.begin(),
				(dword_t)Buffer.size(),
				&RequiredSize);
	}

	class get_device_registry_property_exception: public std::exception
	{
	public:
		const char *what() const throw() 
		{ 
			return 
				"::cbear_berlios_de::windows::setupapi::hdevinfo::GetDeviceRegistryProperty";
		}
	};

	registry::data_id_type GetDeviceRegistryProperty(
		const sp_devinfo_data &DeviceInfoData,
		spdrp Property,
		com::bstr_t &Buffer) const
	{
		registry::data_id_type PropertyRegDataType;
		dword_t RequiredSize;
		try
		{
			this->GetDeviceRegistryProperty<wchar_t>(
				DeviceInfoData,
				Property,
				PropertyRegDataType,
				byte_range(),
				RequiredSize);
		}
		catch(const windows::exception &E)
		{
			if(E.result()!=windows::exception::insufficient_buffer) throw;
			if(
				PropertyRegDataType!=registry::data_id_type::sz &&
				PropertyRegDataType!=registry::data_id_type::multi_sz)
				throw get_device_registry_property_exception();
		}
		Buffer.resize(RequiredSize/2 - 1);
		this->GetDeviceRegistryProperty<wchar_t>(
			DeviceInfoData,
			Property,
			PropertyRegDataType,
			byte_range(
				(byte_t *)Buffer.c_str(), 
				(byte_t *)(Buffer.c_str() + Buffer.size() + 1)),
			RequiredSize);
		return PropertyRegDataType;
	}

	bool EnumDeviceInterfaces(
		const optional_ref<const sp_devinfo_data> &deviceInfoData,
		const com::uuid &interfaceClassGuid,
		dword_t memberIndex,
		sp_device_interface_data &deviceInterfaceData)
	{
		try
		{
			exception::scope_last_error ScopeLastError;
			SetupDiEnumDeviceInterfaces(
				this->internal(),
				const_cast< ::SP_DEVINFO_DATA *>(deviceInfoData.get()),
				interfaceClassGuid.c_in(),
				memberIndex,
				&deviceInterfaceData.internal());
		}
		catch(const exception &E)
		{
			if(E.result()==exception::no_more_items) return false;
			throw;
		}
		return true;
	}

	template<class Char>
	sp_device_interface_detail_data<Char> GetDeviceInterfaceDetail(
		const sp_device_interface_data &deviceInterfaceData,
		const optional_ref<const sp_devinfo_data> &deviceInfoData) const
	{
		dword_t requiredSize = 0;
		try
		{
			exception::scope_last_error ScopeLastError;
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
				Char, ::SetupDiGetDeviceInterfaceDetail)(
					this->internal(),
					const_cast< ::SP_DEVICE_INTERFACE_DATA *>(
						&deviceInterfaceData.internal()),
					0,
					0,
					&requiredSize,
					const_cast< ::SP_DEVINFO_DATA *>(deviceInfoData.get()));
		}
		catch(const windows::exception &E)
		{
			if(E.result()!=windows::exception::insufficient_buffer) throw;
		}
		sp_device_interface_detail_data<Char> deviceInterfaceDetailData;
		deviceInterfaceDetailData.resize(requiredSize);
		{
			exception::scope_last_error ScopeLastError;
			CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
				Char, ::SetupDiGetDeviceInterfaceDetail)(
					this->internal(),
					const_cast< ::SP_DEVICE_INTERFACE_DATA *>(
						&deviceInterfaceData.internal()),
					&deviceInterfaceDetailData.internal(),
					requiredSize,
					0,
					const_cast< ::SP_DEVINFO_DATA *>(deviceInfoData.get()));
		}
		return deviceInterfaceDetailData;
	}
};

}
}
}

#endif
