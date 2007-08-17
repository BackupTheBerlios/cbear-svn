#ifndef CBEAR_BERLIOS_DE_BASE_CHARACTER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CHARACTER_HPP_INCLUDED

// ::boost::mpl::bool_
// #include <boost/mpl/bool.hpp>
// ::boost::is_same
#include <boost/type_traits/is_same.hpp>
#include <cbear.berlios.de/meta/const.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class T, class U>
class is_same: public meta::false_
{
};

template<class T>
class is_same<T, T>: public meta::true_
{
};

template<class T, class U>
class or: public meta::const_<bool, T::value || U::value>
{
};

template<class T>
class is_character: public is_same<T, char>::template or_<is_same<T, wchar_t> >
{
};

}
}

#endif
