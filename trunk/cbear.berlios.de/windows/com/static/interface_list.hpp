#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_LIST_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/static/interface.hpp>
#include <cbear.berlios.de/meta/list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T, class L>
class interface_list: 
	public interface_<T, typename L::front::type::interface_t>, 
	public interface_list<T, typename L::pop_front::type>
{
protected:
	typedef interface_<T, typename L::front::type::interface_t> interface_t;
	typedef interface_list<T, typename L::pop_front::type> pop_front_t;
	iunknown_t::move_t query_interface(const uuid &U) throw()
	{
		iunknown_t::move_t R = this->interface_t::query_interface(U);
		if(*R) 
		{
			return R;
		}
		return this->pop_front_t::query_interface(U);
	}
};

template<class T>
class interface_list<T, meta::list>
{
protected:
	iunknown_t::move_t query_interface(const uuid &) throw()
	{
		return iunknown_t::move_t();
	}
};

}
}
}
}

#endif
