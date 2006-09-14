#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_SYSTEM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_SYSTEM_HPP_INCLUDED

// COINIT
#include <objbase.h>

#include <cbear.berlios.de/windows/com/exception.hpp>
#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/enum.hpp>
#include <cbear.berlios.de/windows/com/clsctx.hpp>

// ::CoInitializeEx
#pragma comment(lib, "ole32.lib")

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class system
{
public:

	enum coinit_type
	{
		apartmentthreaded = COINIT_APARTMENTTHREADED,

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
		multithreaded = COINIT_MULTITHREADED,
		disable_ole1dde = COINIT_DISABLE_OLE1DDE,
		speed_over_memory = COINIT_SPEED_OVER_MEMORY,
#endif

	};

	system()
	{
		exception::throw_unless(::CoInitialize(0));
	}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
	system(coinit_type C) 
	{ 
		exception::throw_unless(::CoInitializeEx(0, C)); 
	}
#endif

	~system() 
	{ 
		::CoUninitialize(); 
	}
};

template<class T>
pointer<T> create_instance(
	const uuid &Uuid, const pointer<IUnknown> &UnkOuter, clsctx ClsContext)
{
	pointer<T> Result;
	exception::throw_unless(::CoCreateInstance(
		*Uuid.c_in(), 
		internal<in>(UnkOuter), 
		internal<in>(ClsContext), 
		*uuid::of<T>().c_in(), 
		(void**)internal<out>(Result)));
/*
	exception::throw_unless(::CoCreateInstanceEx(
		*Uuid.c_in(), 
		internal<in>(UnkOuter), 
		internal<in>(ClsContext), 
		*uuid::of<T>().c_in(), 
		(void**)internal<out>(Result)));
		*/
	return Result;
}

}
}
}

#endif
