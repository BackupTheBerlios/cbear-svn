#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPELIB_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPELIB_HPP_INCLUDED

#include <boost/filesystem/path.hpp>

#include <cbear.berlios.de/windows/hmodule.hpp>
#include <cbear.berlios.de/windows/syskind.hpp>
#include <cbear.berlios.de/windows/com/pointer.hpp>
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
		return uuid::cpp_in_out(&this->internal().guid); 
	}
	const uuid &guid() const 
	{ 
		return uuid::cpp_in(&this->internal().guid); 
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
class pointer_content<Base, ::ITypeLib>: 
	public pointer_content<Base, ::IUnknown>
{
public:
	template<class Interface>
	itypeinfo_t gettypeinfoofguid() const
	{
		itypeinfo_t Result;
		exception::throw_unless(this->reference().GetTypeInfoOfGuid(
			*uuid::of<Interface>().c_in(),
			com::internal<out>(Result)));
		return Result;
	}
	tlibattr_t getlibattr() const 
	{ 
		tlibattr_t::internal_type *Temp;
		exception::throw_unless(this->reference().GetLibAttr(&Temp));
		tlibattr_t Result(*Temp);
		this->reference().ReleaseTLibAttr(Temp);
		return Result;
	}
};

typedef pointer< ::ITypeLib> itypelib;

inline itypelib loadtypelib(const lpcwstr_t File)
{
	itypelib Result;
	com::exception::throw_unless(::LoadTypeLib(
		File.get(), com::internal<out>(Result)));
	return Result;
}

inline void register_type_lib(
	const itypelib &TypeLib, const lpcwstr_t &FullPath, const lpcwstr_t &HelpDir)
{
	com::exception::throw_unless(::RegisterTypeLib( 
		com::internal<in>(TypeLib), 
		const_cast<wchar_t *>(FullPath.get()), 
		const_cast<wchar_t *>(HelpDir.get())));
}

inline void un_register_type_lib(
	const uuid &LibId, 
	ushort_t VerMajor, 
	ushort_t VerMinor, 
	const lcid_t &Lcid, 
	const syskind_t &Syskind)
{
	com::exception::throw_unless(::UnRegisterTypeLib( 
		*LibId.c_in(),
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
			locale::cast<bstr_t>(TlbFileName.native_file_string()));
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
