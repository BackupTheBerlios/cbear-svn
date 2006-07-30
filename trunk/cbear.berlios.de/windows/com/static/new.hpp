#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/static/interface_list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class pointer_t: public meta::identity<com::pointer<implementation<T> > > {};

template<class T>
typename pointer<implementation<T> >::move_t new_()
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in(new implementation_t()));
}

template<class T, class P>
typename pointer<implementation<T> >::move_t new_(const P &P_)
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in(new implementation_t(P_)));
}

}
}
}
}

#endif
