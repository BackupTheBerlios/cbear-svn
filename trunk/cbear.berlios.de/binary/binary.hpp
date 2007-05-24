#ifndef CBEAR_BERLIOS_DE_BINARY_BINARY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BINARY_BINARY_HPP_INCLUDED

#include <cbear.berlios.de/meta/const.hpp>

namespace cbear_berlios_de
{
namespace binary
{

template<unsigned int N>
class binary: public meta::const_<unsigned int, N>
{
public:

	template<unsigned int N2>
	class binary_: public binary<N << 4 | N2>
	{
	};

	typedef binary_<0>  _0000;
	typedef binary_<1>  _0001;
	typedef binary_<2>  _0010;
	typedef binary_<3>  _0011;
	typedef binary_<4>  _0100;
	typedef binary_<5>  _0101;
	typedef binary_<6>  _0110;
	typedef binary_<7>  _0111;
	typedef binary_<8>  _1000;
	typedef binary_<9>  _1001;
	typedef binary_<10> _1010;
	typedef binary_<11> _1011;
	typedef binary_<12> _1100;
	typedef binary_<13> _1101;
	typedef binary_<14> _1110;
	typedef binary_<15> _1111;
};

typedef binary<0>  _0000;
typedef binary<1>  _0001;
typedef binary<2>  _0010;
typedef binary<3>  _0011;
typedef binary<4>  _0100;
typedef binary<5>  _0101;
typedef binary<6>  _0110;
typedef binary<7>  _0111;
typedef binary<8>  _1000;
typedef binary<9>  _1001;
typedef binary<10> _1010;
typedef binary<11> _1011;
typedef binary<12> _1100;
typedef binary<13> _1101;
typedef binary<14> _1110;
typedef binary<15> _1111;


} // namespace binary
} // namespace cbear_berlios_de

#endif
