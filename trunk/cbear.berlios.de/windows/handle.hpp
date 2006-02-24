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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/overlapped.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>

#include <setupapi.h>
#include <cbear.berlios.de/windows/hwnd.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>

namespace cbear_berlios_de
{
namespace windows
{

typedef range::iterator_range<byte *> byte_range_t;

template<class Char>
class win32_find_data: 
	public select_traits<Char, WIN32_FIND_DATAA, WIN32_FIND_DATAW>::type
{
};

// Handle to an object.
class handle: public policy::wrap<handle, ::HANDLE>
{
public:
	typedef policy::wrap<handle, ::HANDLE> wrap_type;
	typedef wrap_type::internal_type internal_type;

	handle() {}
	explicit handle(internal_type X): wrap_type(X) {}

	dword_t DeviceIoControl(
		dword_t IoControlCode,
		const byte_range_t &In,
		const byte_range_t &Out,
		overlapped_t *Overlapped) const
	{
		dword_t BytesReturned;
		{
			exception::scope_last_error ScopeLastError;
			::DeviceIoControl(
				this->internal(),
				IoControlCode,
				In.begin(),
				dword_t(In.size()),
				Out.begin(),
				dword_t(Out.size()),
				&BytesReturned, 
				Overlapped);
		}
		return BytesReturned;
	}
};

template<class Char>
static handle FindFirstFile(
	const basic_lpstr<const Char> &fileName, 
	win32_find_data<Char> &findFileData)
{
	handle result;
	{
		exception::scope_last_error ScopeLastError;
		result.internal() = 
			select<Char>(::FindFirstFileA, ::FindFirstFileW)(
				fileName.internal(),
				&findFileData);
	}
	return result;
}

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

class hdevinfo: public policy::wrap<hdevinfo, ::HDEVINFO>
{
public:
	void SetupDiDestroyDeviceInfoList() const
	{
		exception::scope_last_error ScopeLastError;
		::SetupDiDestroyDeviceInfoList(this->internal());
	}
	void SetupDiEnumDeviceInfo(
		dword_t MemberIndex, sp_devinfo_data &DeviceInfoData) const
	{
		exception::scope_last_error ScopeLastError;
		::SetupDiEnumDeviceInfo(
			this->internal(), MemberIndex, &DeviceInfoData.internal());
	}
};

hdevinfo SetupDiCreateDeviceInfoList(const com::uuid *ClassGuid, hwnd Parent)
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
hdevinfo SetupDiGetClassDevsEx(
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

#endif
