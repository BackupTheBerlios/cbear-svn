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

typedef pointer< ::ITypeInfo> itypeinfo;

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
	static const itypeinfo &typeinfo() { return Value; }
private:
	static itypeinfo Value;
};

template<class T>
itypeinfo scoped_type_info<T>::Value;

}
}
}

#endif
