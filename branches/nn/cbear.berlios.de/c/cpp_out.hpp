#ifndef CBEAR_BERLIOS_DE_C_CPP_OUT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_CPP_OUT_HPP_INCLUDED

#include <cbear.berlios.de/c/out.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
T &cpp_out(typename out_t<T>::type X) throw()
{
	return traits<T>::cpp_out(X);
}

}
}

#endif
