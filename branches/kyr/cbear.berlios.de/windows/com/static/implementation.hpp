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
		iunknown_t &P = iunknown_t::cpp_out(
			reinterpret_cast<iunknown_t::c_out_t>(PP));
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
