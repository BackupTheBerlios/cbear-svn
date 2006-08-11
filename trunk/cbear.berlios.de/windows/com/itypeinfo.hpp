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

typedef pointer< ::ITypeInfo> itypeinfo_t;

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

	unsigned short &cfuncs()
	{
		return this->pointer.get()->cFuncs;
	}

private:

	typeattr_t(typeattr_t const &);
	typeattr_t &operator=(typeattr_t const &);

	itypeinfo_t info;
	base::initialized< ::TYPEATTR *> pointer;
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
		Value = library_info<T>::type::typelib().gettypeinfoofguid<T>();
	}

	static const itypeinfo_t &typeinfo() { return Value; }

private:

	static itypeinfo_t Value;
};

template<class T>
itypeinfo_t scoped_type_info<T>::Value;

}
}
}

#endif
