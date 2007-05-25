#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_ISUPPORTERRORINFO_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_ISUPPORTERRORINFO_HPP_INCLUDED

#include <cbear.berlios.de/c/in.hpp>
#include <cbear.berlios.de/c/cpp_in.hpp>
#include <cbear.berlios.de/c/out.hpp>
#include <cbear.berlios.de/c/cpp_out.hpp>
#include <cbear.berlios.de/windows/com/static/interface_content.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T, class B>
class interface_content<T, B, ::ISupportErrorInfo>: 
	public interface_<T, B, ::IUnknown>
{
public:
	HRESULT __stdcall InterfaceSupportsErrorInfo(const IID &)
	{
		return hresult::s_ok;
	}
};

}
}
}
}

#endif
