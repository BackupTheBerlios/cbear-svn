#ifndef CBEAR_BERLIOS_DE_BASE_ABS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_ABS_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace base
{

template<class T>
T abs(T const &x)
{
	return x < T() ? -x: x;
}

}
}

#endif
