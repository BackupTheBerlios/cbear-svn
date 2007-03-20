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
	return implementation<T>::new_();
}

template<class T, class P>
typename pointer<implementation<T> >::move_t new_(P const &P_)
{
	return implementation<T>::new_(P_);
}

}
}
}
}

#endif
