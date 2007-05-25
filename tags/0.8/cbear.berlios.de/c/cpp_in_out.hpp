#ifndef CBEAR_BERLIOS_DE_C_CPP_IN_OUT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_CPP_IN_OUT_HPP_INCLUDED

#include <cbear.berlios.de/c/in_out.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
T &cpp_in_out(typename in_out<T>::type X) throw()
{
	return traits<T>::cpp_in_out(X);
}

}
}

#endif
