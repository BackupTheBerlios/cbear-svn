#ifndef CBEAR_BERLIOS_DE_BASE_ABS_HPP
#define CBEAR_BERLIOS_DE_BASE_ABS_HPP

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
