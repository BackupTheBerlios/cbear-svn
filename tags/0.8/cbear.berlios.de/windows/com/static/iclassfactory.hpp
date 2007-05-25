#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_ICLASSFACTORY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_ICLASSFACTORY_HPP_INCLUDED

#include <cbear.berlios.de/c/in.hpp>
#include <cbear.berlios.de/c/cpp_in.hpp>
#include <cbear.berlios.de/c/out.hpp>
#include <cbear.berlios.de/c/cpp_out.hpp>
#include <cbear.berlios.de/windows/com/static/interface_content.hpp>
#include <cbear.berlios.de/windows/com/static/interface.hpp>
#include <cbear.berlios.de/windows/com/hresult.hpp>
#include <cbear.berlios.de/windows/bool.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T, class B>
class interface_content<T, B, ::IClassFactory>: 
	public interface_<T, B, ::IUnknown>
{
public:

	hresult::internal_type __stdcall CreateInstance(
		internal_result<in, iunknown_t>::type Outer, 
		const uuid::c_t &Uuid, 
		void **ppObject)
	{
		// Cannot aggregate.
		if(Outer) return hresult::class_e_noaggregation;
		return this->QueryInterface(Uuid, ppObject);
	}

	hresult::internal_type __stdcall LockServer(bool_t::value_t fLock)
	{
		if(fLock) this->AddRef(); else this->Release();
		return hresult::s_ok;
	}

};

}
}
}
}

#endif
