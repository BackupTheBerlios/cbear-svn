#ifndef CBEAR_BERLIOS_DE_SI_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_SI_MAIN_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace si
{

inline double yotta() throw()
{
	return 1.0e+24;
}

inline double zetta() throw()
{
	return 1.0e+21;
}

inline double exa() throw()
{
	return 1.0e+18;
}

inline double peta() throw()
{
	return 1.0e+15;
}

inline double tera() throw()
{
	return 1.0e+12;
}

inline double giga() throw()
{
	return 1.0e+9;
}

inline double mega() throw()
{
	return 1.0e+6;
}

inline double kilo() throw()
{
	return 1.0e+3;
}

inline double hecto() throw()
{
	return 1.0e+2;
}

inline double deka() throw()
{
	return 1.0e+1;
}

inline double deci() throw()
{
	return 1.0e-1;
}

inline double centi() throw()
{
	return 1.0e-2;
}

inline double milli() throw()
{
	return 1.0e-3;
}

inline double micro() throw()
{
	return 1.0e-6;
}

inline double nano() throw()
{
	return 1.0e-9;
}

inline double pico() throw()
{
	return 1.0e-12;
}

inline double femto() throw()
{
	return 1.0e-15;
}

inline double atto() throw()
{
	return 1.0e-18;
}

inline double zepto() throw()
{
	return 1.0e-21;
}

inline double yocto() throw()
{
	return 1.0e-24;
}

template<class T, T X>
class power_traits
{
public:

	template<T P>
	class power: public meta::const_<T, power<P - 1>::value * X>
	{
	};

	template<>
	class power<0>: public meta::const_<T, 1>
	{
	};
};

class integer
{
public:

	typedef ::boost::uint64_t t;

	template<t P>
	class e: public power_traits<t, 10>::power<P>
	{
	};

	// static t const yotta = e<24>::value;
	// static t const zetta = e<21>::value;
	static t const exa = e<18>::value;
	static t const peta = e<15>::value;
	static t const tera = e<12>::value;
	static t const giga = e<9>::value;
	static t const mega = e<6>::value;
	static t const kilo = e<3>::value;
	static t const hecto = e<2>::value;
	static t const deka = e<1>::value;
	static t const inversed_deci = e<1>::value;
	static t const inversed_centi = e<2>::value;
	static t const inversed_milli = e<3>::value;
	static t const inversed_micro = e<6>::value;
	static t const inversed_nano = e<9>::value;
	static t const inversed_pico = e<12>::value;
	static t const inversed_femto = e<15>::value;
	static t const inversed_atto = e<18>::value;
	// static t const inversed_zepto = e<21>::value;
	// static t const inversed_yocto = e<24>::value;
};

}
}

#endif
