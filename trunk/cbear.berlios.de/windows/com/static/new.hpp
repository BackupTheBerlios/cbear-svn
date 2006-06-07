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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/iunknown.hpp>
#include <cbear.berlios.de/meta/list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class B, class I = B>
class interface_;

template<class B, class I>
class interface_content: public interface_<B, ::IUnknown>
{
};

template<class B>
class interface_content<B, ::IUnknown>: public B
{
};

template<class B, class I>
class interface_: public interface_content<B, I>
{
protected:
	iunknown::move_t query_interface(const uuid &U) throw()
	{
		if(uuid::of<I>()==U)
		{
			return move::copy(iunknown::cpp_in_cast(static_cast<I *>(this)));
		}
		return iunknown::move_t();
	}
};

template<class L>
class interface_list: 
	public interface_<typename L::front::type>, 
	public interface_list<typename L::pop_front::type>
{
protected:
	typedef interface_<typename L::front::type> interface_t;
	typedef interface_list<typename L::pop_front::type> pop_front_t;
	iunknown::move_t query_interface(const uuid &U) throw()
	{
		iunknown::move_t R = this->interface_t::query_interface(U);
		if(*R) 
		{
			return R;
		}
		return this->pop_front_t::query_interface(U);
	}
};

template<>
class interface_list<meta::list>
{
protected:
	iunknown::move_t query_interface(const uuid &) throw()
	{
		return iunknown::move_t();
	}
};

template<class T>
class implementation: 
	public T::template implementation_t<implementation<T> >,
	public interface_list<typename T::interface_list_t>
{
public:

	typedef typename T::template implementation_t<implementation> base_t;
	typedef interface_list<typename T::interface_list_t> interface_list_t;

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

template<class T>
typename pointer<implementation<T> >::move_t new_()
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in_cast(new implementation_t()));
}

template<class T, class P>
typename pointer<implementation<T> >::move_t new_(const P &P_)
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in_cast(new implementation_t(P_)));
}

}
}
}
}

#endif
