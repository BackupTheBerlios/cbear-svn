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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_SYSTEM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_SYSTEM_HPP_INCLUDED

// COINIT
#include <objbase.h>

#include <cbear.berlios.de/windows/com/exception.hpp>
#include <cbear.berlios.de/windows/com/object.hpp>
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
		multithreaded = COINIT_MULTITHREADED,
		apartmentthreaded = COINIT_APARTMENTTHREADED,
		disable_ole1dde = COINIT_DISABLE_OLE1DDE,
		speed_over_memory = COINIT_SPEED_OVER_MEMORY,
	};

	system(coinit_type C) { exception::throw_unless(::CoInitializeEx(0, C)); }
	~system() { ::CoUninitialize(); }
};

template<class T>
object<T> create_instance(
	const uuid &Uuid, const object<IUnknown> &UnkOuter, clsctx ClsContext)
{
	object<T> Result;
	exception::throw_unless(::CoCreateInstance(
		internal<in>(Uuid), 
		internal<in>(UnkOuter), 
		internal<in>(ClsContext), 
		internal<in>(uuid::of<T>()), 
		(void**)internal<out>(Result)));
	return Result;
}

}
}
}

#endif
