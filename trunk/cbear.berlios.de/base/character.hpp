#ifndef CBEAR_BERLIOS_DE_BASE_CHARACTER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CHARACTER_HPP_INCLUDED

// ::boost::mpl::bool_
#include <boost/mpl/bool.hpp>
// ::boost::is_same
#include <boost/type_traits/is_same.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class Type>
struct is_character: boost::mpl::bool_<
	boost::is_same<Type, char>::value ||
	boost::is_same<Type, wchar_t>::value>
{
};

}
}

#endif
