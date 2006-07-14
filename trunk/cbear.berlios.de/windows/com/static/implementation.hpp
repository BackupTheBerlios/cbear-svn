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
#include <cbear.berlios.de/windows/com/static/isupporterrorinfo.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

namespace detail
{

template<class T>
class implementation_traits
{
public:
	typedef typename T::template implementation_t<implementation<T> > base_t;
	typedef typename T::interface_list_t base_interface_list_t;
	typedef typename base_interface_list_t::template push_back< 
		::ISupportErrorInfo>::type 
		base_extension_interface_list_t;
	typedef interface_list<T, base_extension_interface_list_t> interface_list_t;
};

}

template<class T>
class implementation: 
	private detail::implementation_traits<T>::base_t,
	public detail::implementation_traits<T>::interface_list_t
{
public:

	typedef detail::implementation_traits<T> tratis_t;
	typedef typename tratis_t::base_t base_t;
	typedef typename tratis_t::interface_list_t interface_list_t;

	typedef com::pointer<implementation> pointer_t;

	class access_t: public base_t::access_t
	{
	public:
		access_t(implementation *This):
			base_t::access_t(static_cast<base_t *>(This))
		{
		}
	};

	implementation() 
	{
	}

	template<class P>
	implementation(const P &P_): 
		base_t(P_)
	{
	}		

	static typename pointer_t::move_t this_pointer(base_t *B)
	{
		return move::copy(pointer_t::cpp_in(static_cast<implementation *>(B)));
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
		iunknown &P = iunknown::cpp_out(reinterpret_cast<iunknown::c_out_t>(PP));
		P = this->interface_list_t::query_interface(uuid::cpp_in(&U));
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
