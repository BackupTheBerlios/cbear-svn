#ifndef CBEAR_BERLIOS_DE_C_CPP_IN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_CPP_IN_HPP_INCLUDED

#include <cbear.berlios.de/c/in.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
const T &cpp_in(const typename in_t<T>::type &X) throw()
{
	return traits<T>::cpp_in(X);
}

}
}

#endif
