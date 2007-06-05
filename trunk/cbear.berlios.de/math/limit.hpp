#ifndef CBEAR_BERLIOS_DE_MATH_LIMIT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_MATH_LIMIT_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace math
{

template<class T>
T limit(T x, T min, T max)
{
	return x < min ? min: x > max ? max: x;
}

}
}

#endif
