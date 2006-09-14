#ifndef CBEAR_BERLIOS_DE_C_OUT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_OUT_HPP_INCLUDED

#include <cbear.berlios.de/c/traits.hpp>
#include <cbear.berlios.de/meta/identity.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
class out_t: public meta::identity<typename traits<T>::out_t> 
{
};

template<class T>
typename out_t<T>::type out(T &X) throw()
{
	return traits<T>::out(X);
}

}
}

#endif
