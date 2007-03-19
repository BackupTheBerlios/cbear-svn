#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_CONTENT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_CONTENT_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/iunknown.hpp>
#include <cbear.berlios.de/windows/com/hresult.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class implementation;

template<class T, class B, class I>
class interface_content;

template<class T, class B>
class interface_content<T, B, ::IUnknown>: public B
{
protected:
	typedef implementation<T> implementation_t;
	class access_t: public implementation_t::access_t
	{
	public:
		access_t(interface_content *This):
			implementation_t::access_t(static_cast<implementation_t *>(This))
		{
		}
	};
	iunknown_t::move_t query_interface(const uuid &U) throw()
	{
		if(uuid::of< ::IUnknown>()==U)
		{
			return move::copy(iunknown_t::cpp_in(static_cast< ::IUnknown *>(this)));
		}
		return iunknown_t::move_t();
	}
	/*
	hresult::c_t internal_catch() throw()
	{
		return static_cast<implementation_t *>(this)->catch_().c_in();
	}
	*/
};

}
}
}
}

#endif
