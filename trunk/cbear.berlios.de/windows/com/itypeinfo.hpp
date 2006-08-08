#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPEINFO_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ITYPEINFO_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

typedef pointer< ::ITypeInfo> itypeinfo_t;

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
