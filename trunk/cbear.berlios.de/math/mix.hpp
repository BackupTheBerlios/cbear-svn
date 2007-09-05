#ifndef CBEAR_BERLIOS_DE_MATH_MIX_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_MATH_MIX_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace math
{

template<class T>
T mix(T a, T b, T p)
{
	return a * p + b * (1.0 - p);
}

}
}

#endif
