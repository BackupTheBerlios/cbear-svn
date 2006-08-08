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

class typeattr_t
{
public:

	typedef move::t<typeattr_t> move_t;

	typeattr_t()
	{
	}

	typeattr_t(const itypeinfo_t &I)
	{
		this->assign(I);
	}

	typeattr_t(const move_t &M)
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

	void assign(const itypeinfo_t &info)
	{
		this->assign();
		if(info->GetTypeAttr(&this->pointer.get()) == S_OK)
		{
			this->info = info;
		}
	}

	void assign(const move_t &M)
	{
		base::swap(this->info, M->info);
		base::swap(this->pointer, M->pointer);
	}

	uuid &guid()
	{
		return uuid::cpp_in_out(&this->pointer.get()->guid);
	}

private:

	typeattr_t(const typeattr_t &);
	typeattr_t &operator=(const typeattr_t &);

	itypeinfo_t info;
	base::initialized< ::TYPEATTR *> pointer;
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
