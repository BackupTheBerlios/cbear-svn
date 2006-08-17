#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPEINFO_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPEINFO_HPP_INCLUDED

#include <boost/utility/value_init.hpp>

#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class typekind_t
{
public:

	typedef ::TYPEKIND c_t;

	enum enum_t
	{
   	enum_ = ::TKIND_ENUM,
		record = ::TKIND_RECORD,
		module = ::TKIND_MODULE,
		interface_ = ::TKIND_INTERFACE,
		dispatch = ::TKIND_DISPATCH,
		coclass = ::TKIND_COCLASS,
		alias = ::TKIND_ALIAS,
		union_ = ::TKIND_UNION,
		max = ::TKIND_MAX,
	};

	typekind_t(enum_t X = enum_):
		X(c_t(X))
	{
	}

	static typekind_t &cpp_in_out(c_t *X)
	{
		return *cast::traits<typekind_t *>::reinterpret(X);
	}

	bool operator==(typekind_t const &B) const
	{
		return this->X == B.X;
	}

	bool operator!=(typekind_t const &B) const
	{
		return this->X != B.X;
	}

private:
	c_t X;
};

template<class Base>
class pointer_content<Base, ::ITypeInfo>: 
	public pointer_content<Base, ::IUnknown>
{
public:
	template<class T>
	typename T::itypeinfo_t::move_t getreftypeinfo(const T &hRefType) const
	{
		typename pointer<Base>::move_t Result;
		exception::throw_unless(
			this->reference().GetRefTypeInfo(hRefType.c_in(), Result->c_out()));
		return Result;
	}
};

typedef pointer< ::ITypeInfo> itypeinfo_t;

class hreftype_t
{
public:
	typedef itypeinfo_t itypeinfo_t;
	typedef ::HREFTYPE c_t;
	const c_t &c_in() const
	{
		return this->V;
	}
private:
	::HREFTYPE V;
};

class typeattr_t
{
public:

	typedef move::t<typeattr_t> move_t;

	typeattr_t()
	{
	}

	typeattr_t(itypeinfo_t const &I)
	{
		this->assign(I);
	}

	typeattr_t(move_t const &M)
	{
		this->assign(M);
	}

	~typeattr_t()
	{
		this->assign();
	}

	void assign()
	{
		if(this->info)
		{
			this->info->ReleaseTypeAttr(this->pointer.get());
			this->pointer.get() = 0;
		}
	}

	void assign(itypeinfo_t const &info)
	{
		this->assign();
		if(info->GetTypeAttr(&this->pointer.get()) == S_OK)
		{
			this->info = info;
		}
	}

	void assign(move_t const &M)
	{
		base::swap(this->info, M->info);
		base::swap(this->pointer, M->pointer);
	}

	uuid &guid()
	{
		return uuid::cpp_in_out(&this->pointer.get()->guid);
	}

	typekind_t &typekind()
	{
		return typekind_t::cpp_in_out(&this->pointer.get()->typekind);
	}

	unsigned long &sizeinstance()
	{
		return this->pointer.get()->cbSizeInstance;
	}

	unsigned short &cfuncs()
	{
		return this->pointer.get()->cFuncs;
	}

	unsigned short cvars()
	{
		return this->pointer.get()->cVars;
	}

private:

	typeattr_t(typeattr_t const &);
	typeattr_t &operator=(typeattr_t const &);

	itypeinfo_t info;
	base::initialized< ::TYPEATTR *> pointer;
};

class paramflags_t
{
public:
	enum enum_t
	{
		in = PARAMFLAG_FIN,
		out = PARAMFLAG_FOUT,
	};

	bool has(enum_t E) const
	{
		return (this->V & E) != 0;
	}

private:
	windows::ushort_t V;
};

class paramdesc_t
{
public:
	paramflags_t &paramflags()
	{
		return cast::traits<paramflags_t &>::reinterpret(this->V.wParamFlags);
	}
private:
	::PARAMDESC V;
};

class typedesc_t
{
public:
	typedesc_t &desc()
	{
		return *cast::traits<typedesc_t *>::reinterpret(this->V.lptdesc);
	}
	hreftype_t &hreftype()
	{
		return cast::traits<hreftype_t &>::reinterpret(this->V.hreftype);
	}
	vartype_t &vt()
	{
		return cast::traits<vartype_t &>::reinterpret(this->V.vt);
	}
private:
	::TYPEDESC V;
};

class elemdesc_t
{
public:
	typedesc_t &tdesc()
	{
		return cast::traits<typedesc_t &>::reinterpret(this->V.tdesc);
	}
	paramdesc_t &paramdesc()
	{
		return cast::traits<paramdesc_t &>::reinterpret(this->V.paramdesc);
	}
private:
	::ELEMDESC V;
};

class vardesc_t
{
public:

	vardesc_t()
	{
	}

	vardesc_t(itypeinfo_t const &info, unsigned int index)
	{
		this->assign(info, index);
	}

	void assign()
	{
		if(this->info)
		{
			this->info->ReleaseVarDesc(this->pointer.get());
			this->pointer.get() = 0;
		}
	}

	void assign(itypeinfo_t const &info, unsigned int index)
	{
		this->assign();
		if(info->GetVarDesc(index, &this->pointer.get()) == S_OK)
		{
			this->info = info;
		}
	}

	elemdesc_t &elemdescvar()
	{
		return cast::traits<elemdesc_t &>::reinterpret(
			this->pointer.get()->elemdescVar);
	}

	unsigned long &oinst()
	{
		return this->pointer.get()->oInst;
	}

private:

	vardesc_t(vardesc_t const &);
	vardesc_t &operator=(vardesc_t const &);

	itypeinfo_t info;
	base::initialized< ::VARDESC *> pointer;
};

class funcdesc_t
{
public:

	funcdesc_t()
	{
	}

	funcdesc_t(unsigned int N, itypeinfo_t const &info)
	{
		this->assign(N, info);
	}

	~funcdesc_t()
	{
		this->assign();
	}

	void assign()
	{
		if(this->info)
		{
			this->info->ReleaseFuncDesc(this->pointer.get());
			this->pointer.get() = 0;
		}
	}

	void assign(unsigned int N, itypeinfo_t const &info)
	{
		this->assign();
		if(info->GetFuncDesc(N, &this->pointer.get()) == S_OK)
		{
			this->info = info;
		}
	}

	short &cparams()
	{
		return this->pointer.get()->cParams;
	}

	elemdesc_t *elemdescparam()
	{
		return cast::traits<elemdesc_t *>::reinterpret(
			this->pointer.get()->lprgelemdescParam);
	}

private:

	funcdesc_t(funcdesc_t const &);
	funcdesc_t &operator=(funcdesc_t const &);

	itypeinfo_t info;
	base::initialized< ::FUNCDESC *> pointer;
};

template<class T>
class library_info;

template<class T>
class scoped_type_info
{
public:

	scoped_type_info()
	{
		this->Value = library_info<T>::type::typelib().gettypeinfoofguid<T>();
	}

	static const itypeinfo_t &typeinfo() 
	{ 
		return this->Value; 
	}

private:

	static itypeinfo_t Value;
};

template<class T>
itypeinfo_t scoped_type_info<T>::Value;

}
}
}

#endif
