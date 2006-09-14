#ifndef CBEAR_BERLIOS_DE_C_IN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_C_IN_HPP_INCLUDED

#include <cbear.berlios.de/c/traits.hpp>
#include <cbear.berlios.de/meta/identity.hpp>

namespace cbear_berlios_de
{
namespace c
{

template<class T>
class in_t: public meta::identity<typename traits<T>::in_t> 
{
};

template<class T>
typename in_t<T>::type in(const T &X) throw()
{
	return traits<T>::in(X);
}

}
}

#endif
