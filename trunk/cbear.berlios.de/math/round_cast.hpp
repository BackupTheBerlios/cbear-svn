#ifndef CBEAR_BERLIOS_DE_MATH_ROUND_CAST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_MATH_ROUND_CAST_HPP_INCLUDED

namespace cbear_berlios_de
{

template<class To, class From>
To round_cast(From f)
{
	return static_cast<To>(f + 0.5);
}

}

#endif
