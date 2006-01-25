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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPELIB_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPELIB_HPP_INCLUDED

#include <boost/filesystem/path.hpp>

#include <cbear.berlios.de/windows/hmodule.hpp>
#include <cbear.berlios.de/windows/com/object.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>
#include <cbear.berlios.de/windows/com/lcid.hpp>
#include <cbear.berlios.de/windows/com/itypeinfo.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class tlibattr_t: public policy::wrap<tlibattr_t, ::TLIBATTR>
{
public:
	typedef policy::wrap<tlibattr_t, ::TLIBATTR> wrap_type;
	explicit tlibattr_t(const internal_type &X): wrap_type(X) {}
	// globally unique library ID.
	uuid &guid() 
	{ 
		return uuid::wrap_ref(this->internal().guid); 
	}
	const uuid &guid() const 
	{ 
		return uuid::wrap_ref(this->internal().guid); 
	}
	// Locale of the TypeLibrary.
	lcid_t &lcid() 
	{ 
		return this->internal().lcid; 
	}
	const lcid_t lcid() const 
	{ 
		return this->internal().lcid; 
	}
	// Target hardware platform.
	syskind_t &syskind() 
	{ 
		return syskind_t::wrap_ref(this->internal().syskind); 
	}
	const syskind_t &syskind() const 
	{ 
		return syskind_t::wrap_ref(this->internal().syskind); 
	}
	// Major version number.
	ushort_t &wMajorVerNum() 
	{ 
		return this->internal().wMajorVerNum; 
	}
	const ushort_t &wMajorVerNum() const 
	{ 
		return this->internal().wMajorVerNum; 
	}
	// Minor version number.
	ushort_t &wMinorVerNum() 
	{ 
		return this->internal().wMinorVerNum; 
	}
	const ushort_t &wMinorVerNum() const 
	{ 
		return this->internal().wMinorVerNum; 
	}
  // Library flags.
	ushort_t &wLibFlags() 
	{ 
		return this->internal().wLibFlags; 
	}
	const ushort_t &wLibFlags() const 
	{ 
		return this->internal().wLibFlags; 
	}
};

template<class Base>
class object_content<Base, ::ITypeLib>: public object_content<Base, ::IUnknown>
{
public:
	template<class Interface>
	itypeinfo gettypeinfoofguid() const
	{
		itypeinfo Result;
		exception::throw_unless(this->internal_reference().GetTypeInfoOfGuid(
			com::internal<in>(uuid::of<Interface>()), 
			com::internal<out>(Result)));
		return Result;
	}
	tlibattr_t getlibattr() const 
	{ 
		tlibattr_t::internal_type *Temp;
		exception::throw_unless(this->internal_reference().GetLibAttr(&Temp));
		tlibattr_t Result(*Temp);
		this->internal_reference().ReleaseTLibAttr(Temp);
		return Result;
	}
};

typedef object< ::ITypeLib> itypelib;

inline itypelib loadtypelib(const lpcwstr_t File)
{
	itypelib Result;
	com::exception::throw_unless(::LoadTypeLib(
		File.internal(), com::internal<out>(Result)));
	return Result;
}

inline void register_type_lib(
	const itypelib &TypeLib, const lpcwstr_t &FullPath, const lpcwstr_t &HelpDir)
{
	com::exception::throw_unless(::RegisterTypeLib( 
		com::internal<in>(TypeLib), 
		const_cast<wchar_t *>(FullPath.internal()), 
		const_cast<wchar_t *>(HelpDir.internal())));
}

inline void un_register_type_lib(
	const uuid &LibId, 
	ushort_t VerMajor, 
	ushort_t VerMinor, 
	const lcid_t &Lcid, 
	const syskind_t &Syskind)
{
	com::exception::throw_unless(::UnRegisterTypeLib( 
		com::internal<in>(LibId),             
		VerMajor,  
		VerMinor,  
		com::internal<in>(Lcid),                 
		Syskind.internal()));
}

inline void un_register_type_lib(const tlibattr_t &LibAttr)
{
	un_register_type_lib(
		LibAttr.guid(), 
		LibAttr.wMajorVerNum(), 
		LibAttr.wMinorVerNum(),
		LibAttr.lcid(),
		LibAttr.syskind());
}

template<class T>
class scoped_typelib
{
public:
	static const itypelib &typelib() { return TypeLib; }
protected:
	scoped_typelib(const std::wstring &Name, const hmodule Module = hmodule())
	{ 
		boost::filesystem::path ThisFileName(
			Module.file_name<char_t>(), ::boost::filesystem::native);
		boost::filesystem::path Path = ThisFileName.branch_path();
		boost::filesystem::path TlbFileName = 
			Path / locale::cast<std::string>(Name + L".tlb");
		TypeLib = loadtypelib(
			locale::cast<std::wstring>(TlbFileName.native_file_string()));
	}
private:
	static itypelib TypeLib;
};

template<class T>
itypelib scoped_typelib<T>::TypeLib;

}
}
}

#endif
