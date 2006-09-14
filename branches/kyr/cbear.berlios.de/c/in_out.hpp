#ifndef CBEAR_BERLIOS_DE_C_IN_OUT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_IN_OUT_HPP_INCLUDED

#include <cbear.berlios.de/c/traits.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
class in_out_t: public meta::identity<typename traits<T>::in_out_t> 
{
};

template<class T>
typename in_out_t<T>::type in_out(T &X) throw()
{
	return traits<T>::in_out(X);
}

}
}

#endif
