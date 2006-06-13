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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IMPLEMENTATION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IMPLEMENTATION_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/static/interface_list.hpp>
#include <cbear.berlios.de/windows/com/static/idispatch.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class implementation: 
	public T::template implementation_t<implementation<T> >,
	public interface_list<T, typename T::interface_list_t>
{
public:

	typedef typename T::template implementation_t<implementation> base_t;
	typedef interface_list<T, typename T::interface_list_t> interface_list_t;

	typedef com::pointer<implementation> pointer_t;

	implementation() 
	{
	}

	template<class P>
	implementation(const P &P_): 
		base_t(P_)
	{
	}		

	static typename pointer_t::move_t this_pointer(base_t &B)
	{
		return move::copy(pointer_t::cpp_in_cast(
			&static_cast<implementation &>(B)));
	}

// ::IUnknown
#if 1

	ulong_t __stdcall AddRef()
	{
		return this->Counter.increment();
	}

	ulong_t __stdcall Release()
	{
		ulong_t R = this->Counter.decrement();
		if(!R)
		{
			delete this;
			return 0;
		}
		return R;
	}

	hresult::internal_type __stdcall QueryInterface(
		const uuid::internal_type &U, void **PP)
	{
		iunknown &P = iunknown::cpp_out_cast(reinterpret_cast<iunknown::c_out_t>(PP));
		P = this->interface_list_t::query_interface(uuid::cpp_in_cast(&U));
		return P ? hresult::s_ok: hresult::e_nointerface;
	}

#endif

private:
	atomic::wrap<ulong_t> Counter;
};

}
}
}
}

#endif
