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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_OBJECT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_OBJECT_HPP_INCLUDED

#include <cbear.berlios.de/base/exception.hpp>
#include <cbear.berlios.de/windows/syskind.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/com/bstr.hpp>
#include <cbear.berlios.de/windows/com/enum.hpp>
#include <cbear.berlios.de/windows/com/ulong.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class Base, class Interface = Base>
class implementation;

template<class Interface>
class object;

template<class Interface>
struct object_policy: private policy::standard_policy<Interface *>
{
	typedef policy::standard_policy<Interface *> standard_policy;

	using standard_policy::construct;
	using standard_policy::equal;
	using standard_policy::less;
	using standard_policy::swap;
	using standard_policy::reference_of;

	typedef typename standard_policy::pointer pointer;
	typedef typename standard_policy::reference reference;

	typedef Interface interface_type;
	typedef object<interface_type> object_type;
	typedef Interface *type;

	static void add_ref(type X) { if(X) X->AddRef(); }
	static void release(type X) { if(X) X->Release(); }

	static void construct_copy(type &This, const type &Source)
	{
		This = Source;
		add_ref(This);
	}

	static void assign(type &This, const type &Source) 
	{
		add_ref(Source);
		release(This);
		This = Source; 
	}

	static void destroy(type &This)
	{
		release(This);
	}

	typedef policy::wrap<object_type, type, object_policy> wrap;
};

template<class Interface1>
struct add_object { typedef object<Interface1> type; };

template<class Interface1>
struct add_object<object<Interface1> > { typedef object<Interface1> type; };

template<class Interface>
class object_base: public object_policy<Interface>::wrap
{
public:
	typedef Interface interface_type;
	typedef implementation<interface_type> implementation_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;

	static const vartype_t vt = 
		boost::is_base_of< ::IDispatch, Interface>::value ?
			::VT_DISPATCH: ::VT_UNKNOWN;

	template<class Type>
	typename add_object<Type>::type query_interface() const
	{
		typedef typename add_object<Type>::type object_type;
		object_type Result;
		internal_type P = this->internal();
		if(P)
		{
			P->QueryInterface(
				com::internal<in>(object_type::uuid()), 
				(void **)com::internal<out>(Result));
		}
		return Result;
	}		

	static const com::uuid &uuid() { return uuid::of<interface_type>(); }

	class uninitialized: public base::exception
	{
	public:
		void what(::std::ostream &O) const 
		{ 
			O << "cbear_berlios_de::com::object<" << typeid(Interface).name() << 
				"> uninitialized.";
		}
	};

protected:

	interface_type &internal_reference() const
	{ 
		internal_type P = this->internal();
		if(!P) throw uninitialized();
		return *P;
	}
};

template<class Base, class Interface>
class object_content: public object_base<Base>
{
};

template<class Interface>
class object: public object_content<Interface, Interface>
{
public:

	typedef Interface interface_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;

	object() {}

	template<class Interface1>
	object(const object<Interface1> &P)
	{
		internal_policy::construct_copy(this->internal(), P.internal());
	}

	explicit object(internal_type X)
	{
		internal_policy::construct_copy(this->internal(), X);
	}

	operator bool() const { return this->internal(); }
};

template<class T>
object<T> make_object(T *P) { return object<T>(P); }

typedef object< ::IUnknown> iunknown;
typedef object< ::IDispatch> idispatch;

typedef object< ::ITypeInfo> itypeinfo;

typedef LCID lcid_t;

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
	itypeinfo GetTypeInfoOfGuid() const
	{
		itypeinfo Result;
		exception::throw_unless(this->internal_reference().GetTypeInfoOfGuid(
			com::internal<in>(uuid::of<Interface>()), 
			com::internal<out>(Result)));
		return Result;
	}
	tlibattr_t GetLibAttr() const 
	{ 
		tlibattr_t::internal_type *Temp;
		exception::throw_unless(this->internal_reference().GetLibAttr(&Temp));
		tlibattr_t Result(*Temp);
		this->internal_reference().ReleaseTLibAttr(Temp);
		return Result;
	}
};

typedef object< ::ITypeLib> itypelib;

inline itypelib load_type_lib(const lpcwstr_t File)
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

typedef object< ::IClassFactory> iclassfactory;

class regcls: public com::enum_t<regcls, dword_t>
{
public:
	typedef com::enum_t<regcls, dword_t> wrap_type;
	enum enumeration_type 
	{ 
		singleuse = REGCLS_SINGLEUSE,
    multipleuse = REGCLS_MULTIPLEUSE,                        
    multi_separat = REGCLS_MULTI_SEPARATE,
    suspended = REGCLS_SUSPENDED,
    surrogate = REGCLS_SURROGATE,
	};
	regcls(enumeration_type X): wrap_type(X) {}
};

class clsctx: public com::enum_t<clsctx, dword_t>
{
public:
	typedef com::enum_t<clsctx, ::DWORD> wrap_type;
	enum enumeration_type 
	{ 
		inproc_server = CLSCTX_INPROC_SERVER, 
		inproc_handler = CLSCTX_INPROC_HANDLER, 
		local_server = CLSCTX_LOCAL_SERVER, 
		inproc_server16 = CLSCTX_INPROC_SERVER16,
		remote_server = CLSCTX_REMOTE_SERVER,
		inproc_handler16 = CLSCTX_INPROC_HANDLER16,
		//reserved1 = CLSCTX_RESERVED1,
		//reserved2 = CLSCTX_RESERVED2,
		//reserved3 = CLSCTX_RESERVED3,
		//reserved4 = CLSCTX_RESERVED4,
		no_code_download = CLSCTX_NO_CODE_DOWNLOAD,
		//reserved5 = CLSCTX_RESERVED5,
		no_custom_mrshal = CLSCTX_NO_CUSTOM_MARSHAL,
		enable_code_download = CLSCTX_ENABLE_CODE_DOWNLOAD,
		no_failure_log = CLSCTX_NO_FAILURE_LOG,
		//disable_aaa = CLSCTX_DISABLE_AAA,
		//enable_aaa = CLSCTX_ENABLE_AAA,
		//from_default_context = CLSCTX_FROM_DEFAULT_CONTEXT,

		all = CLSCTX_ALL,
	};
	clsctx(enumeration_type X): wrap_type(X) {}
};

class class_object
{
public:
	class_object(
		const uuid &Uuid, 
		const iunknown &Unk, 
		const clsctx &Clsctx, 
		const regcls &Regcls)
	{
		exception::throw_unless(::CoRegisterClassObject(
			internal<in>(Uuid),
			internal<in>(Unk),
			internal<in>(Clsctx),
			internal<in>(Regcls),
			internal<out>(this->Register)));
	}
	~class_object()
	{
		exception::throw_unless(::CoRevokeClassObject(this->Register));
	}
private:
	dword_t Register;
};

}
}
}

#endif
